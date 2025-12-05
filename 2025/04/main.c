#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IN_RANGE(x, lo, hi) (((x) >= (lo)) && ((x) < (hi)))


typedef struct {
    char *file_name;
    int part1;
    int part2;
} ExpectedSolution;


void check_solution(int part, char *file_name, int solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 13, 43},
        {"input.txt", 1351, 8345},
    };
    for (int i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            int expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(0);
}


int remove_rolls(char grid[], int size) {
    int n = 0;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (grid[y * size + x] == '.') continue;
            int nbors = 0;
            for (int y_ = y - 1; y_ <= y + 1; ++y_) {
                for (int x_ = x - 1; x_ <= x + 1; ++x_) {
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
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            if (grid[y * size + x] == 'x') grid[y * size + x] = '.';
        }
    }
    return n;
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int solution_part1_ = 0;
    int solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    // Find grid's size
    int size = 0;
    int c;
    while((c = fgetc(fp)) != EOF && c != '\n') size += 1;
    fseek(fp, 0, SEEK_SET);

    // Create and read grid
    char *grid = malloc(size * size * sizeof(char));
    int i = 0;
    while((c = fgetc(fp)) != EOF) {
        if (c == '\n') continue;
        grid[i++] = (char)c;
    }
    fclose(fp);

    solution_part2_ = solution_part1_ = remove_rolls(grid, size);
    while((i = remove_rolls(grid, size)) != 0) solution_part2_ += i;

    free(grid);

    printf("Part 1: %d\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %d\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
