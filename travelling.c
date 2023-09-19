#include <stdio.h>
#include <limits.h>

#define V 4

int travllingSalesmanProblem(int graph[V][V], int s, int path[V]);
void swap(int *x, int *y);
void permute(int *array, int start, int end, int graph[V][V], int source, int *min_path, int path[V]);

int main() {
    // Matrix representation of the graph
    int graph[V][V] = {{0, 10, 15, 20},
                      {10, 0, 35, 25},
                      {15, 35, 0, 30},
                      {20, 25, 30, 0}};
    int s = 0;
    int path[V];
    int min_path = travllingSalesmanProblem(graph, s, path);

    printf("TSP Path: ");
    for (int i = 0; i < V; i++) {
        printf("%d -> ", path[i]);
    }
    printf("%d\n", path[0]); // Return to the starting point
    printf("Minimum Weight: %d\n", min_path);
    
    return 0;
}

int travllingSalesmanProblem(int graph[V][V], int s, int path[V]) {
    int vertex[V - 1];
    int count = 0;
    for (int i = 0; i < V; i++) {
        if (i != s) {
            vertex[count] = i;
            count++;
        }
    }

    int min_path = INT_MAX;
    permute(vertex, 0, V - 2, graph, s, &min_path, path);

    return min_path;
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int *array, int start, int end, int graph[V][V], int source, int *min_path, int path[V]) {
    if (start == end) {
        int current_pathweight = 0;
        int k = source;

        for (int i = 0; i <= end; i++) {
            current_pathweight += graph[k][array[i]];
            k = array[i];
        }
        current_pathweight += graph[k][source];

        if (current_pathweight < *min_path) {
            *min_path = current_pathweight;
            // Copy the path to 'path' array
            path[0] = source;
            for (int i = 0; i <= end; i++) {
                path[i + 1] = array[i];
            }
        }
    } else {
        for (int i = start; i <= end; i++) {
            swap((array + start), (array + i));
            permute(array, start + 1, end, graph, source, min_path, path);
            swap((array + start), (array + i)); // backtrack
        }
    }
}