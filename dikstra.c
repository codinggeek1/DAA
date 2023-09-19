#include <stdio.h>
#include <stdlib.h>

#define INFINITY 9999

void Dijkstra(int** Graph, int n, int start) {
    int* distance = (int*)malloc(n * sizeof(int));
    int* pred = (int*)malloc(n * sizeof(int));
    int* visited = (int*)malloc(n * sizeof(int));
    int count, mindistance, nextnode, i, j;

    // Initialize the cost matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (Graph[i][j] == 0) {
                Graph[i][j] = INFINITY;
            }
        }
    }

    for (i = 0; i < n; i++) {
        distance[i] = Graph[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;
    mindistance = INFINITY;

    while (count < n - 1) {
        mindistance = INFINITY;

        for (i = 0; i < n; i++) {
            if (distance[i] < mindistance && !visited[i]) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++) {
            if (!visited[i] && mindistance + Graph[nextnode][i] < distance[i]) {
                distance[i] = mindistance + Graph[nextnode][i];
                pred[i] = nextnode;
            }
        }
        count++;
    }

    // Printing the distance
    for (i = 0; i < n; i++) {
        if (i != start) {
            printf("\nDistance from source to %d: %d", i, distance[i]);
        }
    }

    // Free allocated memory
    free(distance);
    free(pred);
    free(visited);
}

int main() {
    int i, j, n, u;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int** Graph = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        Graph[i] = (int*)malloc(n * sizeof(int));
    }

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &Graph[i][j]);
        }
    }

    printf("Enter the starting node: ");
    scanf("%d", &u);

    Dijkstra(Graph, n, u);

    // Free allocated memory
    for (i = 0; i < n; i++) {
        free(Graph[i]);
    }
    free(Graph);

    return 0;
}
