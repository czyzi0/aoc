#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint32_t part1;
    uint32_t part2;
} ExpectedSolution;

void check_solution(size_t part, const char *file_name, uint32_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 13, 43},
        {"input.txt", 1351, 8345},
    };
    for (size_t i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint32_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(false);
}


#define IN_RANGE(x, lo, hi) (((x) >= (lo)) && ((x) < (hi)))

uint32_t remove_rolls(char *grid, int32_t size) {
    uint32_t n = 0;
    for (int32_t y = 0; y < size; ++y) {
        for (int32_t x = 0; x < size; ++x) {
            if (grid[y * size + x] == '.') continue;
            uint32_t nbors = 0;
            for (int32_t y_ = y - 1; y_ <= y + 1; ++y_) {
                for (int32_t x_ = x - 1; x_ <= x + 1; ++x_) {
                    if (y_ == y && x_ == x) continue;
                    if (IN_RANGE(y_, 0, size) && IN_RANGE(x_, 0, size) && grid[y_ * size + x_] != '.') nbors += 1;
                }
            }
            if (nbors < 4) {
                n += 1;
                grid[y * size + x] = 'x';
            }
        }
    }
    for (int32_t y = 0; y < size; ++y) {
        for (int32_t x = 0; x < size; ++x) {
            if (grid[y * size + x] == 'x') grid[y * size + x] = '.';
        }
    }
    return n;
}

void solve(const char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint32_t solution_part1_ = 0;
    uint32_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    // Find grid's size
    int32_t size = 0;
    int c;
    while ((c = fgetc(fp)) != EOF && c != '\n') size += 1;
    fseek(fp, 0, SEEK_SET);

    // Create and read grid
    char *grid = malloc(size * size * sizeof(char));
    assert(grid);
    int32_t i = 0;
    while ((c = fgetc(fp)) != EOF) {
        assert(i <= size * size);
        if (c == '\n') continue;
        grid[i++] = (char)c;
    }
    fclose(fp);

    solution_part2_ = solution_part1_ = remove_rolls(grid, size);
    while ((i = remove_rolls(grid, size)) != 0) solution_part2_ += i;

    free(grid);

    printf("Part 1: %" PRIu32 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %" PRIu32 "\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
