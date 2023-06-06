```C
__attribute__((leaf))
size_t my_strlen(const char *s);

const char *my_index(const char *s, char v) {
  for (size_t i = 0; i < my_strlen(s); i++)
    if (s[i] == v)
      return &s[i];
  return 0;
}

static size_t my_strlen(const char *s){
  long length = 0;
  while (*s != '\0') {
    s++;
    length++;
  }
  return length;
}
```

### Inlining: 
  - podstawianie ciała funkcji w miejscu jej wołania

### Ile razy zostanie zawołana funkcja «my_strlen» w funkcji «my_index» i dlaczego?
 - funkcja «my_strlen» będzie wywoływana przy każdej iteracji, ponieważ kompilator przypuszcza że wynik tej funkcji może ulec zmianie

### Dodaj atrybut2 «pure» do funkcji «my_strlen». Czemu tym razem kompilator był w stanie lepiej zoptymalizować funkcję «my_index»? 
 - atrubut pure mówi kompilatorowi że dana funkcja ma zawsze taki sam wynik dla danego argumentu, przez co kompilator może zastąpić kolejne wywołania tej funkcji wartością pierwszego wywołania

### Następnie uzupełnij ciało funkcji «my_strlen» tak, by wykonywała to samo co «strlen». Następnie usuń atrybut «pure» i dodając słowo kluczowe «static» zawęź zakres widoczności funkcji do bieżącej jednostki translacji. Co się stało w wyniku przeprowadzenia inliningu? Czy kompilatorowi udało się samemu wywnioskować, że funkcja jest czysta?
 - Kompilator wywołuję wbudowaną funkcje strlen zamiast my_strlen oraz wykrył że strlen jest pure w tym kontekście.