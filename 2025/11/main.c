#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char *file_name;
    uint64_t part1;
    uint64_t part2;
} ExpectedSolution;

void check_solution(size_t part, char *file_name, uint64_t solution) {
    ExpectedSolution solutions[3] = {
        {"sample1.txt", 5, 0},
        {"sample2.txt", 0, 2},
        {"input.txt", 791, 520476725037672},
    };
    for (size_t i = 0; i < 3; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint64_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
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

#define MAX_NODES 576
#define MAX_NAMES (26*26*26)

typedef struct {
    Node nodes[MAX_NODES];
    size_t count;

    size_t order_map[MAX_NODES];
    size_t names_map[MAX_NAMES];
} Graph;

void graph_init(Graph *g) {
    g->count = 0;
    for (size_t i = 0; i < MAX_NAMES; ++i) {
        g->names_map[i] = MAX_NODES;
    }
}

void graph_free(Graph *g) {
    for (size_t i = 0; i < g->count; ++i) {
        Edge *e = g->nodes[i].out;
        while (e != NULL) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
        g->nodes[i].out = NULL;
    }
    g->count = 0;
}

size_t graph_encode_name(const char* name) {
    return (
        (name[0] - 'a') * 26 * 26 +
        (name[1] - 'a') * 26 +
        (name[2] - 'a')
    );
}

size_t graph_get_node(Graph *g, const char *name) {
    return g->names_map[graph_encode_name(name)];
}

size_t graph_add_node(Graph *g, const char *name) {
    // NOTE: This may duplicate node
    size_t i = g->count++;
    strcpy(g->nodes[i].name, name);
    g->nodes[i].out = NULL;
    g->names_map[graph_encode_name(name)] = i;
    return i;
}

size_t graph_get_or_add_node(Graph *g, const char *name) {
    size_t i = graph_get_node(g, name);
    if (i == MAX_NODES) {
        i = graph_add_node(g, name);
    }
    return i;
}

void graph_add_edge(Graph *g, size_t from, size_t to) {
    // NOTE: This may duplicate edge
    Edge *e = malloc(sizeof(Edge));
    e->to = to;
    e->next = g->nodes[from].out;
    g->nodes[from].out = e;
}

#define BUFF_SIZE 128

void graph_load(Graph *g, const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[BUFF_SIZE];
    const char *delim = ": \n";

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');

        char *tok = strtok(buff, delim);
        size_t from = graph_get_or_add_node(g, tok);
        tok = strtok(NULL, delim);
        while (tok) {
            size_t to = graph_get_or_add_node(g, tok);
            graph_add_edge(g, from, to);
            tok = strtok(NULL, delim);
        }
    }

    fclose(fp);
}

void _dfs(Graph *g, bool *visited, size_t n, size_t *i) {
    visited[n] = true;

    for (Edge *e = g->nodes[n].out; e != NULL; e = e->next) {
        if (!visited[e->to]) {
            _dfs(g, visited, e->to, i);
        }
    }

    g->order_map[(*i)++] = n;
}

void graph_sort_topologically(Graph *g) {
    bool visited[MAX_NODES] = {0};
    size_t i = 0;
    for (size_t j = 0; j < g->count; ++j) {
        if (!visited[j]) {
            _dfs(g, visited, j, &i);
        }
    }
    assert(i == g->count);
}

uint64_t graph_count_paths_dp(Graph *g, const char *from, const char *to) {
    // NOTE: Requires the graph to be sorted topologically

    size_t from_i = graph_get_node(g, from);
    size_t to_i = graph_get_node(g, to);
    if (from_i == MAX_NODES || to_i == MAX_NODES) return 0;

    uint64_t dp[MAX_NODES] = {0};
    dp[from_i] = 1;

    for (int i = g->count - 1; i >= 0; --i) {
        size_t n = g->order_map[i];
        for (Edge *e = g->nodes[n].out; e != NULL; e = e->next) {
            dp[e->to] += dp[n];
        }
    }

    return dp[to_i];
}


void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    Graph graph;
    graph_init(&graph);
    graph_load(&graph, file_path);
    graph_sort_topologically(&graph);

    uint64_t solution_part1_ = graph_count_paths_dp(&graph, "you", "out");

    uint64_t solution_part2_ = (
        graph_count_paths_dp(&graph, "svr", "dac")
        * graph_count_paths_dp(&graph, "dac", "fft")
        * graph_count_paths_dp(&graph, "fft", "out")
    );
    if (solution_part2_ == 0) {
        solution_part2_ = (
            graph_count_paths_dp(&graph, "svr", "fft")
            * graph_count_paths_dp(&graph, "fft", "dac")
            * graph_count_paths_dp(&graph, "dac", "out")
        );
    }

    graph_free(&graph);

    printf("Part 1: %" PRIu64 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %" PRIu64 "\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
