/*
 * This algorithm use dynamic-programming for the all-pairs 
 * shortest paths problem on a directed graph G = (V, E).
 * For the all-pairs shortest paths problem , we can prove
 * that all subpaths of a shortest path are shortest paths.
 *
 * Let lij(m) be the minimum weight of any path from vertex
 * i to vertex that contains at most m edges. 
 * So, what we need to know is how to get lij(m) from lij(m-1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VER_MAX 100

struct Graph {
	int node_num;
	int adjcent_matrix[VER_MAX][VER_MAX];
	int shortest_matrix[VER_MAX][VER_MAX];
};

void initGraph(struct Graph *, int);
void input(struct Graph *, int);
void allpair_spath(struct Graph *);
void output(struct Graph *);
void extend_shortest_path(struct Graph *);

int main(void)
{
	int node_num, edge_num;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		initGraph(&graph, node_num);
		input(&graph, edge_num);
		allpair_spath(&graph);
		output(&graph);
	}

	return 0;
}

void initGraph(struct Graph *graph, int node_num)
{
	int i, j;

	graph->node_num = node_num;
	for (i = 1; i <= node_num; i++) {
		for (j = 1; j <= node_num; j++) {
			graph->adjcent_matrix[i][j] = INT_MAX;
			graph->shortest_matrix[i][j] = INT_MAX;
		}
		graph->adjcent_matrix[i][i] = 0;
		graph->shortest_matrix[i][i] = 0;
	}
}

void input(struct Graph *graph, int edge_num)
{
	int i;
	int from, to, weight;

	for (i = 0; i < edge_num; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		graph->adjcent_matrix[from][to] = weight;
		graph->shortest_matrix[from][to] = weight;
	}
}

void allpair_spath(struct Graph *graph)
{
	int i;

	for (i = 2; i < graph->node_num; i++)
		extend_shortest_path(graph);
}

void extend_shortest_path(struct Graph *graph)
{
	int i, j, k;
	int min;

	for (i = 1; i <= graph->node_num; i++)
		for (j = 1; j <= graph->node_num; j++) {
			min = INT_MAX;
			for (k = 1; k <= graph->node_num; k++)
				if (graph->adjcent_matrix[k][j] != INT_MAX &&\
					graph->shortest_matrix[i][k] != INT_MAX &&\
				graph->adjcent_matrix[k][j] + graph->shortest_matrix[i][k]\
				< min)
					min = graph->adjcent_matrix[k][j] +\
							graph->shortest_matrix[i][k];
			graph->shortest_matrix[i][j] = min;
		}
}

void output(struct Graph *graph)
{
	int i, j;

	printf("The minimum distance matrix is:\n");
	for (i = 1; i <= graph->node_num; i++) {
		for (j = 1; j <= graph->node_num; j++) {
			printf(" %6d ", graph->shortest_matrix[i][j]);
		}
		printf("\n");
	}
}
