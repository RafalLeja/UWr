// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

struct Node {
  unsigned short v;
  unsigned short inTime;
  unsigned short outTime;
  // struct Node *parent;
  struct Node *child;
  struct Node *sibling;
};

int isParent(unsigned short a, unsigned short b, struct Node *tree);

void dfsTimes(struct Node *v, struct Node *tree, unsigned short *hierarchy, unsigned short t);

void buildTree(unsigned short *hierarchy, struct Node *tree, int n);

int main(void)
{ 
  unsigned short n, q;
  scanf("%hu %hu", &n, &q);

  unsigned short *hierarchy;
  hierarchy = (unsigned short *)calloc((n-1), sizeof(unsigned short));

  struct Node *tree;
  tree = calloc(n, sizeof(struct Node));

  // printf("size of tree: %d\n", sizeof(struct Node));

  for (unsigned short i = 0; i < n-1; i++) {
    scanf("%hu", &hierarchy[i]);
  }

  buildTree(hierarchy, tree, n);

  dfsTimes(tree, tree, hierarchy, 1);

  // for (int i = 0; i < n; i++) {
  //   printf("v: %hu, in: %hu, out: %hu\n", tree[i].v, tree[i].inTime, tree[i].outTime);
  // }

  for (unsigned short i = 0; i < q; i++) {
    unsigned short a, b;
    scanf("%hu %hu", &a, &b);
    if (a == 1) {
      printf("TAK\n");
      continue;
    }
    if (isParent(a, b, tree)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(hierarchy);
  free(tree);
  return 0;
}

void buildTree(unsigned short *hierarchy, struct Node *tree, int n) {
  tree[0].v = 1;

  for (int i = 1; i <= n-1; i++) {
    struct Node *parent = &tree[hierarchy[i-1]-1];
    struct Node *child = &tree[i];
    child->v = i+1;
    // child->parent = parent;
    if (parent->child == NULL) {
      parent->child = child;
    } else {
      struct Node *sibling = parent->child;
      while (sibling->sibling != NULL) {
        sibling = sibling->sibling;
      }
      sibling->sibling = child;
    }
  }
}

void dfsTimes(struct Node *v, struct Node *tree, unsigned short *hierarchy, unsigned short t) {
  v->inTime = t;
  v->outTime = t;
  struct Node *child = v->child;
  if (child != NULL) {
    dfsTimes(child, tree, hierarchy, t+1);
    // v->outTime = child->outTime;
  }
  struct Node *sibling = v->sibling;
  if (sibling != NULL) {
    dfsTimes(sibling, tree, hierarchy, v->outTime+1);
  }
  if (v->v != 1) {
    struct Node *parent = &tree[hierarchy[v->v-2]-1];
    // printf("v: %hu, parent: %hu\n", v->v, parent->v);
    if (v->outTime > parent->outTime)
      parent->outTime = v->outTime;
  }
}

int isParent(unsigned short a, unsigned short b, struct Node *tree){
  // printf("a in: %hu, out: %hu\n", inTime[a-1], outTime[a-1]);
  // printf("b in: %hu, out: %hu\n", inTime[b-1], outTime[b-1]);
  if (tree[a-1].inTime <= tree[b-1].inTime && tree[a-1].outTime >= tree[b-1].outTime) {
    return 1;
  } else {
    return 0;
  }
}