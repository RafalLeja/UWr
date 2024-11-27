### Na użytek przydziału i zwalniania stron pamięci w przestrzeni użytkownika systemy uniksowe udostępniają wywołania systemowe sbrk(2) oraz parę mmap(2) i munmap(2). Jakie są wady stosowania sbrk do zarządzania rozmiarem sterty przez biblioteczny algorytm zarządzania pamięcią malloc(3)?


### Jak można to poprawić przy pomocy mmap i munmap? Kiedy procedura free może zwrócić pamięć do jądra?