#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int u, v, w;
} Edge;

typedef struct
{
    int parent[MAX];
    int rank[MAX];
} DisjointSet;

void initializeDisjointSet(DisjointSet *ds, int n)
{
    for (int i = 0; i < n; i++)
    {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

int find(DisjointSet *ds, int u)
{
    if (ds->parent[u] != u)
    {
        ds->parent[u] = find(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

void unionSets(DisjointSet *ds, int u, int v)
{
    int rootU = find(ds, u);
    int rootV = find(ds, v);

    if (rootU != rootV)
    {
        if (ds->rank[rootU] > ds->rank[rootV])
        {
            ds->parent[rootV] = rootU;
        }
        else if (ds->rank[rootU] < ds->rank[rootV])
        {
            ds->parent[rootU] = rootV;
        }
        else
        {
            ds->parent[rootV] = rootU;
            ds->rank[rootU]++;
        }
    }
}

int compareEdges(const void *a, const void *b)
{
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->w - edgeB->w;
}

void kruskal(Edge edges[], int n, int e)
{
    DisjointSet ds;
    initializeDisjointSet(&ds, n);

    qsort(edges, e, sizeof(Edge), compareEdges);

    Edge result[MAX];
    int resultIndex = 0;

    for (int i = 0; i < e; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;

        if (find(&ds, u) != find(&ds, v))
        {
            result[resultIndex++] = edges[i];
            unionSets(&ds, u, v);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < resultIndex; i++)
    {
        printf("%d -- %d == %d\n", result[i].u, result[i].v, result[i].w);
    }
}

int main()
{
    int n, e;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    Edge edges[MAX];
    printf("Enter the edges (u v w):\n");
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    kruskal(edges, n, e);

    return 0;
}