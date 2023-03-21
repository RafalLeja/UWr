/*
    Rafał Leja
    PO: słowa Fibbonaciego, lista 4, zadanie 2
    > mcs slowaFibbonacciego.cs
    https://learn.microsoft.com/en-us/dotnet/api/system.collections.ienumerable?view=net-8.0
*/

using System;
using System.Collections;

namespace fibonacci
{
    // klasa SlowaFibonacciego implementuje IEnumerable
    public class SlowaFibonacciego : IEnumerable
    {
        // tablica do przechowywania słów
        private string[] _slowa;

        // konstruktor
        public SlowaFibonacciego(int n)
        {
            // konstrukcja tablicy
           _slowa = new string[n];

           for (int i = 0; i < n; i++)
           {
                _slowa[i] = Slowo(i+1);
           }
        }

        // rekurencyjna funkcja generująca kolejne słowa
        public string Slowo(int n)
        {
            if(n==1) return "b";
            if(n==2) return "a";
            return Slowo(n-1)+Slowo(n-2);
        }

        // implementacja funkcji GetEnumerator()
        public IEnumerator GetEnumerator()
        {
            // odwoływanie się do Enumeratora wbudowanej klasy Array
            return _slowa.GetEnumerator();
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