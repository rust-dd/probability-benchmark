const std = @import("std");
const zprob = @import("zprob");

const num_runs = 1000;

fn run_once(allocator: *std.mem.Allocator) !u64 {
    const n = 500_000;
    const t = 1.0;
    const dt = t / @as(f64, n);

    var gn = try allocator.alloc(f64, n - 1);
    defer allocator.free(gn);

    var ou = try allocator.alloc(f64, n);
    defer allocator.free(ou);

    const theta = 1.0;
    const mu = 1.0;
    const sigma = 1.0;

    const seed: u64 = @intCast(std.time.microTimestamp());
    var prng = std.Random.DefaultPrng.init(seed);
    var rand = prng.random();
    var normal = zprob.Normal(f64).init(&rand);

    var timer = try std.time.Timer.start();

    for (0..n - 1) |i| {
        const sample = try normal.sample(0.0, std.math.sqrt(dt));
        gn[i] = sample;
    }

    ou[0] = 0.0;
    for (1..n) |i| {
        ou[i] = ou[i - 1] + theta * (mu - ou[i - 1]) * dt + sigma * gn[i - 1];
    }

    return timer.read();
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    var allocator = gpa.allocator();

    var total_ns: u64 = 0;

    for (0..num_runs) |_| {
        const elapsed_ns = try run_once(&allocator);
        total_ns += elapsed_ns;
    }

    const avg_ns = total_ns / num_runs;
    std.debug.print("Average elapsed time over {} runs: {d} ns\n", .{ num_runs, avg_ns });
    std.debug.print("Total: {d} ns\n", .{total_ns});
}
