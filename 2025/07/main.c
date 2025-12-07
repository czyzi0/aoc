#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    long long part1;
    long long part2;
} ExpectedSolution;


void check_solution(int part, char *file_name, long long solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 21, 40},
        {"input.txt", 1562, 24292631346665},
    };
    for (int i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            long long expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(0);
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    long long solution_part1_ = 0;
    long long solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    // Find grid's size
    int X = 0, Y = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            Y += 1;
        } else if (Y == 0) {
            X += 1;
        }
    }
    fseek(fp, 0, SEEK_SET);

    // Create and read grid
    long long *grid = malloc(X * Y * sizeof(long long));
    assert(grid);
    int i = 0;
    while ((c = fgetc(fp)) != EOF) {
        assert(i <= X * Y);
        if (c == '\n') continue;
        c = (c == 'S') ? 1 : c;
        c = (c == '.') ? 0 : c;
        c = (c == '^') ? -1 : c;
        grid[i++] = (long long)c;
    }
    fclose(fp);

    // Propagate tachyons, counting possible paths
    for (int y = 0; y < Y - 1; ++y) {
        for (int x = 0; x < X; ++x) {
            int curr = x + X * y;
            int down = x + X * (y + 1);
            if (grid[curr] <= 0) continue;
            if (grid[down] != -1) {
                grid[down] += grid[curr];
            } else {
                if (x > 0) grid[down - 1] += grid[curr];
                if (x < X - 1) grid[down + 1] += grid[curr];
                solution_part1_ += 1;
            }
        }
    }

    // Calculate all possible paths
    for (int x = 0; x < X; ++x) {
        int curr = x + X * (Y - 1);
        if (grid[curr] > 0) solution_part2_ += grid[curr];
    }

    free(grid);

    printf("Part 1: %lld\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %lld\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
