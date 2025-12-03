#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *file_name;
    long long part1;
    long long part2;
} ExpectedSolution;


void check_solution(int part, char *file_name, long long solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 357LL, 3121910778619LL},
        {"input.txt", 17346LL, 172981362045136LL},
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


int find_max_digit(char digits[], int begin, int end) {
    int max_i = begin;
    for (int i = begin; i < end; ++i) {
        if (digits[i] > digits[max_i]) max_i = i;
        if (digits[i] == '9') break;
    }
    return max_i;
}


long long get_max_number(char digits[], int n, int n_digits) {
    long long result = 0;
    int i = -1;
    while (n_digits > 0) {
        n_digits -= 1;
        i = find_max_digit(digits, i + 1, n - n_digits);
        result += pow(10, n_digits) * (digits[i] - '0');
    }
    return result;
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    long long solution_part1_ = 0;
    long long solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char digits[128];
    while (fgets(digits, sizeof(digits), fp) != NULL) {
        int n = strlen(digits) - 1;
        assert(digits[n] == '\n');
        digits[n] = '\0';

        solution_part1_ += get_max_number(digits, n, 2);
        solution_part2_ += get_max_number(digits, n, 12);
    }

    fclose(fp);

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
