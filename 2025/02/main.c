#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(int part, char *file_name, uint64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 1227775554, 0},
        {"input.txt", 54234399924, 0},
    };
    for (int i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint64_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(0);
}


#define N 256

uint64_t count_digits(uint64_t n) {
    uint64_t result = 1;
    while (n >= 10) {
        n /= 10;
        result++;
    }
    return result;
}

uint64_t pow10_(uint64_t exp) {
    uint64_t result = 1;
    while (exp--) {
        result *= 10;
    }
    return result;
}

uint64_t sanitize_lo(uint64_t lo) {
    uint64_t n_digits = count_digits(lo);
    if (n_digits % 2 == 0) return lo;
    return pow10_(n_digits);
}

uint64_t sanitize_hi(uint64_t hi) {
    uint64_t n_digits = count_digits(hi);
    if (n_digits % 2 == 0) return hi;
    return pow10_(n_digits - 1) - 1;
}

uint64_t leading_half(uint64_t n) {
    uint64_t n_digits = count_digits(n);
    assert(n_digits % 2 == 0);
    return n / pow10_(n_digits / 2);
}

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint64_t solution_part1_ = 0;
    // int solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[N];

    int c;
    size_t i = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c != ',' && c != '\n') {
            buff[i++] = (char)c;
            assert(i < N);
            continue;
        }
        buff[i] = '\0';

        uint64_t lo, hi;
        assert(sscanf(buff, "%" SCNu64 "-%" SCNu64, &lo, &hi) == 2);

        lo = sanitize_lo(lo);
        hi = sanitize_hi(hi);
        for (uint64_t j = leading_half(lo); j <= leading_half(hi); ++j) {
            uint64_t candidate = pow10_(count_digits(j)) * j + j;
            if (candidate >= lo && candidate <= hi) solution_part1_ += candidate;
        }

        i = 0;
    }

    fclose(fp);

    printf("Part 1: %" PRIu64 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    // printf("Part 2: %d\n", solution_part2_);
    // check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
