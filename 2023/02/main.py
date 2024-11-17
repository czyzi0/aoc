import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 8,
    "input.txt": 1734,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 2286,
    "input.txt": 70387,
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
    limits = {"red": 12, "green": 13, "blue": 14}
    result = 0

    with open(file_path, "r", encoding="utf-8") as fp:
        for game in fp:
            id_, rounds = parse_game(game)
            for round_ in rounds:
                if any(n > limits[c] for c, n in round_.items()):
                    break
            else:
                result += id_

    return result


def solve_part2(file_path):
    result = 0

    with open(file_path, "r", encoding="utf-8") as fp:
        for game in fp:
            _, rounds = parse_game(game)
            result += (
                max(r.get("red", 0) for r in rounds)
                * max(r.get("green", 0) for r in rounds)
                * max(r.get("blue", 0) for r in rounds)
            )

    return result


def parse_game(game):
    id_, rounds_ = game.split(":")

    id_ = int(id_.split()[-1])

    rounds = []
    for round__ in rounds_.split(";"):
        round_ = {}
        for number, color in (x.split() for x in round__.split(",")):
            number = int(number.strip())
            color = color.strip()
            round_[color] = number
        rounds.append(round_)

    return id_, rounds


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
