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
    ExpectedSolution solutions[2] = {
        {"sample1.txt", 40, 25272},
        {"input.txt", 47040, 4884971896},
    };
    for (size_t i = 0; i < 2; ++i) {
        if (strcmp(file_name, solutions[i].file_name) == 0) {
            uint64_t expected = (part == 1) ? solutions[i].part1 : solutions[i].part2;
            assert(solution == expected);
            return;
        }
    }
    assert(false);
}


#define N 1000

typedef struct {
    int32_t x, y, z;
    size_t circuit;
} JunctionBox;

int64_t calculate_distance(JunctionBox box1, JunctionBox box2) {
    int64_t dx = box1.x - box2.x;
    int64_t dy = box1.y - box2.y;
    int64_t dz = box1.z - box2.z;
    return dx * dx + dy * dy + dz * dz;
}

typedef struct {
    int64_t distance;
    size_t box1, box2;
} Distance;

int compare_distances(const void *p1, const void *p2) {
    const Distance *d1 = p1;
    const Distance *d2 = p2;

    if (d1->distance < d2->distance) return -1;
    if (d1->distance > d2->distance) return 1;
    return 0;
}

typedef struct {
    size_t *boxes;
    size_t size, capacity;
} Circuit;

void circuit_init(Circuit *c) {
    c->boxes = NULL;
    c->size = 0;
    c->capacity = 0;
}

void circuit_add(Circuit *c, size_t box) {
    if (c->size == c->capacity) {
        size_t capacity = c->capacity ? c->capacity * 2 : 4;
        size_t *boxes = realloc(c->boxes, capacity * sizeof(size_t));
        assert(boxes);
        c->capacity = capacity;
        c->boxes = boxes;
    }
    c->boxes[c->size++] = box;
}

void circuit_free(Circuit *c) {
    if (c->boxes != NULL) free(c->boxes);
    c->boxes = NULL;
    c->size = 0;
    c->capacity = 0;
}

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    // Note that sample data has different number of created connections
    size_t n_connections = (strcmp(file_name, "sample1.txt") == 0) ? 10 : 1000;

    uint64_t solution_part1_ = 0;
    uint64_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[256];

    JunctionBox *boxes = malloc(N * sizeof(JunctionBox));
    size_t n_boxes = 0;
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        JunctionBox b = { .circuit = N };
        assert(sscanf(buff, "%" SCNd32 ",%" SCNd32 ",%" SCNd32 "\n", &b.x, &b.y, &b.z) == 3);
        boxes[n_boxes++] = b;
        assert(n_boxes <= N);
    }

    Distance *distances = malloc(n_boxes * (n_boxes - 1) / 2 * sizeof(Distance));
    size_t n_distances = 0;
    for (size_t i = 0; i < n_boxes - 1; ++i) {
        for (size_t j = i + 1; j < n_boxes; ++j) {
            Distance d = {
                .distance = calculate_distance(boxes[i], boxes[j]),
                .box1 = i,
                .box2 = j,
            };
            distances[n_distances++] = d;
        }
    }
    qsort(distances, n_distances, sizeof(*distances), compare_distances);

    Circuit *circuits = malloc(N * sizeof(Circuit));
    size_t n_circuits = 0;
    size_t n_not_connected = n_boxes;
    for (size_t i = 0; i < n_distances; ++i) {
        size_t box1_i = distances[i].box1;
        size_t box2_i = distances[i].box2;
        JunctionBox *box1 = &boxes[box1_i];
        JunctionBox *box2 = &boxes[box2_i];

        // Both boxes are not in any circuit
        if (box1->circuit == N && box2->circuit == N) {
            box1->circuit = n_circuits;
            box2->circuit = n_circuits;
            circuit_init(&circuits[n_circuits]);
            circuit_add(&circuits[n_circuits], box1_i);
            circuit_add(&circuits[n_circuits], box2_i);
            n_circuits++;
            n_not_connected -= 2;
        }
        // One box is in a circuit, other is not
        else if (box1->circuit != N && box2->circuit == N) {
            box2->circuit = box1->circuit;
            circuit_add(&circuits[box1->circuit], box2_i);
            n_not_connected -= 1;
        }
        else if (box1->circuit == N && box2->circuit != N) {
            box1->circuit = box2->circuit;
            circuit_add(&circuits[box2->circuit], box1_i);
            n_not_connected -= 1;
        }
        // Both are in different circuits
        else if (box1->circuit != box2->circuit) {
            size_t circuit_i_mov = box2->circuit;
            for (size_t j = 0; j < circuits[circuit_i_mov].size; ++j) {
                size_t box_i_mov = circuits[circuit_i_mov].boxes[j];
                circuit_add(&circuits[box1->circuit], box_i_mov);
                boxes[box_i_mov].circuit = box1->circuit;
            }
            circuit_free(&circuits[circuit_i_mov]);
        }
        // Both boxes are in the same circuit
        else if (box1->circuit == box2->circuit) { }
        // Not possible
        else { assert(false); }

        n_connections--;
        if (n_connections == 0) {
            size_t max1 = 0, max2 = 0, max3 = 0;
            for (size_t i = 0; i < n_circuits; i++) {
                size_t x = circuits[i].size;
                if (x > max1) {
                    max3 = max2; max2 = max1; max1 = x;
                } else if (x > max2) {
                    max3 = max2; max2 = x;
                } else if (x > max3) {
                    max3 = x;
                }
            }
            solution_part1_ = max1 * max2 * max3;
        }

        if (n_not_connected == 0) {
            solution_part2_ = (uint64_t)box1->x * (uint64_t)box2->x;
        }

        if (solution_part1_ != 0 && solution_part2_ != 0) break;
    }

    free(boxes);
    free(distances);
    for (size_t i = 0; i < n_circuits; ++i) {
        circuit_free(&circuits[i]);
    }
    free(circuits);
    fclose(fp);

    printf("Part 1: %" PRId64 "\n", solution_part1_);
    check_solution(1, file_name, solution_part1_);
    printf("Part 2: %" PRId64 "\n", solution_part2_);
    check_solution(2, file_name, solution_part2_);
}


int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        solve(argv[i]);
    }
    return 0;
}
