/* 
	* Rafał Leja
   * PO: lista 2, zadanie 1: IntStream
	* msc strumienie-liczb.cs 
*/

using System;

public class Strumienie
{
	public class IntStream
	{
		int val;

		public IntStream(){
			val = 0;
		}

		public virtual void reset(){
			val = 0;
		}

		public virtual int next(){
			// wywoływanie funkcji sprawdzającej granice zakresu
			if (eos())
			{
				Console.WriteLine("granica zakresu liczb!");
				return val;
			}

			return val++;
		}

		public virtual bool eos(){
			// sprawdzanie czy liczba jest równa maksimum typu Int32
			if (val == Int32.MaxValue){ 
				return true;
			}
			return false;
		}

	}

	public class PrimeStream : IntStream
	{
		int val;

		public PrimeStream(){
			val = 1;
		}

		public override void reset(){
			val = 1;
		}

		private bool pierwsza(int x){
			// algorytm do sprawdzania czy liczba jest pierwsza
			for (int i = 2; i * i <= x; i++){
				if(x % i == 0){
						  return false;
				}
			}

			return true;
		}

		public override int next(){
			val++;

			// iterowanie po kolejnych liczbach aż napotkamy liczbę pierwszą
			while (!pierwsza(val)){
				if(eos()){
					Console.WriteLine("granica zakresu liczb!");
				}
				val++;
			}

			return val;
		}

		public override bool eos(){
			if (val == Int32.MaxValue){
				return true;
			}
			return false;
		}

	}

	public class RandomStream : IntStream
	{
		// konstrukcja wbudowaniej klasy Random służącej do generowania liczb losowych
		private Random val;

		public RandomStream(){
			val = new Random();
		}

		// zwracanie liczby losowej z klasy Random
		public override int next(){
			return val.Next();
		}

		public override bool eos(){
			return false;
		}
	}

	public class RandomWordStream
	{
		private PrimeStream pierwsze;
		private RandomStream rand;

		public RandomWordStream(){
			pierwsze = new PrimeStream();
			rand = new RandomStream();
		}

		public string next(){
			// generowanie długości potrzebnego słowa
			int len = pierwsze.next(); 

			// inicjacja tablicy znaków, która posłuży do układania losowago słowa
			char[] output = new char[len]; 

			// przypisywanie kolejnym elementom tablicy wartości zwracanej przez funkcje los()
			for (int i = 0; i < len; i++) 
			{
				output[i] = los();
			}

				return string.Join("", output);
		}

		public char los(){
			// funkcja zwracająca losowy znak z przedziału a - z
			return (char)('a' + rand.next() % 26); 
		}

		public void reset(){
			pierwsze.reset();
		}
	}

	public class Program
	{
		public static void Main(string[] args){
			var naturalne = new IntStream();
			var pierwsze = new PrimeStream();
			var rand = new RandomStream();
			var slowo = new RandomWordStream();
			Console.WriteLine("naturalne: || pierwsze: || losowe: || slowa: ");
			for (int i = 0; i < 10; i++){
				Console.Write($"{naturalne.next()} || ");
				Console.Write($"{pierwsze.next()} || ");
				Console.Write($"{rand.next()} || ");
				Console.WriteLine($"{slowo.next()}");
			}

			naturalne.reset();
			pierwsze.reset();
			rand.reset();
			slowo.reset();

			Console.WriteLine("-----------------");

			for (int i = 0; i < 10; i++){
				Console.Write($"{naturalne.next()} || ");
				Console.Write($"{pierwsze.next()} || ");
				Console.Write($"{rand.next()} || ");
				Console.WriteLine($"{slowo.next()}");
			}
		}
	}
}