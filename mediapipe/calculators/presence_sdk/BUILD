load("//mediapipe/framework/port:build_config.bzl", "mediapipe_proto_library")

licenses(["notice"])

package(default_visibility = ["//visibility:private"])

mediapipe_proto_library (
    name = "rect_to_crop_calculator_proto",
    srcs = ["rect_to_crop_calculator.proto"],
    visibility = ["//visibility:public"],
    deps = [
        "//mediapipe/framework:calculator_options_proto",
        "//mediapipe/framework:calculator_proto",
    ],
)

cc_library(
    name = "rect_to_crop_calculator",
    srcs = ["rect_to_crop_calculator.cc"],
    hdrs = ["rect_to_crop_calculator.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":rect_to_crop_calculator_cc_proto",
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework:calculator_options_cc_proto",
        "//mediapipe/framework/formats:detection_cc_proto",
        "//mediapipe/framework/formats:location_data_cc_proto",
        "//mediapipe/framework/formats:rect_cc_proto",
        "//mediapipe/framework/port:ret_check",
        "//mediapipe/framework/port:status",
        "@com_google_absl//absl/types:optional",
    ],

    alwayslink = 1,
)
