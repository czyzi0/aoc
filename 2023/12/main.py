import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 21,
    "input.txt": 6958,
}
# SOLUTIONS_PART2 = {
#     "input.txt": 544723432977,
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

    def is_ok(candidate, limitation):
        for chr_candidate, chr_limitation in zip(candidate, limitation):
            if chr_limitation != "?" and chr_limitation != chr_candidate:
                return False
        return True

    limitations, groups_list = [], []
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            limitation, groups = line.strip().split()
            limitations.append(limitation)
            groups_list.append([int(g) for g in groups.split(",")])

    result = 0
    for limitation, groups in zip(limitations, groups_list):
        for candidate in generate_candidates(groups, len(limitation)):
            if is_ok(candidate, limitation):
                result += 1

    return result


# def solve_part2(file_path):
#     return 0


def generate_candidates(groups, length):
    n = length - sum(groups) - len(groups) + 1
    k = len(groups) + 1
    for gaps in generate_k_compositions(n, k):
        gaps = [gaps[0], *[g + 1 for g in gaps[1:-1]], gaps[-1]]
        yield "".join((
            *["." * gap + "#" * group for gap, group in zip(gaps[:-1], groups)],
            "." * gaps[-1]
        ))


def generate_k_compositions(n, k):
    composition = [0] * k
    composition[0] = n
    while True:
        yield composition
        v = composition[-1]
        if v == n:
            break
        composition[-1] = 0
        j = -2
        while composition[j] == 0:
            j -= 1
        composition[j] -= 1
        composition[j + 1] = 1 + v


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
