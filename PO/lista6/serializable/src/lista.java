import java.io.Serializable;
import java.security.InvalidParameterException;
import java.util.Iterator;
import java.util.NoSuchElementException;

class Element<T> implements Serializable
{
  public Element<T> prev;
  public Element<T> next;
  public T val;

  // konstruktor klasy Element,
  // która przechowuje warość 
  // oraz odnośniki od kolejnych elementów
  public Element(T setValue, Element<T> setPrev, Element<T> setNext)
  {
    val = setValue;
    prev = setPrev;
    next = setNext;
  }
}

class ListaIterator<T> implements Iterator<T> {
  private Element<T> current;

  public ListaIterator(Element<T> start) {
    current = start;
  }

  public boolean hasNext() {
    return current != null;
  }

  public T next() {
    if (!hasNext()) {
      throw new NoSuchElementException();
    }
    T val = current.val;
    current = current.next;
    return val;
  }

  public void remove() {
    throw new UnsupportedOperationException();
  }
}

class Lista<T> implements Serializable, Iterable<T> {
  public int size;
  Element<T> first;
  Element<T> last;

  // konstruktor klasy Lista,
  // która przechowuje rozmiar
  // oraz odnośniki od pierwszego oraz ostatniego elementu
  public Lista()
  {
    size = 0;
    first = null;
    last = null;
  }

  

  // dodawanie elementu na początek
  public void push_front(T val)
  {
    // sprawdzanie, czy dodawany element będzie pierwszym
    if (this.isEmpty())
    {
      Element<T> elem = new Element<T>(val, null, null);
      size++;
      first = elem;
      last = elem;
    }else
    {
      Element<T> elem = new Element<T>(val, null, first);
      first.prev = elem;
      first = elem;
      size++;
    }
  }
  
  // dodawanie elementu na koniec
  public void push_back(T val)
  {
    // sprawdzanie, czy dodawany element będzie pierwszym
    if (this.isEmpty())
    {
      Element<T> elem = new Element<T>(val, null, null);
      size++;
      first = elem;
      last = elem;
    }else
    {            
      Element<T> elem = new Element<T>(val, last, null);
      last.next = elem;
      last = elem;
      size++;
    }
  }

  // zwracanie elementu z początku
  public T pop_front()
  {
    // gdy lista jest pusta,
    // zgłaszam wyjątek zgodnie z dokumentacją:
    // https://learn.microsoft.com/pl-pl/dotnet/csharp/-
    // fundamentals/exceptions/creating-and-throwing-exceptions
    if (this.isEmpty())
    {
      throw new InvalidParameterException(
        "Próbujesz zabrać element z pustej listy!");
    }
    T outval = first.val;
    first = first.next;
    size--;
    return outval;
  }

  // zwracanie elementu z końca
  public T pop_back()
  {
    // gdy lista jest pusta,
    // zwracamy wyjątek
    if (this.isEmpty())
    {
      throw new InvalidParameterException(
        "Próbujesz zabrać element z pustej listy!");
    }
    T outval = last.val;
    last = last.prev;
    size--;
    return outval;
  }

  // funkcja sprawdzająca rozmiar tablicy
  public boolean isEmpty()
  {
    return size==0; 
  }

  // dodawanie elementu do kolekcji
  public boolean add(T val) {
    this.push_back(val);
    return true;
  }

  
  
  public boolean addAll(Lista<T> c) {
    for (T item : c) {
      add(item);
    }
    return true;
    }
    
    public void clear() {
      size = 0;
    first = null;
    last = null;
  }
  
  public boolean contains(T o) {
    for (Element<T> curr = first; curr != null; curr = curr.next) {
      if (curr.val.equals(o)) {
        return true;
    }
  }
    return false;
  }
  
  public boolean containsAll(Lista<T> c) {
    for (T item : c) {
      if (!contains(item)) {
        return false;
      }
    }
    return true;
  }
  
  public Iterator<T> iterator() {
    return new ListaIterator<T>(first);
  }
  
  // metoda usuwająca wszystkie elementy z danej kolekcji
  public boolean removeAll(Lista<T> c) {
    boolean modified = false;
    for (T item : c) {
      modified = remove(item) || modified;
    }
    return modified;
  }
  
  // metoda usuwająca podany element z kolekcji
  public boolean remove(T o) {
    Element<T> curr = first;
    while (curr != null) {
      if (curr.val.equals(o)) {
        if (curr == first) {
          first = curr.next;
          if (first != null) {
            first.prev = null;
          }
        } else if (curr == last) {
          last = curr.prev;
          if (last != null) {
            last.next = null;
          }
        } else {
          curr.prev.next = curr.next;
          curr.next.prev = curr.prev;
        }
      size--;
      return true;
      }
      curr = curr.next;
    }
    return false;
  }

  // metoda zachowująca tylko elementy zawarte w danej kolekcji
  public boolean retainAll(Lista<T> c) {
    boolean modified = false;
    Element<T> curr = first;
    while (curr != null) {
      if (!c.contains(curr.val)) {
        if (curr == first) {
          first = curr.next;
          if (first != null) {
            first.prev = null;
          }
        } else if (curr == last) {
          last = curr.prev;
          if (last != null) {
            last.next = null;
          }
        } else {
          curr.prev.next = curr.next;
          curr.next.prev = curr.prev;
        }
          size--;
          modified = true;
      }
      curr = curr.next;
    }
    return modified;
  }
}

