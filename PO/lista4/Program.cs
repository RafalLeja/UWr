using Lista;
using Slownik;
using System.Collections.Generic;


class Program
{
    static void Main()
    {
        MyDictionary<string, int> intSlowanik = new();
        Lista<int> intLista = new();

        for (int x = 0; x < 5; x++) intLista.Add(x);
        // intSlowanik.Add("siedem", 7);
        // intSlowanik.Add("jeden", 1);
        // intSlowanik.Add("dycha", 10);

        // intSlowanik.Remove("jeden");
        // intLista.Remove(2);
        
        // Console.WriteLine($"Zawartosc slownika: ");
        // intSlowanik.Show();

        // Console.WriteLine(intLista);
        // for (int i = 0; i < intLista.Length; i++) Console.WriteLine(intLista[i]);

        foreach(int x in intLista)
        {
            Console.WriteLine(x);
        }
    }
}