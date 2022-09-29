licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

cc_library(
    name = "run_graph_main",
    srcs = ["run_graph_main.cc"],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "presence_sdk_cpu",
    deps = [
        "//mediapipe/examples/desktop/PresenceSDK:run_graph_main",
        "//mediapipe/graphs/presence_sdk:presence_sdk_calculators",
    ],
)

cc_library(
    name = "presence_sdk_libs",
    srcs = ["presence_sdk.cc"],
    hdrs = ["presence_sdk.h"],
    deps = [
        "//mediapipe/graphs/presence_sdk:presence_sdk_calculators",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
    alwayslink = True,
)

cc_binary(
    name = "presence_sdk.so",
    linkshared = 1,
    deps = [":presence_sdk_libs"],
)
