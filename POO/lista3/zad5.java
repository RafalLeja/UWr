
public interface List<E> {
    int size();
    boolean isEmpty();
    boolean contains(Object o);
    // może być bardzo powolne dla LinkedList
    E get(int index);
    void add(int index, E element); 
    E remove(int index);
}

// ----------------------------------------------

public interface Collection<E> {
    int size();
    boolean isEmpty();
    boolean contains(Object o);
    // ... other collection methods
}

public interface IndexedCollection<E> extends Collection<E> {
    E get(int index);
    void add(int index, E element);
    E remove(int index);
    // ... other indexed methods
}