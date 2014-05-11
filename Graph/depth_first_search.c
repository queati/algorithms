/*
 * Depth-first search is another simplest algorithms for 
 * searching a graph. Given a graph G = (V, E) and a source
 * vertex s, DFS explores edges out of the most recently 
 * discovered vertex v that still has unexplored edges
 * leaving it.
 * Input: the number of vertexs N and the number of edges E
 * 		  then E lines, each line has two numbers a, b, 
 * 		  represent a edge from a to b
 * Output: Assume vertex 1 is the source node, output the 
 *		   vertex with the BFS procedure.
 */

#include <stdio.h>
#include <stdlib.h>

#define VER_MAX 100

struct Edge {
	int to;
	struct Edge *next;
};

struct Node {
	int from;
	char visited;
	struct Edge *start;
};

struct Graph {
	int node_num;
	struct Node node[VER_MAX];
};

void input(struct Graph *, int, int);
void dfs(struct Graph *, int);

int main(void)
{
	int node_num, edge_num;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		input(&graph, node_num, edge_num);
		dfs(&graph, 1);
	}
	
	return 0;
}

void input(struct Graph *graph, int node_num, int edge_num)
{
	int i;
	int from, to;
	struct Edge *edge;

	graph->node_num = node_num;
	for (i = 1; i <= node_num; i++) {
		graph->node[i].from = i;
		graph->node[i].visited = 'n';
		graph->node[i].start = NULL;
	}
	for (i = 0; i < edge_num; i++) {
		scanf("%d %d", &from, &to);
		if (!(edge = (struct Edge *)malloc(sizeof(struct Edge))))
			exit(1);
		edge->to = to;
		edge->next = graph->node[from].start;
		graph->node[from].start = edge;
	}
}

void dfs(struct Graph *graph, int node)
{
	int i;
	struct Edge *edge;

	if (node > graph->node_num || graph->node[node].visited == 'y')
		return ;

	printf("visit node %d\n", node);
	graph->node[node].visited = 'y';
	for (edge = graph->node[node].start; edge != NULL; edge = edge->next)
		dfs(graph, edge->to);
}
