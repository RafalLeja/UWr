/* 
	* Rafał Leja
	* PO: lista 3, zadanie 4: Wektor
	* msc wektor.cs -out:wektor.dll 
*/

using System;

namespace WektorBib
{
	public class Wektor
	{
		float[] wartosci;
		int wymiar;

		// konstruktor wektora zadawany w sposób:
		// Wektor(wymiar = n,
		// n liczb typu float ozaczających kolejne współrzędne wektora)
		public Wektor(int n, params float[] wart)
		{
			wymiar = n;
			wartosci = wart;
			// usuwanie ewentualnego nadmiaru argumentów
			// (można rówież w takim przypadku zgłosić wyjątek,
			// ale uznałem że tak będzie łaskawiej dla użytkownika)
			Array.Resize(ref wartosci, n);
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
			if(a.wymiar != b.wymiar)
			{
				throw new ArgumentException(
					"Wektory muszą mieć takie same wymiary!");
			}
			int n = a.wymiar;;
			float[] wart = new float[n];
			// dodawanie kolejnych współrzędnych wektora
			for (int i = 0; i < n; i++)
			{
				wart[i] = a.wartosci[i] + b.wartosci[i];
			}
			return new Wektor(n, wart);
		}
		
		// przeciążenie operatora '*', przypadek skalar * wektor
		public static Wektor operator *(float a, Wektor b)
		{
			int n = b.wymiar;
			float[] wart = new float[n];
			// mnożenie kolejnych współrzędnych wektora przez skalar
			for (int i = 0; i < n; i++)
			{
				wart[i] = b.wartosci[i] * a;
			}
			return new Wektor(n, wart);
		}

		// przeciążenie operatora '*' w przypadku wektor * wektor
		public static Wektor operator *(Wektor a, Wektor b)
		{
			// podobnie jak przy dodawaniu, 
			// iloczyn wektorów jest zdefiniowany
			// tylko dla wektorów o jednakowych wymiarach
			if(a.wymiar != b.wymiar)
			{
				throw new ArgumentException(
					"Wektory muszą mieć takie same wymiary!");
			}
			int n = a.wymiar;
			float[] wart = new float[n];
			for (int i = 0; i < n; i++)
			{
				wart[i] = a.wartosci[i] * b.wartosci[i];
			}
			return new Wektor(n, wart);
		}

		public float norma(){
			float wynik = 0;
			foreach (var item in this.wartosci)
			{
				wynik += (float)Math.Pow(item, 2.0f);
			}
			return (float)Math.Sqrt(wynik);
		}
	}
}