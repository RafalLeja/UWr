/* 
	* Rafał Leja
    * PO: lista 3, zadanie 1 oraz 4: lista oraz wektor
	* mcs -t:library -out:wektor.dll wektor.cs
    * mcs -t:library -out:lista.dll lista.cs
    * mcs -r:wektor.dll -r:lista.dll -out:main.exe main.cs
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
            System.Console.WriteLine(
                $"a = {a.norma()}, b = {b.norma()}, c = {(a+b).norma()}");
        
            Lista l = new Lista();
            l.push_front(1)
        }
    }
}