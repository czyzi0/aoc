import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 13,
    "input.txt": 22674,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 30,
    "input.txt": 5747443,
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
    return sum(2 ** (n_wins - 1) if n_wins else 0 for n_wins in read_n_wins(file_path))


def solve_part2(file_path):
    n_wins_list = list(read_n_wins(file_path))
    quantities = [1 for _ in n_wins_list]
    for i, n_wins in enumerate(n_wins_list):
        for j in range(i + 1, i + 1 + n_wins):
            quantities[j] += quantities[i]
    return sum(quantities)


def read_n_wins(file_path):
    with open(file_path, "r", encoding="utf-8") as fp:
        for line in fp:
            _, line = line.split(":")
            winners, numbers = line.split("|")
            winners = {int(n) for n in winners.strip().split()}
            yield sum(int(n) in winners for n in numbers.strip().split())


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
