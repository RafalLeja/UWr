import operator

def rozwiazanie_kryptorym(p1,p2,s,op):
  rozwiazania = []
  dict = litery(p1,p2,s)
  for x in range(10**len(dict)):
    i = 1
    for key in dict.keys():
      dict[key] = (x % (10**i)) - (x % (10**(i-1)))
      i += 1
    if kryptorym(p1,p2,s,op,dict):
      rozwiazania.append(dict.copy())
    print(dict)
  return rozwiazania

def kryptorym(p1,p2,s,op,dict):
  p1 = str_to_num(p1, dict)
  p2 = str_to_num(p2, dict)
  s = str_to_num(s, dict)
  if op(p1,p2) == s:
    return True
  return False
      
def str_to_num(s, dict):
  sum = 0
  i = len(s)-1
  for l in s:
    sum += dict[l] * (10**i)
    i -= 1
  return sum
    
def litery(s1,s2,s3):
  dict = {}
  for x in s1+s2+s3:
    if x not in dict:
      dict[x] = 0
  
  return dict

print(rozwiazanie_kryptorym("kioto","osaka","tokio",operator.add))
# print(rozwiazanie_kryptorym("a","a","b",operator.mul))