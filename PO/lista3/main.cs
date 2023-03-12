/* 
	* Rafał Leja, 12.03.2023
    * PO: lista 3, zadanie 1 oraz 4: lista oraz wektor
    * kompilator: mono, so: Windows 10
	* mcs -t:library -out:wektor.dll wektor.cs
    * mcs -t:library -out:lista.dll lista.cs
    * mcs -r:wektor.dll -r:lista.dll -out:main.exe | ./main.cs
*/

using System;
using WektorBib;
using ListaBib;

namespace Main
{
    class Prog
    {

        static void Main(){


            Wektor a = new Wektor(1, 2f);
            Wektor b = new Wektor(1, 3f);
            Wektor c = new Wektor(1, 5f);

            Lista<Wektor> l = new Lista<Wektor>();
            
            l.push_front(a);
            l.push_front(b);
            l.push_back(c);

            System.Console.WriteLine(l.pop_back());
        }
    }
}