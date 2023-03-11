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

        void push_first(T val)
        {
            Element<T> elem = new Element<T>(val, null, null);
            size++;
            first = elem;
            last = elem;
        }

        public void push_front(T val)
        {
            if (this.is_empty())
            {
                push_first(val);
            }else
            {
                Element<T> elem = new Element<T>(val, null, first);
                first.prev = elem;
                first = elem;
                size++;
            }
        }

        public void push_last(T val)
        {
            if (this.is_empty())
            {
                push_first(val);
            }else
            {            
                Element<T> elem = new Element<T>(val, last, null);
                last.next = elem;
                last = elem;
                size++;
            }
        }

        public Element<T> pop_front()
        {
            if(this.is_empty()) return null;
            Element<T> outval = first;
            first = first.next;
            return outval;
        }

        public Element<T> pop_back()
        {
            if(this.is_empty()) return null;
            Element<T> outval = last;
            last = last.prev;
            return outval;
        }

        public bool is_empty()
        {
            return size==0; 
        }
    }

    public class Program
    {
        static void Main()
        {
            Lista<int> l = new Lista<int>();
            l.push_front(1);
            l.push_last(2);
            l.push_front(3);

            System.Console.WriteLine(l.pop_back().val);
            System.Console.WriteLine(l.pop_back().val);
            System.Console.WriteLine(l.pop_back().val);
        }
    }
}