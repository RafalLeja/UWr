def odc(odcinki):
  odcinki = sorted(odcinki, key=lambda x: x[0])

  out = LIS(odcinki)
  return out
  
def LIS(arr):
  n = len(arr) 

  l = [([],1) for i in range(n)]
  l[0] = ([arr[0]], 1)

  for i in range(1, n):
    for j in range(i):
      if arr[i][1] >= arr[j][1] and (len(l[i][0]) < len(l[j][0]) + 1):
        l[i] = ( l[j][0].copy(), l[i][1] )
    l[i][0].append(arr[i])

  for i in range(n):
    pos = 0
    for j in range(i):
      if arr[i][1] >= arr[j][1] and len(l[i][0]) == len(l[j][0]) + 1:
        pos += l[j][1]
        if pos > l[i][1]:
          l[i] = (l[i][0], pos)
  print(l) 

  maxx = l[0]
  for x in l:
      if len(x[0]) > len(maxx[0]):
          maxx = x

  
  num = 0
  for x in l:
      if len(x[0]) == len(maxx[0]):
          num += x[1]

  maxx = (maxx[0], num)

  return maxx

# print(odc([(0, 6), (1, 5), (2, 4), (3, 3), (4, 2), (5, 1)]))
print(odc([(2, 1), (1, 2), (3, 2), (4, 3)]))