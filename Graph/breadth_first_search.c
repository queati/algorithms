/*
 * Breadth-first search is one of the simplest algorithms for 
 * searching a graph. Given a graph G = (V, E) and a source
 * vertex s, BFS systematically explores the edges of G to 
 * discover every vertex that is reachable from already found
 * vertex set S and not have been visited. 
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

struct Queue {
	int queue[VER_MAX];
	int size;
	int head;
	int tail;
};

void input(struct Graph *, struct Queue *, int, int);
void bfs(struct Graph *, struct Queue *, int);

int main(void)
{
	int node_num, edge_num;
	struct Queue queue;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		input(&graph, &queue, node_num, edge_num);
		bfs(&graph, &queue, 1);
	}
	
	return 0;
}

void input(struct Graph *graph, struct Queue *queue, \
					int node_num, int edge_num)
{
	int i;
	int from, to;
	struct Edge *edge;

	queue->size = node_num;
	queue->head = queue->tail = 0;
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

void bfs(struct Graph *graph, struct Queue *queue, int node)
{
	int i, cur;
	struct Edge *edge;

	if (node > graph->node_num || graph->node[node].visited == 'y')
		return ;

	queue->queue[(queue->tail)++] = node;
	while (queue->head != queue->tail) {
		cur = queue->queue[(queue->head)++];
		printf("visit node %d\n", cur);
		graph->node[cur].visited = 'y';
		for (edge = graph->node[cur].start; edge != NULL; \
				edge = edge->next)
			if (graph->node[edge->to].visited == 'n')
				queue->queue[(queue->tail)++] = edge->to;
	}
}
