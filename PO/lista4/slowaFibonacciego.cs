/*

    https://learn.microsoft.com/en-us/dotnet/api/system.collections.ienumerable?view=net-8.0
*/

using System;
using System.Collections;

namespace fibonacci
{
    public class SlowaFibonacciego : IEnumerable
    {
        private string[] _slowa;
        public SlowaFibonacciego(int n)
        {
           _slowa = new string[n];

           for (int i = 0; i < n; i++)
           {
                _slowa[i] = Slowo(i+1);
           }
        }

        public string Slowo(int n)
        {
            if(n==1) 
            {
                return "b";
            }else if(n==2)
            {
                return "a";
            }else
            {
                string s2 = "b";
                string s1 = "a";
                string s0 = "";
                for (int i = 2; i < n; i++)
                {
                    s0 = s1 + s2;
                    s2 = s1;
                    s1 = s0;
                }
                return s0;
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
        public string[] _slowa;

        int position = -1;

        public SlowaEnum(string[] list)
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

        public string Current
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
        public static void Main()
        {
            SlowaFibonacciego slowa = new SlowaFibonacciego(6);
            foreach (string s in slowa)
            {
                System.Console.WriteLine(s);
            }
        }
    }

}