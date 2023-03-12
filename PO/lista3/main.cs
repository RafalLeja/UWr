/* 
	* Rafał Leja, 12.03.2023
    * PO: lista 3, zadanie 1 oraz 4: lista oraz wektor
    * kompilator: mono, so: Windows 10
	* mcs -t:library -out:wektor.dll wektor.cs
    * mcs -t:library -out:lista.dll lista.cs
    * mcs -r:wektor.dll -r:lista.dll -out:main.exe | .\main.cs
*/

using System;
using WektorBib;
using ListaBib;

namespace Main
{
    class Prog
    {

        static void Main(){


            Wektor a = new Wektor(2, 2f, 7f);
            Wektor b = new Wektor(2, 3f, 11f);
            Wektor c = new Wektor(2, 5f, 13f);

            Lista<Wektor> l = new Lista<Wektor>();
            
            l.push_back(b);
            l.push_back(c);
            l.push_front(a);
            
            while (l.size != 0)
            {
                Wektor output = l.pop_back();
                Console.Write(
                    $"|[{output.val[0]}, {output.val[1]}]| = "
                );
                Console.WriteLine(
                    $"{output.norma()}"
                );
            };

            Console.Write(
                $"[{a.val[0]}, {a.val[1]}] + "
            );
            Console.Write(
                $"[{b.val[0]}, {b.val[1]}] = "
            );
            Console.WriteLine(
                $"[{(a+b).val[0]}, {(a+b).val[1]}]"
            );

            Console.Write(
                $"[{a.val[0]}, {a.val[1]}] * "
            );
            Console.Write(
                $"[{b.val[0]}, {b.val[1]}] = "
            );
            Console.WriteLine(
                $"[{(a*b).val[0]}, {(a*b).val[1]}]"
            );

            Console.Write(
                $"5 * [{c.val[0]}, {c.val[1]}] = "
            );
            Console.WriteLine(
                $"[{(5*c).val[0]} , {(5*c).val[1]}]"
            );
        }
    }
}