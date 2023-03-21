using Interfejs;

namespace Slownik
{
    public class MyDictionary<K, V> : IListCollection<K>
    {
        public class Node
        {
            public K key;
            public V content;
            public Node? next;

            public Node(K key, V content)
            {
                this.key = key;
                this.content = content;
                next = null;
            }
        }

        public Node? start;

        public bool IsEmpty() => start == null;

        public V? Find(K key)
        {

            Node? current = start;

            while (current != null)
            {
                if (current.key!.Equals(key)) return current.content;
                current = current.next;
            }

            Console.WriteLine($"PODANY KLUCZ NIE ISTNIEJE: {key}");
            return default;
        }

        public void Add(K key, V content)
        {
            if (IsEmpty() == true)
            {
                start = new(key, content);
                Console.WriteLine($"DODANO WARTOSC: {content}");
            }
            else
            {
                Node? current = start;
                while (current!.next != null)
                {
                    if (current.key!.Equals(key))
                    {
                        Console.WriteLine($"PODANY KLUCZ JUZ ISTNIEJE: {key}");
                        return;
                    }
                    current = current.next;
                }
                if (current.key!.Equals(key))
                {
                    Console.WriteLine($"PODANY KLUCZ JUZ ISTNIEJE: {key}");
                    return;
                }
                current.next = new(key, content);
                Console.WriteLine($"DODANO WARTOSC: {content}");
            }
        }

        public void Remove(K key)
        {

            if (start == null)
            {
                Console.WriteLine($"BRAK PODANEGO KLUCZA: {key}");
                return;
            }

            if (start.key!.Equals(key))
            {
                Console.WriteLine($"USUNIETO WARTOSC: {start.content}");
                start = start.next;
                return;
            }

            Node previous = start;
            Node? current = start.next;
            while (current != null)
            {
                if (current.key!.Equals(key))
                {
                    previous.next = current.next;
                    Console.WriteLine($"USUNIETO WARTOSC: {current.content}");
                    return;
                }
            }
            Console.WriteLine($"BRAK PODANEGO KLUCZA {key}");
            return;
        }

        public void Show()
        {
            Node? current = start;
            while (current != null)
            {
                Console.WriteLine($"{current.key} : {current.content}");
                current = current.next;
            }
        }
    }
}