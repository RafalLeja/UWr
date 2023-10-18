# Rafał Leja
# zadanie 5 lista 3 "suma"
# 17.10.2023

def max_sublist_sum(lista):
  max_sum = lista[0]
  max_start = 0
  max_end = 0
  curr_sum = lista[0]
  curr_start = 0
  
  for i in range(len(lista)):
    # sprawdzamy czy suma wzrośnie z następnym elementem
    if lista[i] > curr_sum + lista[i]:
      curr_sum = lista[i]
      curr_start = i
    # w przeciwnym wypadku aktualizujemy sume
    else:
      curr_sum += lista[i]
    # sprawdzamy czy aktualna suma jest największa
    if curr_sum > max_sum:
      max_sum = curr_sum
      max_start = curr_start
      max_end = i
  return (max_start, max_end)

print(max_sublist_sum([1, 2, 3,-4,5,-2,-5,-6,3,5]))