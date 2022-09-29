load(
    "//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_binary_graph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

exports_files(glob([
    "*.pbtxt",
]))

cc_library(
    name = "presence_sdk_calculators",
    deps = [
        "//mediapipe/calculators/core:pass_through_calculator",
        "//mediapipe/calculators/core:flow_limiter_calculator",
        "//mediapipe/modules/face_detection:face_detection_short_range_cpu",
        "//mediapipe/graphs/presence_sdk/subgraphs:crop_scale_cpu",
    ],
)

mediapipe_binary_graph(
    name = "presence_sdk_binary_graph",
    graph = "presence_sdk_smart_camera.pbtxt",
    output_name = "presence_sdk_smart_camera.binarypb",
    deps = [":presence_sdk_calculators"],
)
