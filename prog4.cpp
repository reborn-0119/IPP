#include <iostream>
#include <omp.h>
using namespace std;

#define V 9
int minDistance(int dist[], bool sptSet[]){
	
	int min = INT_MAX, min_index = -1;
	
	#pragma omp parallel
	{
		int local_min = INT_MAX;
		int local_index = -1;
		
		#pragma omp for nowait
		for(int v = 0; v < V; v++ ){
			if (!sptSet[v] && dist[v] <= local_min){
				local_min = dist[v];
				local_index = v;
			}
		}
		#pragma omp critical
		{
			if(local_min < min){
				min = local_min;
				min_index = local_index;
			}
		}
	}
	
	return min_index;
}

void dijkstra(int graph[V][V], int src){
	int dist[V];
	bool sptSet[V];
	
	for(int i = 0; i < V; i++){
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}
	
	dist[src] = 0;
	
	
	for(int count = 0 ; count < V-1 ; count++){
		
		int u = minDistance(dist, sptSet);
		if(u == -1) break;
		
		sptSet[u] = true;
		
		#pragma omp parallel for
		for( int v = 0; v < V; v++){
			if(!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
				dist[v] = dist[u] + graph[u][v];
			}
		}
		
	}
	
	for (int i = 0; i < V; i++){
		cout<< i << "\t\t"<<dist[i]<<endl;
	}
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0);
    return 0;
}
