```C
long neigh(long a[], long n, long i, long j) {
  long ul = a[(i-1)*n + (j-1)];
  long ur = a[(i-1)*n + (j+1)];
  long dl = a[(i+1)*n - (j-1)];
  long dr = a[(i+1)*n - (j+1)];
  return ul + ur + dl + dr;
}

long neigh(long a[], long n, long i, long j) {
  long ix = (i-1)*n;
  long iy = (i+1)*n;
  long jx = j-1;
  long jy = j+1;
  return a[ix + jx]
  + a[ix + jy]
  + a[iy - jx]
  + a[iy - jy];
}

long neigh(long a[], long n, long i, long j) {
  return a[(i-1)*n + j-1]
  + a[(i-1)*n + j+1]
  + a[(i+1)*n - j-1]
  + a[(i+1)*n - j+1];
}
```

### Eliminacja wspólnych podwyrażeń
  - jeżeli jakieś wrażenie jest używane w wielu miejscach kompilator policzy je tylko raz, i zapamięta wynik