import sys
from itertools import pairwise
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 114,
    "input.txt": 1806615041,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 2,
    "input.txt": 1211,
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
    result = 0
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            result += extrapolate_sequence([int(n) for n in line.strip().split()])[-1]
    return result


def solve_part2(file_path):
    result = 0
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            result += extrapolate_sequence([int(n) for n in reversed(line.strip().split())])[-1]
    return result


def extrapolate_sequence(sequence):
    sequences = [sequence]

    while any(n != 0 for n in sequences[-1]):
        sequences.append([b - a for a, b in pairwise(sequences[-1])])

    sequences[-1].append(0)
    for seq1, seq2 in pairwise(reversed(sequences)):
        seq2.append(seq2[-1] + seq1[-1])

    return sequences[0]


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
