using Interfejs;
using System.Collections;

namespace Lista
{
    public class Node<T>
    {
        public T content;
        public Node? next;

        public Node(T content)
        {
            this.content = content;
            next = null;
        }
    }

    public class Lista<T> : IListCollection<T>, IEnumerable
    {
        public Node<T>? head;
        public Node<T>? tail;

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
    
        IEnumerator IEnumerable.GetEnumerator(){
            return new ListaEnum(head, tail);
        }
    }

    public class ListaEnum<T> : IEnumerator
    {
        Node<T> head;
        Node<T> tail;
        Node<T> current;
        int position;


        public ListaEnum(Node<T> getHead, Node<T> getTail)
        {
            position = -1;
            head = getHead;
            current = getHead;
            tail = getTail;
        }

        public bool MoveNext(){
            position++;
            return (current == null);
        }

        public void Reset(){
            position = -1;
            current = head;
        }
        
        object IEnumerator.Current{
            get{
                return current.content;
            }
        }
    }
}