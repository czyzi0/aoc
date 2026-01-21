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
        {"sample1.txt", 7, 33},
        {"input.txt", 417, 0},
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


#define MAX_VECTOR_SIZE 10

typedef struct {
    uint32_t data[MAX_VECTOR_SIZE];
    size_t size;
} Vector;

bool vector_eq(Vector *v1, Vector *v2) {
    assert(v1->size == v2->size);
    return memcmp(v1->data, v2->data, v1->size * sizeof(uint32_t)) == 0;
}

void vector_xor(Vector *out, Vector *v1, Vector *v2) {
    assert(v1->size == v2->size);
    out->size = v1->size;
    for (size_t i = 0; i < v1->size; ++i) {
        out->data[i] = v1->data[i] ^ v2->data[i];
    }
}

void vector_add(Vector *out, Vector *v1, Vector *v2) {
    assert(v1->size == v2->size);
    out->size = v1->size;
    for (size_t i = 0; i < v1->size; ++i) {
        out->data[i] = v1->data[i] + v2->data[i];
    }
}

uint32_t vector_hash(Vector *v, uint32_t mod) {
    uint32_t hash = 5381;
    for (size_t i = 0; i < v->size; ++i) {
        hash = ((hash << 5) + hash) + v->data[i];
    }
    return hash % mod;
}

// void vector_print(Vector *v) {
//     for (size_t i = 0; i < v->size; ++i) {
//         printf("%" PRIu32 " ", v->data[i]);
//     }
//     printf("\n");
// }


typedef struct {
    Vector *data;
    size_t head, tail;
    size_t count, capacity;
} Queue;

void queue_init(Queue *q, size_t capacity) {
    q->data = malloc(capacity * sizeof(Vector));
    assert(q->data != NULL);

    q->head = q->tail = 0;
    q->count = 0;
    q->capacity = capacity;
}

void queue_free(Queue *q) {
    if (q->data != NULL) free(q->data);
    q->data = NULL;

    q->head = q->tail = 0;
    q->count = 0;
    q->capacity = 0;
}

bool queue_empty(Queue *q) {
    return q->count == 0;
}

bool queue_full(Queue *q) {
    return q->count == q->capacity;
}

void queue_push(Queue *q, Vector *v) {
    assert(!queue_full(q));

    q->data[q->tail] = *v;
    q->tail = (q->tail + 1) % q->capacity;
    q->count++;
}

Vector queue_pop(Queue *q) {
    assert(!queue_empty(q));

    Vector v = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->count--;
    return v;
}


typedef struct HashSetEntry {
    Vector key;
    struct HashSetEntry *next;
} HashSetEntry;

typedef struct {
    HashSetEntry **buckets;
    size_t capacity;
} HashSet;

void hashset_init(HashSet *s, size_t capacity) {
    s->buckets = malloc(capacity * sizeof(HashSetEntry*));
    assert(s->buckets != NULL);
    s->capacity = capacity;
    for (size_t i = 0; i < capacity; ++i) {
        s->buckets[i] = NULL;
    }
}

void hashset_free(HashSet *s) {
    if (s->buckets != NULL) {
        for (size_t i = 0; i < s->capacity; ++i) {
            HashSetEntry *entry = s->buckets[i];
            while (entry != NULL) {
                HashSetEntry *next = entry->next;
                free(entry);
                entry = next;
            }
        }
        free(s->buckets);
        s->buckets = NULL;
    }
    s->capacity = 0;
}

bool hashset_contains(HashSet *s, Vector *v) {
    uint32_t index = vector_hash(v, (uint32_t)s->capacity);
    HashSetEntry *entry = s->buckets[index];
    while (entry != NULL) {
        if (vector_eq(&entry->key, v)) {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

void hashset_insert(HashSet *s, Vector *v) {
    assert(!hashset_contains(s, v));

    uint32_t index = vector_hash(v, (uint32_t)s->capacity);
    HashSetEntry *entry = malloc(sizeof(HashSetEntry));
    assert(entry != NULL);
    entry->key = *v;
    entry->next = s->buckets[index];
    s->buckets[index] = entry;
}


Vector parse_target_part1(char *text) {
    size_t size = (size_t)(strlen(text) - 2);
    assert(size <= MAX_VECTOR_SIZE);

    Vector target = { .size = size };
    for (size_t i = 0; i < target.size; ++i) {
        switch (text[i + 1]) {
        case '#':
            target.data[i] = 1U;
            break;
        case '.':
            target.data[i] = 0U;
            break;
        default:
            assert(false);
        }
    }
    return target;
}

Vector parse_button(char *text, size_t size) {
    Vector button = { .size = size };
    char *ptr = text + 1;
    char *end;
    while (*ptr != ')') {
        button.data[(size_t)strtol(ptr, &end, 10)] = 1U;
        if (*end == ',') end++;
        ptr = end;
    }
    return button;
}

Vector parse_target_part2(char *text, size_t size) {
    Vector target = { .size = size };
    size_t i = 0;
    char *ptr = text + 1;
    char *end;
    while (*ptr != '}') {
        target.data[i++] = (uint32_t)strtol(ptr, &end, 10);
        if (*end == ',') end++;
        ptr = end;
    }
    return target;
}

#define MAX_QUEUE_SIZE 1024
#define MAX_HASHSET_SIZE 2048

size_t bfs(Vector *target, Vector buttons[], size_t n_buttons) {
    Queue q;
    queue_init(&q, MAX_QUEUE_SIZE);

    HashSet visited;
    hashset_init(&visited, MAX_HASHSET_SIZE);

    Vector start = {0};
    start.size = target->size;

    queue_push(&q, &start);
    hashset_insert(&visited, &start);

    for (size_t depth = 0; !queue_empty(&q); ++depth) {
        size_t depth_count = q.count;
        for (size_t k = 0; k < depth_count; ++k) {
            Vector current = queue_pop(&q);

            if (vector_eq(&current, target)) {
                queue_free(&q);
                hashset_free(&visited);
                return depth;
            }

            for (size_t i = 0; i < n_buttons; ++i) {
                Vector next;
                vector_xor(&next, &current, &buttons[i]);

                if (!hashset_contains(&visited, &next)) {
                    hashset_insert(&visited, &next);
                    queue_push(&q, &next);
                }
            }
        }
    }

    assert(false);
}

#define MAX_BUFF 256
#define MAX_BUTTONS 24

void solve(char *file_path) {
    char *file_name = strrchr(file_path, '/') + 1;
    printf("### %s ###\n", file_name);

    uint32_t solution_part1_ = 0;
    // uint32_t solution_part2_ = 0;

    FILE *fp = fopen(file_path, "r");
    assert(fp);

    char buff[MAX_BUFF];

    Vector target_part1;
    // Vector target_part2;
    Vector buttons[MAX_BUTTONS];
    size_t n_buttons;

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        assert(buff[strlen(buff) - 1] == '\n');

        n_buttons = 0;

        char *tok = strtok(buff, " ");
        while (tok) {
            if (tok[0] == '[') {
                target_part1 = parse_target_part1(tok);
            } else if (tok[0] == '(') {
                buttons[n_buttons++] = parse_button(tok, target_part1.size);
            // } else if (tok[0] == '{') {
            //     target_part2 = parse_target_part2(tok, target_part1.size);
            // } else {
            //     assert(false);
            }
            tok = strtok(NULL, " ");
        }

        solution_part1_ += bfs(&target_part1, buttons, n_buttons);

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
