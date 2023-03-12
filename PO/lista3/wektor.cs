/*
	* Rafał Leja, 12.03.2023
	* PO: Wektor, lista 3, zadanie 4
    * moduł WektorBib zawierający klasę Wektor
	* mcs -t:library -out:wektor.dll wektor.cs
*/

using System;

namespace WektorBib
{
	public class Wektor
	{
		public float[] val;
		public int dim;

		// konstruktor wektora zadawany w sposób:
		// Wektor(wymiar = n,
		// n liczb typu float ozaczających kolejne współrzędne wektora)
		public Wektor(int n, params float[] SetVal)
		{
			dim = n;
			val = SetVal;
			// usuwanie ewentualnego nadmiaru argumentów
			// (można rówież w takim przypadku zgłosić wyjątek,
			// ale uznałem że tak będzie łaskawiej dla użytkownika)
			Array.Resize(ref val, n);
		}

		// przeciążenie operatora '+'
		public static Wektor operator +(Wektor a, Wektor b)
		{
			// dodawanie wektorów jest zdefiniowane tylko
			// dla wektorów o jednkakowych wymiarach,
			// dlatego sprawdzam ten warunek,
			// i w przypadku różnych wymiarów,
			// zgłaszam wyjątek zgodnie z dokumentacją:
			// https://learn.microsoft.com/pl-pl/dotnet/csharp/fundamentals/exceptions/creating-and-throwing-exceptions
			if(a.dim != b.dim)
			{
				throw new ArgumentException(
					"Wektory muszą mieć takie same wymiary!");
			}
			int n = a.dim;;
			float[] wart = new float[n];
			// dodawanie kolejnych współrzędnych wektora
			for (int i = 0; i < n; i++)
			{
				wart[i] = a.val[i] + b.val[i];
			}
			return new Wektor(n, wart);
		}
		
		// przeciążenie operatora '*', przypadek skalar * wektor
		public static Wektor operator *(float a, Wektor b)
		{
			int n = b.dim;
			float[] wart = new float[n];
			// mnożenie kolejnych współrzędnych wektora przez skalar
			for (int i = 0; i < n; i++)
			{
				wart[i] = b.val[i] * a;
			}
			return new Wektor(n, wart);
		}

		// przeciążenie operatora '*' w przypadku wektor * wektor
		public static Wektor operator *(Wektor a, Wektor b)
		{
			// podobnie jak przy dodawaniu, 
			// iloczyn wektorów jest zdefiniowany
			// tylko dla wektorów o jednakowych wymiarach
			if(a.dim != b.dim)
			{
				throw new ArgumentException(
					"Wektory muszą mieć takie same wymiary!");
			}
			int n = a.dim;
			float[] wart = new float[n];
			for (int i = 0; i < n; i++)
			{
				wart[i] = a.val[i] * b.val[i];
			}
			return new Wektor(n, wart);
		}

		public float norma(){
			float wynik = 0;
			foreach (var item in this.val)
			{
				wynik += (float)Math.Pow(item, 2.0f);
			}
			return (float)Math.Sqrt(wynik);
		}
	}
}