import re
import sys


SOLUTIONS_PART1 = {
    "sample1.txt": 4361,
    "input.txt": 527369,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 467835,
    "input.txt": 73074886,
}


def solve(file_path):
    print(file_path)

    if file_path in SOLUTIONS_PART1:
        solution_part1_ = solve_part1(file_path)
        print(f"Part 1: {solution_part1_}")
        solution_part1 = SOLUTIONS_PART1[file_path]
        assert solution_part1_ == solution_part1

    if file_path in SOLUTIONS_PART2:
        solution_part2_ = solve_part2(file_path)
        print(f"Part 2: {solution_part2_}")
        solution_part2 = SOLUTIONS_PART2[file_path]
        assert solution_part2_ == solution_part2

    print("-" * 40)


def solve_part1(file_path):
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

    for x_ in range(max(xs - 1, 0), min(xe + 1, xmax) + 1):
        if y > 0:
            yield engine[y - 1][x_]
        if y < ymax:
            yield engine[y + 1][x_]


def solve_part2(file_path):
    result = 0

    engine = load_engine(file_path)
    pattern = re.compile(r"\d+")
    for y, x in get_stars(engine):
        neighbors = '.'.join(get_spans(engine, y, x))
        numbers = [int(m.group()) for m in pattern.finditer(neighbors)]
        if len(numbers) == 2:
            result += numbers[0] * numbers[1]

    return result


def get_stars(engine):
    pattern = re.compile(r"\*")
    for y, line in enumerate(engine):
        for m in pattern.finditer(line):
            assert m.start() == m.end() - 1
            yield y, m.start()


def get_spans(engine, y, x):
    xmax = len(engine[y]) - 1
    ymax = len(engine) - 1

    if y > 0:
        xs = x
        while xs > 0:
            xs -= 1
            if not engine[y - 1][xs].isdigit():
                break
        xe = x
        while xe < xmax:
            xe += 1
            if not engine[y - 1][xe].isdigit():
                break
        yield engine[y - 1][xs:xe + 1]

    if y < ymax:
        xs = x
        while xs > 0:
            xs -= 1
            if not engine[y + 1][xs].isdigit():
                break
        xe = x
        while xe < xmax:
            xe += 1
            if not engine[y + 1][xe].isdigit():
                break
        yield engine[y + 1][xs:xe + 1]

    if x > 0:
        xs = x - 1
        while xs > 0:
            if not engine[y][xs].isdigit():
                break
            xs -= 1
        yield engine[y][xs:x]
    if x < xmax:
        xe = x + 1
        while xe < xmax:
            if not engine[y][xe].isdigit():
                break
            xe += 1
        yield engine[y][x + 1:xe + 1]


def load_engine(file_path):
    with open(file_path, "r") as fp:
        return [l.strip() for l in fp]


if __name__ == "__main__":
    for file_path in sys.argv[1:]:
        solve(file_path)
