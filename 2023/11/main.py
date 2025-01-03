import sys
from itertools import combinations
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 374,
    "input.txt": 9522407,
}
SOLUTIONS_PART2 = {
    "input.txt": 544723432977,
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
    return calculate_distance_sum(
        find_galaxy_cooridnates(
            image=load_image(file_path),
            expansion_ratio=2,
        )
    )


def solve_part2(file_path):
    return calculate_distance_sum(
        find_galaxy_cooridnates(
            image=load_image(file_path),
            expansion_ratio=1_000_000,
        )
    )


def load_image(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        return [l.strip() for l in f]


def find_galaxy_cooridnates(image, expansion_ratio):
    empty_rows = {i for i, row in enumerate(image) if row == len(row) * "."}
    image_transposed = [''.join(s) for s in zip(*image)]
    empty_cols = {i for i, row in enumerate(image_transposed) if row == len(row) * "."}

    galaxies = []
    y_mod = 0
    for y, row in enumerate(image):
        if y in empty_rows:
            y_mod += expansion_ratio - 1
            continue
        x_mod = 0
        for x, chr in enumerate(row):
            if x in empty_cols:
                x_mod += expansion_ratio - 1
                continue
            if chr == "#":
                galaxies.append((x + x_mod, y + y_mod))
    return galaxies


def calculate_distance_sum(galaxies):
    result = 0
    for g1, g2 in combinations(galaxies, 2):
        result += abs(g1[0] - g2[0]) + abs(g1[1] - g2[1])
    return result


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
