const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib = b.addStaticLibrary(.{
        .name = "tinyspline",

        // .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });

    lib.linkLibC();
    lib.addCSourceFiles(&.{
        "src/tinyspline.c",
    }, &.{});

    b.installArtifact(lib);

    const mod = b.addModule("tinyspline", .{
        .source_file = .{ .path = "src/zig/mod.zig" },
    });

    const main_tests = b.addTest(.{
        .root_source_file = .{ .path = "test/zig/tests.zig" },
        .target = target,
        .optimize = optimize,
    });
    main_tests.linkLibrary(lib);
    main_tests.addModule("tinyspline", mod);

    const run_main_tests = b.addRunArtifact(main_tests);

    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&run_main_tests.step);
}
