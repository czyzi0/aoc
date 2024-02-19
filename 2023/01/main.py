import sys


def solve(file_path):
    print(file_path)
    print(f'Part 1: {solve_part1(file_path)}')
    print(f'Part 2: {solve_part2(file_path)}')


def solve_part1(file_path):
    number = 0
    with open(file_path, 'r') as fp:
        for line in fp:
            for c in line:
                digit = get_digit(c)
                if digit is not None:
                    number += 10 * digit
                    break
            for c in reversed(line):
                digit = get_digit(c)
                if digit is not None:
                    number += digit
                    break
    return number


def get_digit(character):
    try:
        return int(character)
    except ValueError:
        return None


def solve_part2(file_path):
    number = 0
    with open(file_path, 'r') as fp:
        for line in fp:
            for i in range(len(line)):
                digit = get_digit_(line[i:])
                if digit is not None:
                    number += 10 * digit
                    break
            for i in range(len(line) - 1, -1, -1):
                digit = get_digit_(line[i:])
                if digit is not None:
                    number += digit
                    break
    return number


def get_digit_(text):
    try:
        return int(text[0])
    except ValueError:
        d = {
            "one": 1, "two": 2, "three": 3,
            "four": 4, "five": 5, "six": 6,
            "seven": 7, "eight": 8, "nine": 9,
        }
        for digit_n, digit in d.items():
            if text.startswith(digit_n):
                return digit
    return None


if __name__ == "__main__":
    for file_path in sys.argv[1:]:
        solve(file_path)
