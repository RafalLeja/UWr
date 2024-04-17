import sys

def V(i,j):
  return 'V%d_%d' % (i,j)

def get_row(i, k):
    return [V(i,j) for j in range(k)] 
            
def get_column(j, m):
    return [V(i,j) for i in range(m)] 

def domains(Vs):
  return [ q + ' in 0..1' for q in Vs ]

def triplets(k, m):
  cons = []
  # horizontal
  for i in range(k):
    for j in range(2, m-2):
      cons.append('tuples_in([[%s, %s, %s]], [[1, 1, 1], [0, 1, 1], [0, 0, 1], [0, 0, 0], [1, 0, 0], [1, 1, 0], [1, 0, 1]])' % (V(i, j-1), V(i, j), V(i, j+1)))

  # vertical
  for j in range(m):
    for i in range(2, k-2):
      cons.append('tuples_in([[%s, %s, %s]], [[1, 1, 1], [0, 1, 1], [0, 0, 1], [0, 0, 0], [1, 0, 0], [1, 1, 0], [1, 0, 1]])' % (V(i-1, j), V(i, j), V(i+1, j)))

  return cons

def squares(k, m):
  cons = []
  for i in range(k-1):
    for j in range(m-1):
      cons.append(('tuples_in([[%s, %s, %s, %s]], [[1, 1, 1, 1], [0, 0, 0, 0],' 
      '[0, 0, 0, 1], [0, 0, 1, 0], [0, 1, 0, 0], [1, 0, 0, 0],'
      '[1, 1, 0, 0], [1, 0, 1, 0], [0, 1, 0, 1], [0, 0, 1, 1]])') % (V(i, j), V(i+1, j), V(i, j+1), V(i+1, j+1)))
  return cons

def print_constraints(Cs, indent, d):
  position = indent
  print (indent * ' ', end='')
  for c in Cs:
    print (c + ',', end=' ')
    position += len(c)
    if position > d:
      position = indent
      print ()
      print (indent * ' ', end='')

def rowSums(k, rows):
  cons = []
  for i in range(k):
    cons.append('sum([%s], #=, %d)' % (', '.join(get_row(i, k)), rows[i]))
  return cons

def colSums(m, cols):
  cons = []
  for j in range(m):
    cons.append('sum([%s], #=, %d)' % (', '.join(get_column(j, m)), cols[j]))
  return cons

def burze(k, m, fills, rows, cols):
  variables = [ V(i,j) for i in range(k) for j in range(m)]

  print (':- use_module(library(clpfd)).')
  print ('solve([' + ', '.join(variables) + ']) :- ')
  
  cs = domains(variables) + triplets(k, m) + squares(k, m) + rowSums(k, rows) + colSums(m, cols)
  for i,j,val in fills:
    cs.append( '%s #= %d' % (V(i,j), val) )

  print_constraints(cs, 4, 120),
  print ()
  print ('    labeling([ff], [' +  ', '.join(variables) + ']).' )
  print ()
  print (':- solve(X), write(X), nl.')  


  return

if __name__ == '__main__':
  inputFile = open('zad_input.txt', 'r')

  rows = list(map(int, inputFile.readline().strip().split()))
  k = len(rows)

  cols = list(map(int, inputFile.readline().strip().split()))
  m = len(cols)  

  fills = []
  for line in inputFile:
    fills.append(list(map(int, line.strip().split())))

  with open('zad_output.txt', 'w') as sys.stdout:
    burze(k, m, fills, rows, cols)