#include "presence_sdk.h"


namespace presenceSDK {

    // pixel_data must have been allocated of
    // size at least width_step*height and width_step must be at least
    // width*num_channels*depth.  Both width_step and depth are in units
    // of bytes.
    PresenceSDK::PresenceSDK(mediapipe::ImageFormat::Format format,
        int width, int height, int width_step):
            mFormat(format),
            mWidth(width),
            mHeight(height),
            mWidthStep(width_step),
            mPoller(nullptr) {
    }

    absl::Status PresenceSDK::open() {
        // 1. get propto from file
        std::string graph_config_content;
        LOG(INFO) << "get propto from file";
        MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
            "mediapipe/graphs/presence_sdk/presence_sdk_smart_camera.pbtxt",
            &graph_config_content));

        // 2. get the config
        LOG(INFO) << "get the config";
        mediapipe::CalculatorGraphConfig config =
        mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
          graph_config_content);

        // 3. Initialize the grpah with config
        LOG(INFO) << "Initialize the grpah with config";
        MP_RETURN_IF_ERROR(mGraph.Initialize(config));

        // 4. Add output poller and start the graph
        LOG(INFO) << "Start running the calculator graph.";
        auto poller_or_status = mGraph.AddOutputStreamPoller(kOutputStream);
        RET_CHECK(poller_or_status.ok());
        mPoller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(poller_or_status.value()));
        MP_RETURN_IF_ERROR(mGraph.StartRun({}));

        LOG(INFO) << "Graph opened";
    }

    absl::Status PresenceSDK::processBuffer(uint8* input_pixel_data, uint8* output_pixel_data) {
        RET_CHECK(input_pixel_data != nullptr)
            << "Input data should not be null";
            // Send image packet into the graph.

        // Wrap input pixel data into ImageFrame
        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
            mFormat, mWidth, mHeight, mWidthStep, input_pixel_data);
        size_t frame_timestamp_us =
            (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;

        // Add input frame into packet
        MP_RETURN_IF_ERROR(mGraph.AddPacketToInputStream(
            kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us))));

        // Get the graph result packet, or stop if that fails.
        mediapipe::Packet packet;
        RET_CHECK(!mPoller->Next(&packet));
        auto& output_frame = packet.Get<mediapipe::ImageFrame>();

        if (output_pixel_data != nullptr) {
            output_frame.CopyToBuffer(output_pixel_data, mWidth * mHeight);
        } else {
            output_frame.CopyToBuffer(input_pixel_data, mWidth * mHeight);
        }
        RET_CHECK(true);
    }

    absl::Status PresenceSDK::close() {
        LOG(INFO) << "close the graph";
        MP_RETURN_IF_ERROR(mGraph.CloseInputStream(kInputStream));
        return mGraph.WaitUntilDone();
    }
} // namespace presenceSDK
