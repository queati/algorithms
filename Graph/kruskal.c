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

#define VER_MAX 100
#define EDG_MAX 1000

struct Edge {
	int from;
	int to;
	int weight;
};

struct Tree {
	int node_num;
	int edge_num;
	struct Edge edge[EDG_MAX];
};

void make_set(int, int *);
int find_set(int, int *);
void union_set(int, int, int *);
void input(int, int, struct Tree *, int *);
int kruskal(struct Tree *, int *);
void quickSort(struct Edge *, int, int);
int partition(struct Edge *, int, int);
void copyEdge(struct Edge *, struct Edge *);

int main(void)
{
	int node_num, edge_num;
	int ans;
	int set[VER_MAX];
	struct Tree tree;

	while (scanf("%d %d", &node_num, &edge_num) != EOF) {
		input(node_num, edge_num, &tree, set);
		ans = kruskal(&tree, set);
		printf("The weight of minimum spanning tree is %d\n", ans);
	}

	return 0;
}

void input(int node_num, int edge_num, struct Tree *tree, int *set)
{
	int i;
	int from, to, weight;

	tree->node_num = node_num;
	tree->edge_num = edge_num;
	for (i = 1; i <= edge_num; i++) {
		scanf("%d %d %d", &from, &to, &weight);
		tree->edge[i].from = from;
		tree->edge[i].to = to;
		tree->edge[i].weight = weight;
	}
	for (i = 1; i <= node_num; i++)
		make_set(i, set);
}

int kruskal(struct Tree *tree, int *set)
{
	int i, j;
	int ans;

	ans = 0;

	quickSort(tree->edge, 1, tree->edge_num);
	for (i = 1, j = 1; i < tree->node_num; i++) {
		while (find_set(tree->edge[j].from, set) == \
				find_set(tree->edge[j].to, set))
			j++;
		union_set(tree->edge[j].from, tree->edge[j].to, set);
		ans += tree->edge[j].weight;
		printf("choose edge from %d to %d\n", tree->edge[j].from, \
											tree->edge[j].to);
		j++;
	}
	return ans;
}

void quickSort(struct Edge *edge, int low, int high)
{
	int pos;

	if (low >= high)
		return ;
	pos = partition(edge, low, high);
	quickSort(edge, low, pos - 1);
	quickSort(edge, pos + 1, high);
}

int partition(struct Edge *edge, int low, int high)
{
	int i, j;
	struct Edge tmp;

	i = low;
	j = high;
	copyEdge(&edge[i], &tmp);
	while (i < j) {
		while (i < j && edge[j].weight >= tmp.weight)
			j--;
		copyEdge(&edge[j], &edge[i]);
		while (i < j && edge[i].weight <= tmp.weight)
			i++;
		copyEdge(&edge[i], &edge[j]);
	}
	copyEdge(&tmp, &edge[i]);
	return i;
}

void copyEdge(struct Edge *src, struct Edge *dst)
{
	dst->from = src->from;
	dst->to= src->to;
	dst->weight = src->weight;
}

void make_set(int pos, int *set)
{
	set[pos] = pos;
}

int find_set(int pos, int *set)
{
	int ans;

	ans = pos;
	while (ans != set[ans])
		ans = set[ans];
	return ans;
}

void union_set(int pos1, int pos2, int *set)
{
	int i, j;

	i = find_set(pos1, set);
	j = find_set(pos2, set);

	if (i != j)
		set[i] = j;
}
