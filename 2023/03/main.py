import re
import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 4361,
    "input.txt": 527369,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 467835,
    "input.txt": 73074886,
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

    def get_numbers(engine):
        pattern = re.compile(r"\d+")
        for y, line in enumerate(engine):
            for m in pattern.finditer(line):
                yield int(m.group()), y, m.start(), m.end() - 1

    def get_neighbors(engine, y, xs, xe):
        xmax = len(engine[y]) - 1
        ymax = len(engine) - 1

        if xs > 0:
            yield engine[y][xs - 1]
        if xe < xmax:
            yield engine[y][xe + 1]
        if y > 0:
            yield from engine[y - 1][max(xs - 1, 0) : min(xe + 1, xmax) + 1]
        if y < ymax:
            yield from engine[y + 1][max(xs - 1, 0) : min(xe + 1, xmax) + 1]

    result = 0

    engine = load_engine(file_path)
    for number, *coordinates in get_numbers(engine):
        neighbors = set(get_neighbors(engine, *coordinates))
        if "." in neighbors:
            neighbors.remove(".")
        if not neighbors:
            continue
        result += number

    return result


def solve_part2(file_path):

    def get_stars(engine):
        pattern = re.compile(r"\*")
        for y, line in enumerate(engine):
            for m in pattern.finditer(line):
                assert m.start() == m.end() - 1
                yield y, m.start()

    def get_numbers(engine, y, x):
        pattern = re.compile(r"\d+")
        for m in pattern.finditer(engine[y]):
            if m.start() == x + 1 or m.end() - 1 == x - 1:
                yield int(m.group())
        if y > 0:
            for m in pattern.finditer(engine[y - 1]):
                if x - 1 <= m.start() <= x + 1 or x - 1 <= m.end() - 1 <= x + 1:
                    yield int(m.group())
        if y < len(engine) - 1:
            for m in pattern.finditer(engine[y + 1]):
                if x - 1 <= m.start() <= x + 1 or x - 1 <= m.end() - 1 <= x + 1:
                    yield int(m.group())

    result = 0

    engine = load_engine(file_path)
    for y, x in get_stars(engine):
        numbers = list(get_numbers(engine, y, x))
        if len(numbers) == 2:
            result += numbers[0] * numbers[1]

    return result


def load_engine(file_path):
    with open(file_path, "r", encoding="utf-8") as fp:
        return [l.strip() for l in fp]


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
