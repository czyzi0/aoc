import sys
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 405,
    "input.txt": 32723,
}
SOLUTIONS_PART2 = {
    "sample1.txt": 400,
    "input.txt": 34536,
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

    def compare(seq1, seq2):
        return seq1 == seq2

    result = 0
    for image in load_images(file_path):
        result += find_reflection_index(convert_image(transpose(image)), compare=compare)
        result += 100 * find_reflection_index(convert_image(image), compare=compare)
    return result


def solve_part2(file_path):

    def compare(seq1, seq2):
        non_zero = []
        for a, b in zip(seq1, seq2):
            if a - b != 0:
                non_zero.append((a, b))
        if len(non_zero) != 1:
            return False
        a, b = non_zero[0]
        return (a ^ b).bit_count() == 1

    result = 0
    for image in load_images(file_path):
        result += find_reflection_index(convert_image(transpose(image)), compare=compare)
        result += 100 * find_reflection_index(convert_image(image), compare=compare)
    return result


def load_images(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        yield from (i.split() for i in f.read().split("\n\n"))


def transpose(image):
    return [''.join(c) for c in zip(*image)]


def convert_image(image):
    return [int(l.translate(str.maketrans("#.", "10")), 2) for l in image]


def find_reflection_index(sequence, compare):
    for i in range(1, len(sequence)):
        l = min(i, len(sequence) - i)
        if compare(sequence[i - l:i][::-1], sequence[i: i + l]):
            return i
    return 0


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
