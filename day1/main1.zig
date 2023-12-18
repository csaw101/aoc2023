const std = @import("std");

const stdout = std.io.getStdOut().writer();

pub fn main() !void {
    var buf: [1024]u8 = undefined;
    var sum: u16 = 0;

    var file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();

    while (try in_stream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        var lineSum: u8 = 0;
        var c1: u8 = undefined;
        var c2: u8 = undefined;

        for (line) |c| {
            if (c >= 48 and c <= 57) {
                c1 = c;
                break;
            }
        }

        for (line) |c| {
            if (c >= 48 and c <= 57) {
                c2 = c;
            }
        }

        c1 -= 48;
        c1 *= 10;
        c2 -= 48;

        lineSum = c1 + c2;
        sum += lineSum;
    }

    try stdout.print("{}\n", .{sum}); // 53334
}
