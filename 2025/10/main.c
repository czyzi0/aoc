#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint32_t part1;
    uint32_t part2;
} ExpectedSolution;

void check_solution(size_t part, char *file_name, uint32_t solution) {
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 7, 0},
        {"input.txt", 0, 0},
    };
    for (size_t i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint32_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(false);
}


void set_bit(uint32_t *var, size_t idx, bool val) {
    if (val) {
        *var |= (uint32_t)1U << idx;
    } else {
        *var &= ~((uint32_t)1U << idx);
    }
}

bool get_bit(uint32_t var, size_t idx) {
    return (var >> idx) & 1U;
}

void parse_target(uint32_t *target, size_t *size, const char *text) {
    *target = 0;
    *size = (size_t)(strlen(text) - 2);
    for (size_t i = 0; i < *size; ++i) {
        if (text[i + 1] == '#') {
            set_bit(target, i, true);
        } else if (text[i + 1] != '.') {
            assert(false); 
        }
    }
}

void parse_button(uint32_t *button, const char *text) {
    *button = 0;
    const char *ptr = text + 1;
    char *end;
    while (*ptr != ')') {
        set_bit(button, (size_t)strtol(ptr, &end, 10), true);
        if (*end == ',') end++;
        ptr = end;
    }
}

#define N 256


void print_bits(uint32_t data, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        printf("%d", get_bit(data, i));
    }
    printf("\n");
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    // int32_t solution_part1_ = 0;
    // int32_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[N];

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');
        printf("%s", buff);

        size_t size = 0;
        uint32_t target, button;

        char *tok = strtok(buff, " ");
        while (tok) {
            printf("%s\n", tok);
            if (tok[0] == '[') {
                parse_target(&target, &size, tok);
            } else if (tok[0] == '(') {
                parse_button(&button, tok);

                print_bits(button, size);
            }
            tok = strtok(NULL, " ");
        }

        printf("%lu\n", size);
        print_bits(target, size);
        printf("\n");
    }

    fclose(fp);

    // printf("Part 1: %" PRId32 "\n", solution_part1_);
    // check_solution(1, file_name, solution_part1_);
    // printf("Part 2: %" PRId32 "\n", solution_part2_);
    // check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
