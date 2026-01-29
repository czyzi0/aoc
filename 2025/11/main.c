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


typedef struct EdgeList {
    size_t to;
    struct EdgeList *next;
} EdgeList;

typedef struct {
    char id[4];
    EdgeList *out;
} Node;

#define MAX_NODES 575
#define MAX_IDS (26*26*26)

typedef struct {
    Node nodes[MAX_NODES];
    size_t count;
    size_t ids[MAX_IDS];
} Graph;

void graph_init(Graph *g) {
    g->count = 0;
    for (size_t i = 0; i < MAX_IDS; ++i) {
        g->ids[i] = MAX_NODES;
    }
}

size_t graph_encode_id(const char* id) {
    return (
        (id[0] - 'a') * 26 * 26 +
        (id[1] - 'a') * 26 +
        (id[2] - 'a')
    );
}

size_t graph_add_or_get_node(Graph *g, const char *id) {
    size_t ide = graph_encode_id(id);

    size_t idx = g->ids[ide];
    if (idx != MAX_NODES) {
        return idx;
    }

    idx = g->count++;
    strcpy(g->nodes[idx].id, id);
    g->nodes[idx].out = NULL;
    g->ids[ide] = idx;
    return idx;
}

void graph_add_edge(Graph *g, size_t from, size_t to) {
    // NOTE: This can duplicate edges
    EdgeList *e = malloc(sizeof(EdgeList));
    e->to = to;
    e->next = g->nodes[from].out;
    g->nodes[from].out = e;
}

// void graph_free(Graph *g) {
//     // TODO: Write this
// }

#define BUFF_SIZE 128

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    int32_t solution_part1_ = 0;
    // int32_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[BUFF_SIZE];
    const char *delim = ": \n";

    Graph graph;
    graph_init(&graph);

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');

        char *tok = strtok(buff, delim);
        size_t from = graph_add_or_get_node(&graph, tok);
        tok = strtok(NULL, delim);
        while (tok) {
            size_t to = graph_add_or_get_node(&graph, tok);
            graph_add_edge(&graph, from, to);
            tok = strtok(NULL, delim);
        }

    }

    printf("Number of nodes: %lu\n", graph.count);
    for (size_t i = 0; i < graph.count; ++i) {
        printf("KEY: %s\n", graph.nodes[i].id);
        EdgeList *e = graph.nodes[i].out;
        while (e != NULL) {
            printf("%s\n", graph.nodes[e->to].id);
            e = e->next;
        }
        printf("========\n");
    }

    // TODO: Use DFS to find all possible paths from you to out

    fclose(fp);
    // graph_free(&graph);

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
