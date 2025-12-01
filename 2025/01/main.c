#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void check_solution(int part, char *file_name, int solution) {
    if (strcmp(file_name, "sample1.txt") == 0) {
        switch (part) {
        case 1:
            assert(solution == 3);
            break;
        case 2:
            assert(solution == 6);
            break;
        default:
            assert(0);
        }
    } else if (strcmp(file_name, "input.txt") == 0) {
        switch (part) {
        case 1:
            assert(solution == 1048);
            break;
        case 2:
            assert(solution == 6498);
            break;
        default:
            assert(0);
        }
    } else {
        assert(0);
    }
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int solution_part1_ = 0;
    int solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[8];

    int dial = 50;
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');

        int rotation = atoi(buff + 1);
        int dial_;
        if (buff[0] == 'R') {
            dial_ = dial + rotation;

            solution_part2_ += dial_ / 100;
        } else if (buff[0] == 'L') {
            dial_ = dial - rotation;

            if (dial_ <= 0) {  // Crossed to or via 0
                if (dial != 0 ) solution_part2_ += 1;
                solution_part2_ -= dial_ / 100;  // Adjust for consecutive crosses
            }
        } else {
            assert(0);
        }

        dial = (dial_ % 100 + 100) % 100;

        if (dial == 0) {
            solution_part1_ += 1;
        }
    }

    fclose(fp);

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
