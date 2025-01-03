import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 21,
    "input.txt": 6958,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 525152,
    "input.txt": -1,
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
    for pattern, expected_groups in load_lines(file_path, n_folds=1):
        result += count_possible_solutions(pattern, expected_groups)
    return result


def solve_part2(file_path):
    result = 0
    for pattern, expected_groups in load_lines(file_path, n_folds=5):
        result += count_possible_solutions(pattern, expected_groups)
    return result


def load_lines(file_path, n_folds):
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            pattern, groups = line.strip().split()

            groups = [int(g) for g in reversed(",".join([groups] * n_folds).split(","))]
            pattern = "?".join([pattern] * n_folds) + "."
            yield pattern, groups


def count_possible_solutions(pattern, groups):
    result = 0

    def do(pattern, groups):
        if not pattern and not groups:
            nonlocal result
            result += 1
            return

        success, new_pattern = accept(pattern, ".")
        if success and sum(groups) + len(groups) <= len(new_pattern):
            do(new_pattern, groups)

        if not groups:
            return
        group = groups.pop()
        success, new_pattern = accept(pattern, "#" * group + ".")
        if success and sum(groups) + len(groups) <= len(new_pattern):
            do(new_pattern, groups)
        groups.append(group)

    def accept(pattern, prefix):
        for prefix_chr, pattern_chr in zip(prefix, pattern):
            if pattern_chr not in {"?", prefix_chr}:
                return False, ""
        return True, pattern[len(prefix):]

    do(pattern, groups)
    return result


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
