/*


*/

using System;
using System.Collections;

namespace fibonacci
{
    public class Slowo
    {
        public string val;

        public Slowo(int n)
        {
            if(n==1) 
            {
                this.val = "b";
                return;
            }else if(n==2)
            {
                this.val = "a";
                return;
            }else
            {
                string s2 = "b";
                string s1 = "a";
                string s0 = "";
                for (int i = 0; i < n; i++)
                {
                    s0 = s1 + s2;
                    s2 = s1;
                    s1 = s0;
                }
                this.val = s0;
            }
        }
    }

    public class SlowaFibonacciego : IEnumerable
    {
        private Slowo[] _slowa;
        public SlowaFibonacciego(int n)
        {
           _slowa = new Slowo[n];

           for (int i = 0; i < n; i++)
           {
                _slowa[i] = new Slowo(i+1);
           }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return (IEnumerator) GetEnumerator();
        }

        public SlowaEnum GetEnumerator()
        {
            return new SlowaEnum(_slowa);
        }
    }

    public class SlowaEnum : IEnumerator
    {
        public Slowo[] _slowa;

        int position = -1;

        public SlowaEnum(Slowo[] list)
        {
            _slowa = list;
        }

        public bool MoveNext()
        {
            position++;
            return (position < _slowa.Length);

        }

        public void Reset()
        {
            position = -1;
        }

        object IEnumerator.Current
        {
            get
            {
                return Current;
            }
        }

        public Slowo Current
        {
            get
            {
                try
                {
                    return _slowa[position];
                }
                catch (IndexOutOfRangeException)
                {
                    throw new InvalidOperationException();
                }
            }
        }
    }

    public class Program
    {
        public void Main()
        {
            SlowaFibonacciego slowa = new SlowaFibonacciego(6);
            foreach (Slowo s in slowa)
            {
                System.Console.WriteLine(s);
            }
        }
    }

}