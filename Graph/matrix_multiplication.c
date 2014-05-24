/*
 * This program use a dynamic-programming algorithm for the all-pairs
 * shortest paths problem on a directed graph G = (V, E).
 * As we know, all subpaths of a shortest path are shortest paths, and
 * the shortest path from a vertex to another vertex have at most |V-1|
 * Edges.
 * Using the idea of dynamic programming, we can consider the problem of
 * shortest path contains at most i edges each time.(0 <= i <= |V - 1|)
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "macros.h"
#include "all_pairs_shortest_path.h"

void extend_edge(struct Matrix_Graph *);

void matrix_mult(struct Matrix_Graph *mat_graph)
{
	int i;

	for (i = 1; i < mat_graph->node_num; i++)
		extend_edge(mat_graph);
}

void extend_edge(struct Matrix_Graph *mat_graph)
{
	int i, j, k;

	for (i = 1; i <= mat_graph->node_num; i++)
		for (j = 1; j <= mat_graph->node_num; j++) {
			for (k = 1; k <= mat_graph->node_num; k++)
				if (mat_graph->shortest_matrix[i][k] != INT_MAX && \
					mat_graph->adjcent_matrix[k][j] != INT_MAX && \
					mat_graph->shortest_matrix[i][j] > \
					mat_graph->shortest_matrix[i][k] + \
					mat_graph->adjcent_matrix[k][j]) {
					mat_graph->shortest_matrix[i][j] = \
					mat_graph->shortest_matrix[i][k] + \
					mat_graph->adjcent_matrix[k][j];
					mat_graph->precusor[i][j] = k;
				}
		}
}
