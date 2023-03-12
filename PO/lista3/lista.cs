/*
	* Rafał Leja, 12.03.2023
	* PO: lista.cs, lista 3, zadanie 4
    * moduł ListaBib zawierający klasę Lista oraz Element
*/

using System;

namespace ListaBib
{
    public class Element<T>
    {
        public Element<T> prev;
        public Element<T> next;
        public T val;

        public Element(T setValue, Element<T> setPrev, Element<T> setNext)
        {
            val = setValue;
            prev = setPrev;
            next = setNext;
        }
    }

    public class Lista<T>
    {
        int size;
        Element<T> first;
        Element<T> last;

        public Lista()
        {
            size = 0;
            first = null;
            last = null;
        }

        // dodawanie elementu na początek
        public void push_front(T val)
        {
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
            if(this.is_empty()) return default (T);
            T outval = first.val;
            first = first.next;
            return outval;
        }

        // zwaracnie elementu z końca
        public T pop_back()
        {
            if(this.is_empty()) return default (T);
            T outval = last.val;
            last = last.prev;
            return outval;
        }

        public bool is_empty()
        {
            return size==0; 
        }
    }
}