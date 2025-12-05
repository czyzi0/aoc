#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define N 200

#define IN_RANGE(x, lo, hi) (((x) >= (lo)) && ((x) <= (hi)))


typedef struct {
    char *file_name;
    long long part1;
    long long part2;
} ExpectedSolution;


typedef struct {
    long long lo;
    long long hi;
} Range;


void check_solution(int part, char *file_name, long long solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 3, 14},
        {"input.txt", 701, 352340558684863},
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

    char buff[48];

    // Load all ranges
    Range ranges[N];
    int n = 0;
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(n < N);
        if (strcmp(buff, "\n") == 0) break;
        long long lo, hi;
        assert(sscanf(buff, "%lld-%lld", &lo, &hi) == 2);
        ranges[n].lo = lo;
        ranges[n].hi = hi;
        n += 1;
    }

    // Deduplicate ranges
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (ranges[i].hi < ranges[j].lo || ranges[i].lo > ranges[j].hi) continue;
            ranges[j].lo = (ranges[i].lo < ranges[j].lo) ? ranges[i].lo : ranges[j].lo;
            ranges[j].hi = (ranges[i].hi > ranges[j].hi) ? ranges[i].hi : ranges[j].hi;
            ranges[i].lo = ranges[i].hi = 0;
            break;
        }
    }

    // Count fresh products
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        long long x;
        assert(sscanf(buff, "%lld", &x) == 1);
        for (int i = 0; i < n; ++i) {
            if (ranges[i].lo == 0 || ranges[i].hi == 0) continue;
            if (IN_RANGE(x, ranges[i].lo, ranges[i].hi)) {
                solution_part1_ += 1;
                break;
            }
        }
    }

    // Count all possible fresh products
    for (int i = 0; i < n; ++i) {
        if (ranges[i].lo == 0 || ranges[i].hi == 0) continue;
        solution_part2_ += (ranges[i].hi - ranges[i].lo + 1);
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
