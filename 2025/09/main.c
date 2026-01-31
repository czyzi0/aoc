#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *file_name;
    int64_t part1;
    int64_t part2;
} ExpectedSolution;

void check_solution(size_t part, const char *file_name, int64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 50, 0},
        {"input.txt", 4755429952, 0},
    };
    for (size_t i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            int64_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(false);
}


#define BUFF_SIZE 32
#define N 512

#define ABS(x) ((x) >= 0 ? (x) : -(x))

void solve(const char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int64_t solution_part1_ = 0;
    // int solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[BUFF_SIZE];
    int64_t x[N];
    int64_t y[N];
    size_t n = 0;

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(n <= N);
        assert(sscanf(buff, "%" SCNi64 ",%" SCNi64, &x[n], &y[n]) == 2);
        n += 1;
    }

    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            int64_t s = (1 + ABS(x[i] - x[j])) * (1 + ABS(y[i] - y[j]));
            solution_part1_ = (s > solution_part1_) ? s : solution_part1_;
        }
    }

    fclose(fp);

    printf("Part 1: %" PRIi64 "\n", solution_part1_);
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
