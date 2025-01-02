import re
import sys
from itertools import cycle
from math import lcm
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 2,
    "sample2.txt": 6,
    "input.txt": 21797,
}
SOLUTIONS_PART2 = {
    "sample3.txt": 6,
    "input.txt": 23977527174353,
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
    instructions, network = load_instructions_network(file_path)

    n_steps, node = 0, "AAA"
    while node != "ZZZ":
        node = network[node][next(instructions)]
        n_steps += 1
    return n_steps


def solve_part2(file_path):
    instructions, network = load_instructions_network(file_path)

    n_steps_list = []
    for node in (n for n in network.keys() if n.endswith("A")):
        n_steps = 0
        while not node.endswith("Z"):
            node = network[node][next(instructions)]
            n_steps += 1
        n_steps_list.append(n_steps)

    return lcm(*n_steps_list)


def load_instructions_network(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    instructions = cycle(0 if i == "L" else 1 for i in lines[0].strip())

    network = {}
    for line in lines[2:]:
        match = re.match(r"(\w{3}) = \((\w{3}), (\w{3})\)", line.strip())
        assert match is not None
        network[match.group(1)] = (match.group(2), match.group(3))

    return instructions, network


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
