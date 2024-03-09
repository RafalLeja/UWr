// Rafał Leja
// 340879
// MBa

#include <stdio.h>
#include <stdlib.h>

void sort(unsigned int *hierarchy, unsigned int *orderedHierarchy, int n);

void quickSort(unsigned int *hierarchy, unsigned int *orderedHierarchy, int left, int right);

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime);

void dfsTimes(unsigned int *hierarchy, unsigned int *orderedHierarchy, int v, int t, unsigned int *inTime, unsigned int *outTime, int n);

int main(void)
{ 
  unsigned int n, q;
  scanf("%u %u", &n, &q);

  unsigned int *hierarchy;
  hierarchy = (unsigned int *)calloc((n-1), sizeof(unsigned int));

  unsigned int *orderedHierarchy;
  orderedHierarchy = (unsigned int *)calloc((n-1), sizeof(unsigned int));

  unsigned int *inTime;
  inTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  unsigned int *outTime;
  outTime = (unsigned int *)calloc((n), sizeof(unsigned int));

  for (int i = 0; i < n-1; i++) {
    scanf("%u", &hierarchy[i]);
  }

  sort(hierarchy, orderedHierarchy, n-1);

  dfsTimes(hierarchy, orderedHierarchy, 1, 1, inTime, outTime, n);

  for (int i = 0; i < n; i++) {
    printf("K[%u] = %u, in: %u, out: %u\n", i+1, hierarchy[i-1], inTime[i], outTime[i]);
  }

  for (int i = 0; i < n-1; i++) {
    printf("K[%u] = %u\n", i+1, orderedHierarchy[i]);
  }

  for (int i = 0; i < q; i++) {
    unsigned int a, b;
    scanf("%u %u", &a, &b);
    if (a == 1) {
      printf("TAK\n");
      continue;
    }
    if (isParent(a, b, inTime, outTime)) {
      printf("TAK\n");
    } else {
      printf("NIE\n");
    }
  }

  free(hierarchy);
  free(inTime);
  free(outTime);
  return 0;
}

void sort(unsigned int *hierarchy, unsigned int *orderedHierarchy, int n) {
  for (int i = 0; i < n; i++) {
    orderedHierarchy[i] = i+2;
  }

  quickSort(hierarchy, orderedHierarchy, 0, n-1);
}

int partition(unsigned int *hierarchy, unsigned int *orderedHierarchy, int left, int right) {
  int pivot = hierarchy[right];
  int i = left - 1;
  for (int j = left; j < right; j++) {
    if (hierarchy[j] < pivot) {
      i++;
      int temp = orderedHierarchy[i];
      orderedHierarchy[i] = orderedHierarchy[j];
      orderedHierarchy[j] = temp;
    }
  }
  int temp = orderedHierarchy[i+1];
  orderedHierarchy[i+1] = orderedHierarchy[right];
  orderedHierarchy[right] = temp;
  return i+1;
}

void quickSort(unsigned int *hierarchy, unsigned int *orderedHierarchy, int left, int right) {
  if (left<right)
  {
    int pivot = partition(hierarchy, orderedHierarchy, left, right);
    quickSort(hierarchy, orderedHierarchy, left, pivot-1);
    quickSort(hierarchy, orderedHierarchy, pivot+1, right);
  }
  }

void dfsTimes(unsigned int *hierarchy, unsigned int *orderedHierarchy, int idx, int t, unsigned int *inTime, unsigned int *outTime, int n) {
  inTime[idx-1] = t;
  outTime[idx-1] = t;
  for (int i = 1; i <= n-1; i++) {
    int el = orderedHierarchy[i-1]-1;
    // printf("el: %u, in: %u, out: %u, hierarchy: %u\n", el+1, inTime[el], outTime[el], hierarchy[el-1]);
    inTime[el] = outTime[hierarchy[el-1]-1] + 1;
    outTime[el] = inTime[el];
    outTime[hierarchy[el-1]-1] += 1;
  }

  for (int i = n-1; i > 0; i--) {
    if (outTime[i] > outTime[hierarchy[i-1]-1]) {
      outTime[hierarchy[i-1]-1] = outTime[i];
    }
  }
}

int isParent(int a, int b, unsigned int *inTime, unsigned int *outTime){
  // printf("a in: %u, out: %u\n", inTime[a-1], outTime[a-1]);
  // printf("b in: %u, out: %u\n", inTime[b-1], outTime[b-1]);
  if (inTime[a-1] <= inTime[b-1] && outTime[a-1] >= outTime[b-1]) {
    return 1;
  } else {
    return 0;
  }
}