/* 
	* Rafał Leja
   * PO: lista 2, zadanie 4: LazyList
	* msc leniwa-lista.cs 
*/

using System;
using System.Collections.Generic;

namespace LazyList
{
   public class LazyIntList
   {
		public List<int> lista; 

		public LazyIntList(){
			lista = new List<int>(); 
		}

		public virtual int element(int x){
			// według polecenia liczymy liste od 1, więc musimy wyeliminować błedne wywołania
			if(x <= 0) return 0;

			if(lista.Count < x){
				for (int i = lista.Count; i < x; i++)
				{
					lista.Add(i);
				}
			}

			return lista[x-1];
		}

		public int size(){
			return lista.Count;
		}
		
   }

	public class LazyPrimeList : LazyIntList
	{
		public new List<int> lista; 

		public LazyPrimeList(){
			lista = new List<int>();
		}

		// iterowanie po kolejnych liczbach aż napotkamy pierwszą 
		public override int element(int x){
			if(x <= 0) return 0;
			if(lista.Count < x){
					int pierw = this.element(x-1) + 1;
					while (!pierwsza(pierw)) 
					{
						pierw++;
					}
					lista.Add(pierw);
				}
			

			return lista[x-1];
		}

		// algorytm do sprawdzania czy liczba jest pierwsza
		private bool pierwsza(int x){
			for (int i = 2; i * i <= x; i++) 
			{
				if(x % i == 0)
				{
					return false;
				}
			}

			return true;
		}

		public new int size(){
			return lista.Count;
		}
	}

	public class Program
	{
		public static void Main(string[] args)
		{
			var lista = new LazyIntList();
			var pierwsze = new LazyPrimeList();

			Console.Write($"lista.element(40) = {lista.element(40)}");
			Console.WriteLine($", lista.size() = {lista.size()}");

			Console.Write($"lista.element(38) = {lista.element(38)}");
			Console.WriteLine($", lista.size() = {lista.size()}");

			Console.Write($"pierwsze.element(40) = {pierwsze.element(40)}");
			Console.WriteLine($", pierwsze.size() = {pierwsze.size()}");

			Console.Write($"pierwsze.element(38) = {pierwsze.element(38)}");
			Console.WriteLine($", pierwsze.size() = {pierwsze.size()}");

		}
	}
}