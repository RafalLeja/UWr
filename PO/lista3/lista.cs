/*
	* Rafał Leja, 12.03.2023
	* PO: Lista<T>, lista 3, zadanie 4
    * moduł ListaBib zawierający klasę Lista oraz Element
    * mcs -t:library -out:lista.dll lista.cs
*/

using System;

namespace ListaBib
{
    public class Element<T>
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

    public class Lista<T>
    {
        public int size;
        Element<T> first;
        Element<T> last;

        // konstruktor kalsy Lista,
        // która przchowuje rozmiar
        // oraz odnośniki od piwerwszego oraz ostatniego elementu
        public Lista()
        {
            size = 0;
            first = null;
            last = null;
        }

        // dodawanie elementu na początek
        public void push_front(T val)
        {
            // sprawdzanie czy dodawany element będzie pierwszym
            if (this.is_empty())
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
            // sprawdzanie czy dodawany element będzie pierwszym
            if (this.is_empty())
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
			// https://learn.microsoft.com/pl-pl/dotnet/csharp/fundamentals/exceptions/creating-and-throwing-exceptions
            if (this.is_empty())
            {
                throw new InvalidOperationException(
                    "Próbujesz zabrać element z pustej liczby!");
            }
            T outval = first.val;
            first = first.next;
            size--;
            return outval;
        }

        // zwaracnie elementu z końca
        public T pop_back()
        {
            // gdy lista jest pusta,
            // zwracamy wyjątek
            if (this.is_empty())
            {
                throw new InvalidOperationException(
                    "Próbujesz zabrać element z pustej liczby!");
            }
            T outval = last.val;
            last = last.prev;
            size--;
            return outval;
        }

        // funkcja sprawdzająca rozmiar tablicy
        public bool is_empty()
        {
            return size==0; 
        }
    }
}