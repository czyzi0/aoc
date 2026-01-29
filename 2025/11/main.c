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
        {"sample1.txt", 5, 0},
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


typedef struct Edge {
    size_t to;
    struct Edge *next;
} Edge;

typedef struct {
    char name[4];
    Edge *out;
} Node;

#define MAX_NODES 575

typedef struct {
    Node nodes[MAX_NODES];
    size_t count;
} Graph;

size_t add_node(Graph *g, char *name) {
    // TODO: Check if node already exists, if so return its index

    size_t idx = g->count++;
    strcpy(g->nodes[idx].name, name);
    g->nodes[idx].out = NULL;
    return idx;
}

void add_edge(Graph *g, size_t from, size_t to) {
    Edge *e = malloc(sizeof(Edge));
    e->to = to;
    e->next = g->nodes[from].out;
    g->nodes[from].out = e;
}

#define BUFF_SIZE 128

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int32_t solution_part1_ = 0;
    // int32_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[BUFF_SIZE];

    Graph graph = {0};

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');

        size_t from;

        char *tok = strtok(buff, " ");
        while (tok) {
            if (tok[3] == ':') {
                tok[3] = '\0';
                from = add_node(&graph, tok);
            } else {
                size_t to = add_node(&graph, tok);
                printf("VALEUE: %s\n", tok);
            }
            tok = strtok(NULL, " ");
        }
        printf("==========\n");

        graph.count++;
    }

    fclose(fp);

    printf("Part 1: %" PRIu32 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    // printf("Part 2: %" PRId32 "\n", solution_part2_);
    // check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
