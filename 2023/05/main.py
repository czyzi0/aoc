import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 35,
    "input.txt": 621354867,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 46,
    "input.txt": 15880236,
}


def solve(file_path):
    print(f"### {file_path.name} ###")

    if file_path.name in SOLUTIONS_PART1:
        solution_part1_ = solve_part1(file_path)
        print(f"Part 1: {solution_part1_}")
        solution_part1 = SOLUTIONS_PART1[file_path.name]
        assert solution_part1_ == solution_part1

    if file_path.name in SOLUTIONS_PART2:
        solution_part2_ = solve_part2(file_path)
        print(f"Part 2: {solution_part2_}")
        solution_part2 = SOLUTIONS_PART2[file_path.name]
        assert solution_part2_ == solution_part2


def solve_part1(file_path):
    seeds, maps = read_almanac(file_path, lambda seeds: [(s, s + 1) for s in seeds])
    return min(s for s, _ in apply_maps(seeds, maps))


def solve_part2(file_path):
    seeds, maps = read_almanac(
        file_path,
        lambda seeds: [(s, s + r) for s, r in zip(seeds[::2], seeds[1::2])],
    )
    return min(s for s, _ in apply_maps(seeds, maps))


def read_almanac(file_path, parse_seeds):
    with open(file_path, "r", encoding="utf-8") as fp:
        seeds, *maps = fp.read().strip().split("\n\n")
        seeds = parse_seeds([int(s) for s in seeds.split(":")[-1].strip().split()])
        maps = [
            {
                (int(src), int(src) + int(rng)): int(trg) - int(src)
                for trg, src, rng in (l.strip().split() for l in m.split("\n")[1:])
            }
            for m in maps
        ]
        return seeds, maps


def apply_maps(ranges, maps):

    def apply_map(ranges, map_):
        new_ranges = []
        while ranges:
            start, end = ranges.pop()
            for (start_, end_), delta in map_.items():
                if start < end_ and end > start_:
                    if start < start_:
                        ranges.append((start, start_))
                    if end > end_:
                        ranges.append((end_, end))
                    new_ranges.append(
                        (max(start, start_) + delta, min(end, end_) + delta)
                    )
                    break
            else:
                new_ranges.append((start, end))
        return new_ranges

    for map_ in maps:
        ranges = apply_map(ranges, map_)
    return ranges


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
