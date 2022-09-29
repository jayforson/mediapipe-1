load(
    "//mediapipe/framework/tool:mediapipe_graph.bzl",
    "mediapipe_simple_subgraph",
)

licenses(["notice"])

package(default_visibility = ["//visibility:public"])

mediapipe_simple_subgraph(
    name = "crop_scale_cpu",
    graph = "crop_scale_sub_graph.pbtxt",
    register_as = "CropScaleSubGraph",
    deps = [
        "//mediapipe/calculators/image:image_cropping_calculator",
        "//mediapipe/calculators/image:scale_image_calculator",
        "//mediapipe/calculators/util:detections_to_rects_calculator",
        "//mediapipe/calculators/presence_sdk:rect_to_crop_calculator",
    ],
)
