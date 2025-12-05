#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IN_RANGE(x, lo, hi) (((x) >= (lo)) && ((x) <= (hi)))


typedef struct RangeNode {
    long long lo;
    long long hi;
    struct RangeNode *prev;
    struct RangeNode *next;
} RangeNode;


typedef struct {
    char *file_name;
    long long part1;
    long long part2;
} ExpectedSolution;


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
    RangeNode *head = NULL, *tail = NULL;

    // Load all ranges
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        if (strcmp(buff, "\n") == 0) break;

        long long lo, hi;
        assert(sscanf(buff, "%lld-%lld", &lo, &hi) == 2);

        RangeNode *node = malloc(sizeof(RangeNode));
        assert(node);

        node->lo = lo;
        node->hi = hi;
        node->prev = tail;
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    // Merge overlapping ranges
    RangeNode *curr = head;
    while (curr) {
        RangeNode *runn = curr->next;
        while (runn) {
            if (curr->hi < runn->lo || curr->lo > runn->hi) {  // No overlap
                runn = runn->next;
                continue;
            }

            runn->lo = (runn->lo < curr->lo) ? runn->lo : curr-> lo;
            runn->hi = (runn->hi > curr->hi) ? runn->hi : curr-> hi;

            RangeNode *tmp = curr;
            curr = curr->next;
            if (tmp->prev) tmp->prev->next = tmp->next;
            if (tmp->next) tmp->next->prev = tmp->prev;
            if (tmp == head) head = tmp->next;
            free(tmp);
            break;
        }
        if (!runn) curr = curr->next;
    }

    // Count fresh products
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        long long x;
        assert(sscanf(buff, "%lld", &x) == 1);
        curr = head;
        while (curr) {
            if (IN_RANGE(x, curr->lo, curr->hi)) {
                solution_part1_ += 1;
                break;
            }
            curr = curr->next;
        }
    }
    fclose(fp);

    // Count all possible fresh products
    curr = head;
    while (curr) {
        solution_part2_ += (curr->hi - curr->lo + 1);
        curr = curr->next;
    }

    // Clean up the list
    curr = head;
    while (curr) {
        RangeNode *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    head = NULL; tail = NULL;

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
