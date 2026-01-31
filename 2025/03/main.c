#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(size_t part, const char *file_name, uint64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 357, 3121910778619},
        {"input.txt", 17346, 172981362045136},
    };
    for (size_t i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint64_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(false);
}


size_t find_max_digit(const char *digits, size_t begin, size_t end) {
    size_t max_i = begin;
    for (size_t i = begin; i < end; ++i) {
        if (digits[i] > digits[max_i]) max_i = i;
        if (digits[i] == '9') break;
    }
    return max_i;
}

uint64_t get_max_number(const char *digits, size_t len, size_t n_digits) {
    uint64_t result = 0;
    int32_t i = -1;
    while (n_digits > 0) {
        n_digits -= 1;
        i = find_max_digit(digits, i + 1, len - n_digits);
        result += pow(10, n_digits) * (digits[i] - '0');
    }
    return result;
}

#define BUFF_SIZE 128

void solve(const char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint64_t solution_part1_ = 0;
    uint64_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char digits[BUFF_SIZE];
    while (fgets(digits, sizeof(digits), fp) != NULL) {
        size_t len = strlen(digits) - 1;
        digits[len] = '\0';

        solution_part1_ += get_max_number(digits, len, 2);
        solution_part2_ += get_max_number(digits, len, 12);
    }

    fclose(fp);

    printf("Part 1: %" PRIu64 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %" PRIu64 "\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
