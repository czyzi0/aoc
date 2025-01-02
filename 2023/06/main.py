import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 288,
    "input.txt": 345015,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 71503,
    "input.txt": 42588603,
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
    with open(file_path, "r", encoding="utf-8") as f:
        times = [int(t) for t in next(f).strip().split()[1:]]
        distances = [int(d) for d in next(f).strip().split()[1:]]

    result = 1
    for time, distance in zip(times, distances):
        result *= count_solutions(time, distance)
    return result


def solve_part2(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        time = int("".join(next(f).strip().split()[1:]))
        distance = int("".join(next(f).strip().split()[1:]))

    return count_solutions(time, distance)


def count_solutions(time, distance):
    for i in range(1, time):
        if i * (time - i) > distance:
            return time + 1 - 2 * i
    return 0


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
