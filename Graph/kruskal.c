/*
 * Assume that we have a connected, undirected graph G = (V, E)
 * with a weight function w: E -> R, and we wish to find a 
 * minimum spanning tree for G. 
 * The greedy strategy is grows the minimum spanning tree one
 * edge at a time. At each step, we determine an edge (u, v)
 * that we can add to A that A + {(u, v)} is a subset of some
 * minimum spanning tree. We call such an edge a safe edge for A
 * There are two ways to determine a safe edge. Kruskal is one of 
 * them. Kruskal's algorithm finds a safe edge to add to the 
 * growing forest by finding of all the edges that connect any 
 * two trees in the forest, an edge (u, v) of least weight.
 */

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "minimum_spanning_tree.h"

struct EdgeInfo { 
	int from;
	int to;
	double weight;
};

struct AllEdge {
	int edge_num;
	struct EdgeInfo edges[EDG_MAX];
};
	
extern void myqSort(void *base, size_t num, size_t width, \
					int64_t (*cmp)(const void *, const void *));
extern void chooseEdge(struct Graph *, int, int);


void initAllEdge(struct AllEdge *allEdge)
{
	allEdge->edge_num = 0;
}

void findAllEdge(struct Graph *graph, struct AllEdge *allEdge)
{
	int i;
	struct Edge *edge; 
	struct EdgeInfo edgeInfo;

	for (i = 1; i <= graph->node_num; i++) {
		edge = graph->node[i].start;
		while (edge) {
			if (i < edge->to) {
				edgeInfo.from = i;
				edgeInfo.to = edge->to;
				edgeInfo.weight = edge->weight;
				allEdge->edges[allEdge->edge_num++] = edgeInfo;
			}
			edge = edge->next;
		}
	}
}

int64_t compare(const void *elem1, const void *elem2)
{
	return ((struct EdgeInfo *)elem1)->weight - \
			((struct EdgeInfo *)elem2)->weight;
}

void makeSet(int pos, int *set)
{
	set[pos] = pos;
}

int findSet(int pos, int *set)
{
	while (pos != set[pos])
		pos = set[pos];

	return pos;
}

void unionSet(int pos1, int pos2, int *set)
{
	set[pos1] = findSet(pos2, set);
}

void initMakeSet(struct Graph *graph, int *set)
{
	int i;

	for (i = 1; i <= graph->node_num; i++)
		makeSet(i, set);
}

void kruskal(struct Graph *graph)
{
	int i, j;
	int set[VER_MAX];
	struct AllEdge allEdge;

	initAllEdge(&allEdge);
	findAllEdge(graph, &allEdge);
	initMakeSet(graph, set);
	myqSort(allEdge.edges, allEdge.edge_num, sizeof(struct EdgeInfo), compare);

	for (i = 1, j = 0; i < graph->node_num && j < allEdge.edge_num; i++) {
		while (findSet(allEdge.edges[j].from, set) == \
				findSet(allEdge.edges[j].to, set))
			j++;
		chooseEdge(graph, allEdge.edges[j].from, allEdge.edges[j].to);
		unionSet(allEdge.edges[j].from, allEdge.edges[j].to, set);
	}
}
	
