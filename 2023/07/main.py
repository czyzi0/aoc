import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path


SOLUTIONS_PART1 = {
    "sample1.txt": 6440,
    "input.txt": 248396258,
}
SOLUTIONS_PART2 = {
   "sample1.txt": 5905,
    "input.txt": 246436046,
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

    def rate_hand(game):
        high_card_score = int(game.hand.translate(str.maketrans("TJQKA", "abcde")), 16)
        hand_type_score = rate_hand_type(sorted(Counter(game.hand).values()))
        return (hand_type_score, high_card_score)

    return calculate_winnings(load_games(file_path), rate_hand)


def solve_part2(file_path):

    def rate_hand(game):
        high_card_score = int(game.hand.translate(str.maketrans("TJQKA", "a1cde")), 16)

        counter = Counter(game.hand)
        signature = sorted(count for card, count in counter.items() if card != "J")
        if not signature and counter["J"] == 5:
            signature = [0]
        signature[-1] += counter["J"]

        hand_type_score = rate_hand_type(signature)

        return (hand_type_score, high_card_score)

    return calculate_winnings(load_games(file_path), rate_hand)


@dataclass
class Game:
    hand: str
    bid: int


def load_games(file_path):
    with open(file_path, "r", encoding="utf-8") as f:
        lines = (l.strip().split() for l in f)
        return [Game(l[0], int(l[1])) for l in lines]


def calculate_winnings(games, rate_hand):
    result = 0
    for rank, game in enumerate(sorted(games, key=rate_hand), 1):
        result += rank * game.bid
    return result


def rate_hand_type(signature):
    match signature:
        case [1, 1, 1, 1, 1]:
            return 0
        case [1, 1, 1, 2]:
            return 1
        case [1, 2, 2]:
            return 2
        case [1, 1, 3]:
            return 3
        case [2, 3]:
            return 4
        case [1, 4]:
            return 5
        case [5]:
            return 6
        case _:
            raise RuntimeError


if __name__ == "__main__":
    for file_path_ in sys.argv[1:]:
        solve(Path(file_path_))
