/*
 * The Bellman-Ford algorithm solves the single-source shortest-paths
 * problem in the general case in which edge weights may be negative.
 * Given a weighted, directed graph G = (V, E) with source s and 
 * weight function w: E->R, the Bellman-Ford algorithm returns a 
 * boolean value indicating whether or not there is a negative-weight
 * cycle that is reachable from the source. If there is such a cycle,
 * the algorithm indicates that no solution exists. If there is no
 * such cycle, the algorithm produces the shortest paths and their 
 * weights.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VER_MAX 100

struct Edge {
	int to;
	int weight;
	struct Edge *next;
};

struct Node {
	int dis;
	int precusor;
	struct Edge *start;
};

struct Graph {
	int node_num;
	struct Node node[VER_MAX];
};

void initGraph(struct Graph *, int, int *);
void input(struct Graph *, int);
int bellman_ford(struct Graph *, int);
void output(struct Graph *, int, int);
int relax(struct Graph *, int, struct Edge *);

int main(void)
{
	int node_num, edge_num, src_no;
	int ans;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		initGraph(&graph, node_num, &src_no);
		input(&graph, edge_num);
		ans = bellman_ford(&graph, src_no);
		output(&graph, src_no, ans);
	}

	return 0;
}

void initGraph(struct Graph *graph, int node_num, int *src_no)
{
	int i;

	graph->node_num = node_num;
	*src_no = 1;
	for (i = 2; i <= node_num; i++) {
		graph->node[i].start = NULL;
		graph->node[i].dis = INT_MAX;
		graph->node[i].precusor = -1;
	}
	graph->node[*src_no].start = NULL;
	graph->node[*src_no].dis = 0;
	graph->node[*src_no].precusor = *src_no;
}

void input(struct Graph *graph, int edge_num)
{
	int i;
	int from, to, weight;
	struct Edge *edge;

	for (i = 0; i < edge_num; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		if (!(edge = (struct Edge *)malloc(sizeof(struct Edge))))
			exit(1);
		edge->to = to;
		edge->weight = weight;
		edge->next = graph->node[from].start;
		graph->node[from].start = edge;
	}
}

int bellman_ford(struct Graph *graph, int src_no)
{
	int i, j;
	int ans;
	struct Edge *edge;

	for (i = 1; i < graph->node_num; i++)
		for (j = 1; j <= graph->node_num; j++) {
			edge = graph->node[j].start;
			if (graph->node[j].dis == INT_MAX)
				continue;
			while (edge) {
				relax(graph, j, edge);
				edge = edge->next;
			}
		}

	for (j = 1; j <= graph->node_num; j++) {
		edge = graph->node[j].start;
		while (edge) {
			if (relax(graph, j, edge))
				return 0;
			edge = edge->next;
		}
	}
	return 1;
}

int relax(struct Graph *graph, int from, struct Edge *edge)
{
	int to, weight;

	to = edge->to;
	weight = edge->weight;
	if (graph->node[from].dis == INT_MAX || \
		graph->node[from].dis + weight >= graph->node[to].dis)
		return 0;
	graph->node[to].dis = graph->node[from].dis + weight;
	graph->node[to].precusor = from;
	return 1;
}

void output(struct Graph *graph, int src_no, int ans)
{
	int i, j;

	if (!ans) {
		printf("There are some negative-weight circle in the Graph\n");
		return ;
	}

	printf("The source node is %d:\n", src_no);
	for (i = 1; i <= graph->node_num; i++) {
		if (graph->node[i].dis == INT_MAX) {
			printf("Node %d, unreachable\n",i);
			continue;
		}
		printf("Node %d, distance %d: ", i, graph->node[i].dis);
		j = i;
		while (j != src_no) {
			printf("%d<-", j);
			j = graph->node[j].precusor;
		}
		printf("%d\n", src_no);
	}
}

