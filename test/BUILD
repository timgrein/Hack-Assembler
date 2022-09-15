cc_test(
    name = "tests",
    srcs = glob(["**/*.cpp"]),
    deps = [
        "//src/lib:assembler-lib",
        "@googletest//:gtest_main",
    ],
    data = glob([
        "resources/**"
    ])
)