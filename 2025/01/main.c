#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void solve(char *file_path) {
    printf("### %s ###\n", strrchr(file_path, '/') + 1);

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
    printf("Part 2: %d\n", solution_part2_);
}


int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
