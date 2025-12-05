#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    int part1;
    int part2;
} ExpectedSolution;


void check_solution(int part, char *file_name, int solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 13, 0},
        {"input.txt", 0, 0},
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


int get_size(FILE *fp) {
    int size = 0;
    fseek(fp, 0, SEEK_SET);
    int c;
    while((c = fgetc(fp)) != EOF && c != '\n') size += 1;
    fseek(fp, 0, SEEK_SET);
    return size;
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int solution_part1_ = 0;
    // int solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    int size = get_size(fp);
    char *grid = malloc(size * size * sizeof(char));
    int c, i = 0;
    while((c = fgetc(fp)) != EOF) {
        if (c == '\n') continue;
        
    }


    fclose(fp);

    printf("Part 1: %d\n", solution_part1_);
    // check_solution(1, file_name, solution_part1_);
    // printf("Part 2: %d\n", solution_part2_);
    // check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
