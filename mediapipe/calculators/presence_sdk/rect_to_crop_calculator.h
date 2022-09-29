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
#ifndef MEDIAPIPE_CALCULATORS_PRESENCE_SDK_RECT_TO_CROP_CALCULATOR_H_
#define MEDIAPIPE_CALCULATORS_PRESENCE_SDK_RECT_TO_CROP_CALCULATOR_H_

#include <cmath>

#include "absl/types/optional.h"
#include "mediapipe/calculators/presence_sdk/rect_to_crop_calculator.pb.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator_options.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/formats/location_data.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/framework/port/status.h"

namespace mediapipe {


// A calculator that converts Detection proto to Rect proto.
//
// Detection is the format for encoding one or more detections in an image.
// The input can be a single Detection or std::vector<Detection>. The output can
// be either a single Rect or NormalizedRect, or std::vector<Rect> or
// std::vector<NormalizedRect>. If Rect is used, the LocationData format is
// expected to be BOUNDING_BOX, and if NormalizedRect is used it is expected to
// be RELATIVE_BOUNDING_BOX.
//
// When the input is std::vector<Detection> and the output is a Rect or
// NormalizedRect, only the first detection is converted. When the input is a
// single Detection and the output is a std::vector<Rect> or
// std::vector<NormalizedRect>, the output is a vector of size 1.
//
// Inputs:
//
// One of the following:
// DETECTION: A Detection proto.
// DETECTIONS: An std::vector<Detection>.
//
// IMAGE_SIZE (optional): A std::pair<int, int> represention image width and
//   height. This is required only when rotation needs to be computed (see
//   calculator options).
//
// Output:
// One of the following:
// RECT: A Rect proto.
// NORM_RECT: A NormalizedRect proto.
// RECTS: An std::vector<Rect>.
// NORM_RECTS: An std::vector<NormalizedRect>.
//
// Example config:
// node {
//   calculator: "DetectionsToRectsCalculator"
//   input_stream: "DETECTIONS:detections"
//   input_stream: "IMAGE_SIZE:image_size"
//   output_stream: "NORM_RECT:rect"
//   options: {
//     [mediapipe.DetectionsToRectCalculatorOptions.ext] {
//       rotation_vector_start_keypoint_index: 0
//       rotation_vector_end_keypoint_index: 2
//       rotation_vector_target_angle_degrees: 90
//       output_zero_rect_for_empty_detections: true
//     }
//   }
// }
class RectToCropCalculator : public CalculatorBase {
 public:
  static absl::Status GetContract(CalculatorContract* cc);

  absl::Status Open(CalculatorContext* cc) override;
  absl::Status Process(CalculatorContext* cc) override;

 protected:
  ::mediapipe::RectToCropCalculatorOptions options_;
  float mCropWidth;
  float mCropHeight;
  float mPrevXCenter;
  float mPrevYCenter;
  float mTargetXCenter;
  float mTargetYCenter;
  int mSteps;
  const int kScaleSteps = 10;
  const float kCropWidth = 0.3;
  const float kCropHeight = 0.3;
};

}  // namespace mediapipe
#endif  // MEDIAPIPE_CALCULATORS_UTIL_DETECTIONS_TO_RECTS_CALCULATOR_H_
