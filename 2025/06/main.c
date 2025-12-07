#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(int part, char *file_name, uint64_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 4277556, 0},
        {"input.txt", 5060053676136, 0},
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


#define MAX_LINES 8
#define MAX_NUMS 1024

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint64_t solution_part1_ = 0;
    uint64_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    uint32_t nums[MAX_LINES][MAX_NUMS];

    char *line = NULL;
    size_t size = 0;
    for (size_t i = 0; i < MAX_LINES; ++i) {
        assert(getline(&line, &size, fp) != -1);
        char *token = strtok(line, " \n");
        size_t j = 0;
        if (isdigit(token[0])) {
            while (token != NULL) {
                nums[i][j] = (uint32_t)atoi(token);
                token = strtok(NULL, " \n");
                j += 1;
            }
        } else {
            while (token != NULL) {
                uint64_t result;
                if (token[0] == '+') {
                    result = 0;
                    for (size_t k = 0; k < i; ++k) result += nums[k][j];
                } else if (token[0] == '*') {
                    result = 1;
                    for (size_t k = 0; k < i; ++k) result *= nums[k][j];
                }
                solution_part1_ += result;
                token = strtok(NULL, " \n");
                j += 1;
            }
            break;
        }
    }

    free(line);
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
