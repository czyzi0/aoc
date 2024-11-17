import re
import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 241,
    "input.txt": 54667,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 241,
    "sample2.txt": 281,
    "input.txt": 54203,
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
    number = 0
    regex = re.compile(r"\d")
    with open(file_path, "r", encoding="utf-8") as fp:
        for line in fp:
            match = regex.search(line)
            assert match
            number += 10 * str2int(match.group())
            match = regex.search("".join(reversed(line)))
            assert match
            number += str2int(match.group())
    return number


def solve_part2(file_path):
    number = 0
    pattern = "one|two|three|four|five|six|seven|eight|nine"
    regex_f = re.compile(r"\d|" + pattern)
    regex_b = re.compile(r"\d|" + "".join(reversed(pattern)))
    with open(file_path, "r", encoding="utf-8") as fp:
        for line in fp:
            match = regex_f.search(line)
            assert match
            number += 10 * str2int(match.group())
            match = regex_b.search("".join(reversed(line)))
            assert match
            number += str2int("".join(reversed(match.group())))
    return number


def str2int(text: str) -> int:
    try:
        return int(text)
    except ValueError:
        d = {
            "one": 1,
            "two": 2,
            "three": 3,
            "four": 4,
            "five": 5,
            "six": 6,
            "seven": 7,
            "eight": 8,
            "nine": 9,
        }
        return d[text]


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
