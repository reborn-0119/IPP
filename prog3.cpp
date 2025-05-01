#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

using namespace std;

#define SIZE 700  

void generateTreeGraph(int graph[SIZE][SIZE]) {
    int childrenPerNode = 10;

    #pragma omp parallel for schedule(static)
    for (int i = 0; i < SIZE; i++) {
        int startChild = i * childrenPerNode + 1;
        int endChild = min(startChild + childrenPerNode, SIZE);

        for (int child = startChild; child < endChild; child++) {
            graph[i][child] = 1;
            graph[child][i] = 1;
        }
    }
}

void BFS(int graph[SIZE][SIZE], int start) {
    vector<bool> visited(SIZE, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Order: ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Collect neighbors to process in parallel
        vector<int> neighbors;
        for (int i = 0; i < SIZE; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                neighbors.push_back(i);
            }
        }

        // Parallel processing of neighbors
        #pragma omp parallel
        {
            vector<int> local_queue;
            #pragma omp for
            for (size_t i = 0; i < neighbors.size(); ++i) {
                int neighbor = neighbors[i];
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        local_queue.push_back(neighbor);
                    }
                }
            }

            // Merge local queues into global queue
            #pragma omp critical
            {
                for (int n : local_queue) {
                    q.push(n);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int graph[SIZE][SIZE] = {0};

    generateTreeGraph(graph); 

    cout << "BFS starting from node 0:\n";
    BFS(graph, 0);

    return 0;
}
