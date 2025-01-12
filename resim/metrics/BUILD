# Copyright 2023 ReSim, Inc.
#
# Use of this source code is governed by an MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT.

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "simple_metric",
    hdrs = ["simple_metric.hh"],
    visibility = ["//visibility:public"],
    deps = [
        "//resim/actor:actor_id",
        "//resim/time:timestamp",
    ],
)

cc_library(
    name = "min_distance",
    srcs = ["min_distance.cc"],
    hdrs = ["min_distance.hh"],
    deps = [
        "//resim/actor:actor_id",
        "//resim/actor/state:observable_state",
        "//resim/assert",
        "//resim/transforms:se3",
    ],
)

cc_test(
    name = "min_distance_test",
    srcs = ["min_distance_test.cc"],
    deps = [
        ":min_distance",
        "//resim/actor/state:observable_state",
        "//resim/actor/state:rigid_body_state",
        "//resim/testing:random_matrix",
        "//resim/transforms:se3",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "actor_metrics_unit",
    srcs = ["actor_metrics_unit.cc"],
    hdrs = ["actor_metrics_unit.hh"],
    visibility = ["//visibility:public"],
    deps = [
        "//resim/actor/state:observable_state",
        "//resim/assert",
        "//resim/metrics:min_distance",
        "//resim/metrics:simple_metric",
        "//resim/metrics/proto:simple_metric_proto_cc",
        "//resim/metrics/proto:simple_metric_to_proto",
        "//resim/simulator:executor_builder",
        "//resim/simulator:simulation_unit",
        "//resim/simulator:standard_topics",
        "//resim/time:timestamp",
        "//resim/utils:inout",
        "@fmt",
    ],
)

cc_test(
    name = "actor_metrics_unit_test",
    srcs = ["actor_metrics_unit_test.cc"],
    deps = [
        ":actor_metrics_unit",
        "//resim/actor:test_actor",
        "//resim/actor/state:observable_state",
        "//resim/actor/state:rigid_body_state",
        "//resim/simulator:executor_builder",
        "//resim/simulator:standard_topics",
        "//resim/time:timestamp",
        "//resim/time/proto:time_to_proto",
        "//resim/transforms:frame",
        "//resim/transforms:se3",
        "//resim/utils:inout",
        "//resim/utils:mcap_logger",
        "//resim/utils:uuid",
        "//resim/utils/testing:mock_logger",
        "@com_google_googletest//:gtest_main",
    ],
)
