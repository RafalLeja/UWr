#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct edge {
  int parent;
  int child;
};

struct vertex {
  int v;
  int inTime;
  int outTime;
};

void sort(struct edge *edges, int n);
short partition(struct edge *edges, short left, short right);
void quickSort(struct edge *edges, short left, short right);
void dfs(struct vertex *vertices, struct edge *edges, int v, int time, int n);
int lowerBound(struct edge *edges, int n, int x);
bool isParent(int a, int b, struct vertex *vertices);

int main(void)
{ 
  int n, q;
  scanf("%d %d", &n, &q);

  struct edge *edges;
  edges = (struct edge *)calloc((n-1), sizeof(struct edge));

  struct vertex *vertices;
  vertices = (struct vertex *)calloc((n), sizeof(struct vertex));

  // printf("size of edge: %d\n", sizeof(struct edge));

  for (int i = 0; i < n-1; i++) {
    scanf("%d", &edges[i].parent);
    edges[i].child = i+2;
    vertices[i].v = i+1;
  }
  vertices[n-1].v = n;

  sort(edges, n-1);

  dfs(vertices, edges, 1, 1, n);

  // for (int i = 0; i < n-1; i++) {
  //   printf("parent: %d, child: %d\n", edges[i].parent, edges[i].child);
  // }

  // for (int i = 0; i < n; i++) {
  //   printf("v: %d, in: %d, out: %d\n", vertices[i].v, vertices[i].inTime, vertices[i].outTime);
  // }

  for (int i = 0; i < q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a == 1) {
      printf("TAK\n");
      continue;
    }
    if (isParent(a, b, vertices)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(edges);
  // free(tree);
  return 0;
}

void sort(struct edge *edges, int n) {
  quickSort(edges, 0, n-1);
}

short partition(struct edge *edges, short left, short right) {
  short pivot = edges[right].parent;
  short i = left - 1;
  struct edge temp;
  for (int j = left; j < right; j++) {
    if (edges[j].parent < pivot) {
      i++;
      temp = edges[i];
      edges[i] = edges[j];
      edges[j] = temp;
    }
  }
  temp = edges[i+1];
  edges[i+1] = edges[right];
  edges[right] = temp;
  return i+1;
}

void quickSort(struct edge *edges, short left, short right) {
  if (left<right)
  {
    short pivot = partition(edges, left, right);
    quickSort(edges, left, pivot-1);
    quickSort(edges, pivot+1, right);
  }
}

void push(int *stack, int *stackTop, int v) {
  *stackTop += 1;
  stack[*stackTop] = v;
}

int pop(int *stack, int *stackTop) {
  int v = stack[*stackTop];
  *stackTop -= 1;
  return v;
}

void dfs(struct vertex *vertices, struct edge *edges, int v, int time, int n) {
  int *stack;
  stack = (int *)calloc(n, sizeof(int));

  int stackTop = 0;

  push(stack, &stackTop, v);

  bool *visited;
  visited = (bool *)calloc(n, sizeof(bool));

  int globalTime = time;
  int u;
  int child;
  for (int i = 0; i <= n-1; i++) {
    u = pop(stack, &stackTop);
    visited[u-1] = true;
    // printf("u: %d\n", u);
    
    vertices[u-1].inTime = globalTime;
    vertices[u-1].outTime = globalTime;
    globalTime += 1;

    child = lowerBound(edges, n-1, u);
    while (edges[child].parent == u) {
      if (!visited[edges[child].child-1]) {
        push(stack, &stackTop, edges[child].child);
      }
      child++;
    }
  }

  for (int i = n-1; i >= 0; i--) {
    u = edges[i].child;
    if (vertices[edges[i].parent-1].outTime < vertices[u-1].outTime) {
      vertices[edges[i].parent-1].outTime = vertices[u-1].outTime;
    }
  }

  free(stack);
  free(visited);
}

int lowerBound(struct edge *edges, int n, int x) {
  int left = 0;
  int right = n;
  int mid;
  while (left < right) {
    mid = (left + right) / 2;
    if (edges[mid].parent < x) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return left;
}

bool isParent(int a, int b, struct vertex *vertices){
  // printf("a in: %d, out: %d\n", inTime[a-1], outTime[a-1]);
  // printf("b in: %d, out: %d\n", inTime[b-1], outTime[b-1]);
  if (vertices[a-1].inTime <= vertices[b-1].inTime && vertices[a-1].outTime >= vertices[b-1].outTime) {
    return true;
  } else {
    return false;
  }
}