package(default_visibility = ["//visibility:public"])

load("//tensorflow/contrib/lite:build_def.bzl", "tflite_copts", "tflite_jni_binary")

licenses(["notice"])  # Apache 2.0

cc_library(
    name = "native_framework_only",
    srcs = [
        "exception_jni.cc",
        "nativeinterpreterwrapper_jni.cc",
        "tensor_jni.cc",
        "tensorflow_lite_jni.cc",
    ],
    hdrs = [
        "exception_jni.h",
        "nativeinterpreterwrapper_jni.h",
        "tensor_jni.h",
        "tensorflow_lite_jni.h",
        "tensorflow_lite_macro.h",
    ],
    copts = tflite_copts(),
    includes = select({
        "//tensorflow:android": [],
        "//conditions:default": ["."],
    }),
    linkopts = [
        "-lm",
        "-ldl",
    ],
    deps = [
        "//tensorflow/contrib/lite:context",
        "//tensorflow/contrib/lite:framework",
        "//tensorflow/contrib/lite:schema_fbs_version",
    ],
    alwayslink = 1,
    visibility = ["//visibility:public"],
)

# This includes all ops. If you want a smaller binary, you should copy and
# modify builtin_ops_jni.cc.  You should then link your binary against both
# ":native_framework_only" and your own version of ":native_builtin_ops".
cc_library(
    name = "native",
    srcs = [
        "builtin_ops_jni.cc",
    ],
    copts = tflite_copts(),
    deps = [
        ":native_framework_only",
        "//tensorflow/contrib/lite/kernels:builtin_ops",
    ],
    visibility = ["//visibility:public"],
    alwayslink = 1,
)

tflite_jni_binary(
    name = "libtensorflowlite-noops.so",
    deps = [
        ":native_framework_only",
    ],
    linkscript=":version_script.lds",
)

tflite_jni_binary(
    name = "libtensorflowlite.so",
    deps = [
        ":native",
    ],
    linkscript=":version_script.lds",
)

exports_files(
    [
        "version_script.lds",
    ],
)

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
        ],
    ),
    visibility = ["//tensorflow:__subpackages__"],
)
