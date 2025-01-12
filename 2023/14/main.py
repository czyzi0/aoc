import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 136,
    "input.txt": 108918,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 64,
    "input.txt": 100310,
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
    return calculate_total_load(move_left(load_tiles(file_path)))


def solve_part2(file_path):
    max_cycles = 1_000_000_000

    def locate_repeat(tiles):
        tiles_str_list = []
        for i in range(max_cycles):
            tiles = move_cycle(tiles)
            tiles_str = "".join("".join(r) for r in tiles)
            try:
                j = tiles_str_list.index(tiles_str)
                return j, i - j
            except ValueError:
                tiles_str_list.append(tiles_str)
        raise RuntimeError

    tiles = load_tiles(file_path)
    start, length = locate_repeat(tiles)
    for _ in range(start + (max_cycles - start) % length):
        tiles = move_cycle(tiles)
    return calculate_total_load(tiles)


def load_tiles(file_path):
    # <-- N
    with open(file_path, "r", encoding="utf-8") as f:
        tiles = [l.strip() for l in f]
        tiles = [list(x) for x in zip(*tiles)]
        tiles.reverse()
        return tiles


def calculate_total_load(tiles):
    result = 0
    for row in tiles:
        rank = len(row)
        for tile in row:
            if tile == "O":
                result += rank
            rank -= 1
    return result


def move_left(tiles):
    for row in tiles:
        j = 0
        for i, tile in enumerate(row):
            match tile:
                case ".":
                    continue
                case "O":
                    row[i], row[j] = ".", "O"
                    j += 1
                case "#":
                    j = i + 1
    return tiles


def move_cycle(tiles):
    for _ in range(4):
        tiles = move_left(tiles)
        tiles = [list(x) for x in zip(*reversed(tiles))]
    return tiles


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
