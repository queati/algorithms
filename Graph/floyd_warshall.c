/*
 * Floyd-Wallshall algorithm is another dynamic-programming 
 * algorithm to solve the all-pairs shortest path problem
 * on a directed graph G. 
 *
 * The Floyd-Wallshall algorithm considers the intermediate 
 * vertices of a shortest path. For any pair of vertices i, 
 * j, consider all paths from i to j whose intermediate
 * vertices are all drawn from {1, 2, ..., k}. The Floyd
 * algorithm exploits a relationship between path p and 
 * shortest paths from i to j with all intermediate vertices
 * in the set {1, 2, ..., k-1}.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VER_MAX 100

struct Graph {
	int node_num;
	int adjcent_matrix[VER_MAX][VER_MAX];
	int shortest_distance[VER_MAX][VER_MAX];
};

void initGraph(struct Graph *, int);
void input(struct Graph *, int);
void floyd_warshall(struct Graph *);
void output(struct Graph *);

int main(void)
{
	int node_num, edge_num;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		initGraph(&graph, node_num);
		input(&graph, edge_num);
		floyd_warshall(&graph);
		output(&graph);
	}

	return 0;
}

void initGraph(struct Graph *graph, int node_num)
{
	int i, j;

	graph->node_num = node_num;
	for (i = 1; i <= graph->node_num; i++) {
		for (j = 1; j <= graph->node_num; j++) {
			graph->adjcent_matrix[i][j] = INT_MAX;
			graph->shortest_distance[i][j] = INT_MAX;
		}
		graph->adjcent_matrix[i][i] = 0;
		graph->shortest_distance[i][i] = 0;
	}
}

void input(struct Graph *graph, int edge_num)
{
	int i;
	int from, to, weight;

	for (i = 0; i < edge_num; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		graph->adjcent_matrix[from][to] = weight;
		graph->shortest_distance[from][to] = weight;
	}
}

void floyd_warshall(struct Graph *graph)
{
	int i, j, k;
	int dis1, dis2;

	for (k = 1; k <= graph->node_num; k++)
		for (i = 1; i <= graph->node_num; i++)
			for (j = 1; j <= graph->node_num; j++) {
				dis1 = graph->shortest_distance[i][k];
				dis2 = graph->shortest_distance[k][j];
				if (dis1 != INT_MAX && dis2 != INT_MAX && \
					dis1 + dis2 < graph->shortest_distance[i][j])
					graph->shortest_distance[i][j] = dis1 + dis2;
			}
					
}

void output(struct Graph *graph)
{
	int i, j;
	
	printf("The minimum distance matrix is:\n");
	for (i = 1; i<= graph->node_num; i++) {
		for (j = 1; j <= graph->node_num; j++)
			printf("%6d", graph->shortest_distance[i][j]);
		printf("\n");
	}
}
