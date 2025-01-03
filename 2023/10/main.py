import re
import sys
from dataclasses import dataclass
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 4,
    "sample2.txt": 8,
    "input.txt": 6701,
}
# SOLUTIONS_PART2 = {
#     "sample1.txt": 2,
#     "input.txt": 1211,
# }


def solve(file_path):
    print(f"### {file_path.name} ###")

    if file_path.name in SOLUTIONS_PART1:
        solution_part1_ = solve_part1(file_path)
        print(f"Part 1: {solution_part1_}")
        solution_part1 = SOLUTIONS_PART1[file_path.name]
        assert solution_part1_ == solution_part1

    # if file_path.name in SOLUTIONS_PART2:
    #     solution_part2_ = solve_part2(file_path)
    #     print(f"Part 2: {solution_part2_}")
    #     solution_part2 = SOLUTIONS_PART2[file_path.name]
    #     assert solution_part2_ == solution_part2


def solve_part1(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        tiles = [l.strip() for l in f]

    for y, row in enumerate(tiles):
        if match := re.search(r"S", row):
            s = V(match.start(), y)
            break
    else:
        raise RuntimeError

    if s.y - 1 >= 0 and tiles[s.y - 1][s.x] in "7|F":
        d = V(0, -1)
    elif s.y + 1 < len(tiles) and tiles[s.y + 1][s.x] in "L|J":
        d = V(0, 1)
    elif s.x - 1 >= 0 and tiles[s.y][s.y - 1] in "F-L":
        d = V(-1, 0)
    elif s.x + 1 < len(tiles[0]) and tiles[s.y][s.x + 1] in "J-7":
        d = V(1, 0)
    else:
        raise RuntimeError

    i = 0
    p = V(s.x, s.y)
    while True:
        i += 1

        p.x += d.x
        p.y += d.y

        match d, tiles[p.y][p.x]:
            case (V(-1, 0), "L") | (V(1, 0), "J"):
                d = V(0, -1)
            case (V(-1, 0), "F") | (V(1, 0), "7"):
                d = V(0, 1)
            case (V(0, -1), "7") | (V(0, 1), "J"):
                d = V(-1, 0)
            case (V(0, -1), "F") | (V(0, 1), "L"):
                d = V(1, 0)

        if p == s:
            break

    return i // 2


def solve_part2(file_path):
    return 0


@dataclass
class V:
    x: int
    y: int



if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
