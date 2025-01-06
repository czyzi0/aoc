import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 1320,
    "input.txt": 512283,
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
        return sum(lpf_hash(i) for i in f.read().strip().split(","))


def solve_part2(file_path):
    return 0


def lpf_hash(text):
    result = 0
    for chr in text:
        result += ord(chr)
        result *= 17
        result %= 256
    return result


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
