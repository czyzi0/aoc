import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 136,
    "input.txt": 108918,
}
# SOLUTIONS_PART2 = {
#     "sample1.txt": 400,
#     "input.txt": 34536,
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

    result = 0
    for column in ("".join(c) for c in zip(*tiles)):
        rank = len(column)
        for i, tile in enumerate(column):
            match tile:
                case ".":
                    continue
                case "O":
                    result += rank
                    rank -= 1
                case "#":
                    rank = len(column) - i - 1
    return result


def solve_part2(file_path):
    return 0


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
