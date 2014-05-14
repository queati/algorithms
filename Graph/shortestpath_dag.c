/*
 * This is a implemention of single-source shortest path in
 * directed acyclic graphs. By relaxing the edges of a 
 * weighted dag G = (V, E) according to a topological sort 
 * of its vertices, we can compute shortest paths from a 
 * single source in O(V + E) time.
 * 
 * This algorithm can only used in directed acyclic graphs.
 * 
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
	int precusor;
	int dis;
	int start_time;
	int end_time;
	char visited;
	struct Edge *start;
};

struct Graph {
	int node_num;
	struct Node node[VER_MAX];
};

void initGraph(struct Graph *, int, int *);
void input(struct Graph *, int);
void shortestPath(struct Graph *, int);
void output(struct Graph *, int);
void dfs(struct Graph *, int);
void quickSort(struct Node *, int, int);
int partition(struct Node *, int, int);
void copyNode(struct Node *, struct Node *);
int relax(struct Graph *, int, struct Edge *);

int time;

int main(void)
{
	int node_num, edge_num, src_no;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		initGraph(&graph, node_num, &src_no);
		input(&graph, edge_num);
		shortestPath(&graph, src_no);
		output(&graph, src_no);
	}

	return 0;
}

void initGraph(struct Graph *graph, int node_num, int *src_no)
{
	int i;

	time = 0;
	graph->node_num = node_num;
	*src_no = 1;
	for (i = 2; i <= node_num; i++) {
		graph->node[i].start = NULL;
		graph->node[i].dis = INT_MAX;
		graph->node[i].precusor = -1;
		graph->node[i].visited = 'N';
	}
	graph->node[*src_no].start = NULL;
	graph->node[*src_no].dis = 0;
	graph->node[*src_no].precusor = *src_no;
	graph->node[*src_no].visited = 'N';
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

void shortestPath(struct Graph *graph, int src_no)
{
	int i, j;
	struct Edge *edge;

	for (i = 1; i <= graph->node_num; i++)
		if (graph->node[i].visited == 'N')
			dfs(graph, src_no);

	quickSort(graph->node, 1, graph->node_num);
	for (j = 1; j <= graph->node_num; j++) {
		edge = graph->node[j].start;
		while (edge) {
			relax(graph, j, edge);
			edge = edge->next;
		}
	}
}

void dfs(struct Graph *graph, int node_no)
{
	struct Edge *edge;

	if (graph->node[node_no].visited == 'Y')
		return ;
	graph->node[node_no].start_time = time++;
	graph->node[node_no].visited = 'Y';
	edge = graph->node[node_no].start;
	while (edge) {
		dfs(graph, edge->to);
		edge = edge->next;
	}
	graph->node[node_no].end_time = time++;
}

void quickSort(struct Node *node, int low, int high)
{
	int pos;

	if (low >= high)
		return ;
	pos = partition(node, low, high);
	quickSort(node, low, pos - 1);
	quickSort(node, pos + 1, high);
}

int partition(struct Node *node, int low, int high)
{
	int i, j;
	struct Node tmp;

	copyNode(&node[low], &tmp);
	i = low;
	j = high;
	while (i < j) {
		while (i < j && node[j].end_time <= tmp.end_time)
			j--;
		copyNode(&node[j], &node[i]);
		while (i < j && node[i].end_time >= tmp.end_time)
			i++;
		copyNode(&node[i], &node[j]);
	}
	copyNode(&tmp, &node[i]);
	return i;
}

void copyNode(struct Node *src, struct Node *dst)
{
	dst->dis = src->dis;
	dst->precusor = src->precusor;
	dst->start_time = src->start_time;
	dst->end_time = src->end_time;
	dst->start = src->start;
	dst->visited = src->visited;
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

void output(struct Graph *graph, int src_no)
{
	int i, j;

	printf("The source node is :%d\n", src_no);
	for (i = 1; i <= graph->node_num; i++) {
		if (graph->node[i].dis == INT_MAX) {
			printf("Node %d, unreachable\n", i);
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

