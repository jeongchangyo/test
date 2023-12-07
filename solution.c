#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1001
#define INF 987654321

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

typedef struct Graph {
    int vertices;
    int** matrix;
} Graph;

void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (q->front == NULL) {
        return -1; // Queue is empty
    }

    int data = q->front->data;
    Node* temp = q->front;

    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
    }

    free(temp);
    return data;
}

void dfs(int v, int* visited, Graph* graph) {
    printf("%d ", v);
    visited[v] = 1;

    for (int i = 1; i <= graph->vertices; ++i) {
        if (graph->matrix[v][i] == 1 && !visited[i]) {
            dfs(i, visited, graph);
        }
    }
}

void bfs(int v, int* visited, Graph* graph) {
    Queue q;
    initQueue(&q);

    printf("%d ", v);
    visited[v] = 1;
    enqueue(&q, v);

    while (q.front != NULL) {
        int current = dequeue(&q);

        for (int i = 1; i <= graph->vertices; ++i) {
            if (graph->matrix[current][i] == 1 && !visited[i]) {
                printf("%d ", i);
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
}

int main() {
    int N, M, V;
    scanf("%d %d %d", &N, &M, &V);

    // Initialize the graph
    Graph graph;
    graph.vertices = N;
    graph.matrix = (int**)malloc((N + 1) * sizeof(int*));
    for (int i = 0; i <= N; ++i) {
        graph.matrix[i] = (int*)malloc((N + 1) * sizeof(int));
        for (int j = 0; j <= N; ++j) {
            graph.matrix[i][j] = 0;
        }
    }

    // Build the graph
    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph.matrix[a][b] = 1;
        graph.matrix[b][a] = 1;
    }

    // Initialize visited array
    int* visited = (int*)malloc((N + 1) * sizeof(int));
    for (int i = 0; i <= N; ++i) {
        visited[i] = 0;
    }

    // DFS
    dfs(V, visited, &graph);
    printf("\n");

    // Reset visited array
    for (int i = 0; i <= N; ++i) {
        visited[i] = 0;
    }

    // BFS
    bfs(V, visited, &graph);
    printf("\n");

    // Free allocated memory
    for (int i = 0; i <= N; ++i) {
        free(graph.matrix[i]);
    }
    free(graph.matrix);
    free(visited);

    return 0;
}