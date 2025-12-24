#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(size_t part, char *file_name, uint64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 4277556, 3263827},
        {"input.txt", 5060053676136, 9695042567249},
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


#define MAX_Y 8
#define MAX_N 1024

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint64_t solution_part1_ = 0;
    uint64_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    // Load problem sheet
    char *sheet[MAX_Y] = { NULL };
    size_t Y;

    for (Y = 0; Y < MAX_Y; ++Y) {
        size_t _size = 0;
        if (getline(&sheet[Y], &_size, fp) <= 0) break;
    }
    size_t X = strlen(sheet[0]);
    for (size_t y = 0; y < Y; ++y) sheet[y][X - 1] = ' ';

    // Parse ops
    char ops[MAX_N];
    size_t N;

    char *tok = strtok(sheet[Y - 1], " ");
    for (N = 0; N < MAX_N; ++N) {
        if (tok == NULL) break;
        ops[N] = tok[0];
        tok = strtok(NULL, " ");
    }
    free(sheet[Y - 1]);
    Y -= 1;

    // Locate problems on sheet, parse and solve
    size_t x = 0;
    for (size_t n = 0; n < N; ++n) {
        // Locate start of problem
        size_t bgn;
        for (; x < X; ++x) {
            // Skip empty columns
            int col_empty = 1;
            for (size_t y = 0; y < Y; ++y) {
                if (sheet[y][x] != ' ') {
                    col_empty = 0;
                    break;
                }
            }
            if (col_empty) continue;
            bgn = x;
            break;
        }
        // Locate end of problem
        size_t end;
        for (; x < X; ++x) {
            // Skip non-empty columns
            bool col_full = false;
            for (size_t y = 0; y < Y; ++y) {
                if (sheet[y][x] != ' ') {
                    col_full = true;
                    break;
                }
            }
            if (col_full) continue;
            end = x;
            break;
        }

        uint64_t result;
        // Parse and solve problem (part 1)
        result = (ops[n] == '+') ? 0 : 1;
        for (size_t y = 0; y < Y; ++y) {
            uint64_t num = 0;
            for (size_t x_ = bgn; x_ < end; ++x_) {
                if (sheet[y][x_] == ' ') continue;
                num *= 10;
                num += sheet[y][x_] - '0';
            }
            if (ops[n] == '+') {
                result += num;
            } else if (ops[n] == '*') {
                result *= num;
            } else {
                assert(false);
            }
        }
        solution_part1_ += result;

        // Parse and solve problem (part 2)
        result = (ops[n] == '+') ? 0 : 1;
        for (size_t x_ = bgn; x_ < end; ++x_) {
            uint64_t num = 0;
            for (size_t y = 0; y < Y; ++y) {
                if (sheet[y][x_] == ' ') continue;
                num *= 10;
                num += sheet[y][x_] - '0';
            }
            if (ops[n] == '+') {
                result += num;
            } else if (ops[n] == '*') {
                result *= num;
            } else {
                assert(false);
            }
        }
        solution_part2_ += result;
    }

    for (size_t y = 0; y < Y; ++y) free(sheet[y]);
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
