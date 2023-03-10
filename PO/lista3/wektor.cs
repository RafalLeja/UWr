/* 
	* Rafał Leja
   * PO: lista 3, zadanie 4: LazyList
	* msc leniwa-lista.cs 
*/

using System;

namespace WektorBib
{
	public class Wektor
	{
		float[] wartosci;
		int wymiar;

		public Wektor(int n, params float[] wart)
		{
			wymiar = n;
			wartosci = wart;
		}

		public static Wektor operator +(Wektor a, Wektor b)
		{
			int n = a.wymiar > b.wymiar ? a.wymiar : b.wymiar;
			float[] wart = new float[n];
			for (int i = 0; i < n; i++)
			{
				wart[i] = 0;
				if (a.wymiar > i)
				{
					wart[i] += a.wartosci[i];
				}
				if (b.wymiar > i)
				{
					wart[i] += b.wartosci[i];
				}
			}
			return new Wektor(n, wart);
		}

		public static Wektor operator *(float a, Wektor b)
		{
			int n = b.wymiar;
			float[] wart = new float[n];
			for (int i = 0; i < n; i++)
			{
				wart[i] = b.wartosci[i] * a;
			}
			return new Wektor(n, wart);
		}

		public static Wektor operator *(Wektor a, Wektor b)
		{
			int n = a.wymiar > b.wymiar ? a.wymiar : b.wymiar;
			float[] wart = new float[n];
			for (int i = 0; i < n; i++)
			{
				wart[i] = 0;
				if (a.wymiar > i && b.wymiar > i)
				{
					wart[i] += a.wartosci[i] * b.wartosci[i];
				}
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

	public class Program
	{
		public static void Main(){
			Wektor a = new Wektor(1, 3f);
			Wektor b = new Wektor(1, 2f);
			Wektor c = 2*b;
			System.Console.WriteLine($"a = {a.norma()}, b = {b.norma()}, a*b = {c.norma()}");
		}
	}
}