# Rafał Leja
# zadanie 5 lista 3 "suma"
# 17.10.2023

def max_sublist_sum(lista):
  max_sum = lista[0]
  max_start = 0
  max_end = 0
  curr_sum = lista[0]
  curr_start = 0