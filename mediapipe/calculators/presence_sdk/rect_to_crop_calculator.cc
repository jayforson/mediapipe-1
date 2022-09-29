// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "mediapipe/calculators/presence_sdk/rect_to_crop_calculator.h"

#include <cmath>
#include <limits>

#include "mediapipe/calculators/presence_sdk/rect_to_crop_calculator.pb.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator_options.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/formats/location_data.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/framework/port/status.h"

namespace mediapipe {

constexpr char kNormRectTag[] = "NORM_RECT";

absl::Status RectToCropCalculator::GetContract(CalculatorContract* cc) {
  RET_CHECK(cc->Inputs().HasTag(kNormRectTag))
      << "Exactly one NORM_RECT input stream should be provided.";
  RET_CHECK(cc->Outputs().HasTag(kNormRectTag))
      << "Exactly one NORM_RECT output stream should be provided.";

  if (cc->Inputs().HasTag(kNormRectTag)) {
    cc->Inputs().Tag(kNormRectTag).Set<NormalizedRect>();
  }
  if (cc->Outputs().HasTag(kNormRectTag)) {
    cc->Outputs().Tag(kNormRectTag).Set<NormalizedRect>();
  }
  return absl::OkStatus();
}

absl::Status RectToCropCalculator::Open(CalculatorContext* cc) {
  cc->SetOffset(TimestampDiff(0));

  options_ = cc->Options<RectToCropCalculatorOptions>();

  mCropWidth = options_.has_crop_width() ? options_.crop_width() : kCropWidth;
  mCropHeight = options_.has_crop_height() ? options_.crop_height() : kCropHeight;
  mPrevXCenter = 0.0f;
  mPrevYCenter = 0.0f;
  return absl::OkStatus();
}

absl::Status RectToCropCalculator::Process(CalculatorContext* cc) {
  if (cc->Inputs().HasTag(kNormRectTag) &&
      cc->Inputs().Tag(kNormRectTag).IsEmpty()) {
    return absl::OkStatus();
  }

  auto input_rect = cc->Inputs().Tag(kNormRectTag).Get<NormalizedRect>();

  auto output_rect = absl::make_unique<NormalizedRect>();

//   if (abs(input_rect.x_center() - mPrevXCenter) >= 0.01 || abs(input_rect.y_center() - mPrevYCenter) >= 0.01) {
//     output_rect->set_x_center(input_rect.x_center());
//     output_rect->set_y_center(input_rect.y_center() * 0.9);
//     mPrevXCenter = input_rect.x_center();
//     mPrevYCenter = input_rect.y_center();
//   } else {
//     output_rect->set_x_center(mPrevXCenter);
//     output_rect->set_y_center(mPrevYCenter * 0.9);
//   }

  output_rect->set_x_center(input_rect.x_center());
  output_rect->set_y_center(input_rect.y_center() * 0.9);
  output_rect->set_width(mCropWidth);
  output_rect->set_height(mCropHeight);

  cc->Outputs().Tag(kNormRectTag).Add(output_rect.release(), cc->InputTimestamp());
  return absl::OkStatus();
}

REGISTER_CALCULATOR(RectToCropCalculator);

}  // namespace mediapipe
