#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(size_t part, char *file_name, uint64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 1227775554, 4174379265},
        {"input.txt", 54234399924, 70187097315},
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

bool is_repeated(uint64_t n, uint64_t n_digits, size_t n_repeats) {
    if (n_digits % n_repeats != 0) return false;

    uint64_t aux = pow10_(n_digits / n_repeats);

    uint64_t last = n % aux;
    for (size_t i = 1; i < n_repeats; ++i) {
        n /= aux;
        if (n % aux != last) return false;
    }
    return true;
}

bool is_invalid_part1(uint64_t n) {
    return is_repeated(n, count_digits(n), 2);
}


bool is_invalid_part2(uint64_t n) {
    uint64_t n_digits = count_digits(n);
    for (uint64_t i = 2; i <= n_digits; ++i) {
        if (is_repeated(n, n_digits, i)) return true;
    }
    return false;
}

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint64_t solution_part1_ = 0;
    uint64_t solution_part2_ = 0;

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

        for (uint64_t n = lo; n <= hi; ++n) {
            if (is_invalid_part1(n)) solution_part1_ += n;
            if (is_invalid_part2(n)) solution_part2_ += n;
        }

        i = 0;
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
