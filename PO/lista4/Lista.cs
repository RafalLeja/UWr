using Interfejs;
using System.Collections;

namespace Lista
{
    public class Lista<T> : IListCollection<T>, IEnumerable
    {

        public class Node
        {
            public T content;
            public Node? next;

            public Node(T content)
            {
                this.content = content;
                next = null;
            }
        }

        public Node? head;
        public Node? tail;


        //implementacja dostepu indeksowanego
        public T this[int index]
        {
            get
            {
                Node? current = head;
                int currentIndex = 0;

                while (current != null && currentIndex < index)
                {
                    current = current.next;
                    currentIndex++;
                }

                return current!.content;
            }
        }

        public override string ToString()   //implementacja metody string ToString() -> wywołanie Console.Write("obiekt typu Lista<T>")
        {                                   //wypisze jego cala zawartosc zamiast nazwy obiektu
            string s = "";
            Node? current = head;

            while (current != null)
            {
                s += $"{current.content} ";
                current = current.next;
            }

            return s;
        }

        public int Length   //implementacja wlasciwosci Length
        {
            get
            {
                int len = 0;
                Node? current = head;

                while(current != null){ 
                    len++;
                    current = current.next;
                }

                return len;
            }
        }

        public bool IsEmpty() => head == null;

        public void Add(T value)
        {
            Node newNode = new(value);
            if (IsEmpty() == true) head = tail = newNode;
            else
            {
                tail!.next = newNode;
                tail = newNode;
            }
        }

        public void Remove(T value)
        {
            Node? current = head;
            Node? previous = null;
            while (current != null)
            {
                if(current.content!.Equals(value))
                {
                    if (previous == null)
                    {
                        head = current.next;
                        return;
                    }
                    previous.next = current.next;
                    return;
                }
                previous = current;
                current = current.next;
            }

        }

        public void Show()
        {
            Node? current = head;
            while (current != null)
            {
                Console.WriteLine(current.content);
                current = current.next;
            }
        }
    
        public IEnumerator GetEnumerator()
        {
            return new ListaEnumerator(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        private class ListaEnumerator : IEnumerator
        {
            private readonly Lista<T> _lista;
            private Node? _current;

            public ListaEnumerator(Lista<T> lista)
            {
                _lista = lista;
                _current = null;
            }

            public T Current
            {
                get
                {
                    if (_current == null)
                    {
                        throw new InvalidOperationException();
                    }

                    return _current.content;
                }
            }

            object? IEnumerator.Current => Current;

            public bool MoveNext()
            {
                if (_current == null)
                {
                    _current = _lista.head;
                }
                else
                {
                    _current = _current.next;
                }

                return _current != null;
            }

            public void Reset()
            {
                _current = null;
            }
        }
    }
}