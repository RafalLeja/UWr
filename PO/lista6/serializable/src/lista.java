/* Rafał Leja
 * lista 6 zadanie 1 i 2, Serializable, Collections
 */

import java.io.Serializable;
import java.security.InvalidParameterException;

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

class Lista<T> implements Serializable {
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
    // zgłaszam wyjątek

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
}

