
#ifndef PRESENCE_SDK_H_
#define PRESENCE_SDK_H_

#include <cstdlib>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"


namespace presenceSDK {

class PresenceSDK {
public:
    PresenceSDK(mediapipe::ImageFormat::Format format,
        int width, int height, int width_step);
    ~PresenceSDK() {};
    absl::Status open();
    absl::Status processBuffer(uint8* input_pixel_data,
        uint8* output_pixel_data = nullptr);
    absl::Status close();

private:
    mediapipe::CalculatorGraph mGraph;
    static constexpr char kInputStream[] = "input_video";
    static constexpr char kOutputStream[] = "output_video";
    mediapipe::ImageFormat::Format mFormat;
    int mWidth;
    int mHeight;
    int mWidthStep;
    std::unique_ptr<mediapipe::OutputStreamPoller> mPoller;
};

} // namespace PresenceSDK
#endif
