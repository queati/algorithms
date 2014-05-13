/*
 * Prim is another algorithm for minimum spanning tree. Each step adds
 * to the tree A a light edge that connects A to an isolated vertex--
 * one on which no edge of A is incident.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LEFT(a)		(2 * (a) + 1)
#define RIGHT(a)	(2 * (a) + 2)
#define PRT(a) 		(((a) - 1) / 2)
#define VER_MAX 100

struct Edge {
	int to;
	int weight;
	struct Edge *next;
};

struct Node {
	int from;
	struct Edge *start;
};

struct Graph {
	int node_num;
	struct Node node[VER_MAX];
};

struct Heap_node {
	int weight;
	int no;
};

struct Heap {
	int heap_size;
	struct Heap_node heap_node[VER_MAX];
};

void initHeap(struct Heap *, struct Graph *);
void createHeap(struct Heap *);
void heapify(struct Heap *, int);
void exchange(struct Heap_node *, struct Heap_node *);
struct Heap_node *extractMin(struct Heap *);
void decrease_key(struct Heap *, int, int);
void input(struct Graph *, int, int);
int prim(struct Graph *);

int main(void)
{
	int node_num, edge_num;
	int ans;
	struct Graph graph;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		input(&graph, node_num, edge_num);
		ans = prim(&graph);
		printf("The weight of minimum spanning tree is %d\n", ans);
	}

	return 0;
}

void input(struct Graph *graph, int node_num, int edge_num)
{
	int i;
	int from, to, weight;
	struct Edge *edge;

	graph->node_num = node_num;
	for (i = 0; i < node_num; i++)
		graph->node[i].start = NULL;
	for (i = 0; i < edge_num; i++) {
		scanf("%d %d %d", &from , &to, &weight);
		if (!(edge = (struct Edge *)malloc(sizeof(struct Edge))))
			exit(1);
		edge->to = to - 1;
		edge->weight = weight;
		edge->next = graph->node[from - 1].start;
		graph->node[from - 1].start = edge;
		if (!(edge = (struct Edge *)malloc(sizeof(struct Edge))))
			exit(1);
		edge->to = from - 1;
		edge->weight = weight;
		edge->next = graph->node[to - 1].start;
		graph->node[to - 1].start = edge;

	}
}

int prim(struct Graph *graph)
{
	int ans;
	struct Heap_node *minNode;
	struct Heap heap;
	struct Edge *edge;

	ans = 0;
	initHeap(&heap, graph);
	createHeap(&heap);
	while (heap.heap_size != 0) {
		minNode = extractMin(&heap);
		ans += minNode->weight;
		printf("choose vertex %d, corresponging edge weight \
		%d\n", minNode->no, minNode->weight);
		edge = graph->node[minNode->no].start;
		while (edge) {
			decrease_key(&heap, edge->to, edge->weight);
			edge = edge->next;
		}
for (int i = 0; i < heap.heap_size; i++)
	printf("node %d, weight %d\n", heap.heap_node[i].no, heap.heap_node[i].weight);
	}
	return ans;
}

void initHeap(struct Heap *heap, struct Graph *graph)
{
	int i;
	int source;
	struct Edge tmp;

	source = 0;
	heap->heap_size = graph->node_num;
	for (i = 1; i < graph->node_num; i++) {
		heap->heap_node[i].weight = INT_MAX;
		heap->heap_node[i].no = i;
	}
	heap->heap_node[source].no = source;
	heap->heap_node[source].weight = 0;
}

void createHeap(struct Heap *heap)
{
	int i;
	
	for (i = PRT(heap->heap_size - 1); i >= 0; i--)
		heapify(heap, i);
}

// if macro PRT() safe? 
void heapify(struct Heap *heap, int pos)
{
	int pmin;	

	if (heap->heap_size <= 1)
		return ;
	while (pos <= PRT(heap->heap_size - 1)) {
		pmin = LEFT(pos);
		if (RIGHT(pos) < heap->heap_size && \
			heap->heap_node[RIGHT(pos)].weight < heap->heap_node[pmin].weight)
			pmin++;
		if (heap->heap_node[pos].weight <= heap->heap_node[pmin].weight)
			return ;
		exchange(&heap->heap_node[pos], &heap->heap_node[pmin]);
		pos = pmin;
	}
}

struct Heap_node *extractMin(struct Heap *heap)
{
	exchange(&heap->heap_node[0], &heap->heap_node[heap->heap_size - 1]);
	(heap->heap_size)--;
	heapify(heap, 0);
	return &heap->heap_node[heap->heap_size];
}

void exchange(struct Heap_node *node1, struct Heap_node *node2)
{
	struct Heap_node tmp;

	tmp = *node1;
	*node1 = *node2;
	*node2 = tmp;
}

void decrease_key(struct Heap *heap, int node, int weight)
{
	int i;
	int pos, parent;

	pos = -1;
	for (i = 0; i < heap->heap_size; i++)
		if (heap->heap_node[i].no == node)
			pos = i;

	if (pos == -1 || heap->heap_node[pos].weight <= weight)
		return ;
	heap->heap_node[pos].weight = weight;
	while (pos > 0) {
		parent = PRT(pos);
		if (heap->heap_node[pos].weight >= heap->heap_node[parent].weight)
			return ;
		exchange(&heap->heap_node[pos], &heap->heap_node[parent]);
		pos = parent;
	}
}
