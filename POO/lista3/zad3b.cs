using System;

public interface ITaxCalculator {
  double CalculateTax( double Price );
}

public interface IPrinter {
  void PrintBill( Item[] Items, ITaxCalculator taxCalc );
}

public class TaxCalculator : ITaxCalculator{
  public double CalculateTax( double Price ) {
    return Price * 0.22;
  }
}

public class EnglishTaxCalculator : ITaxCalculator{
  public double CalculateTax( double Price ) {
    return Price * 0.2;
  }
}

public class Printer : IPrinter {
  public void PrintBill( Item[] Items, ITaxCalculator taxCalc) {
    foreach ( var item in Items ) {
      Console.WriteLine( "towar {0} : cena {1} + podatek {2}",
        item.Name, item.Price, taxCalc.CalculateTax( item.Price ) );
    }
  }
}

public class EnglishPrinter : IPrinter {
  public void PrintBill( Item[] Items, ITaxCalculator taxCalc) {
    foreach ( var item in Items ) {
      Console.WriteLine( "product {0} : price {1} + tax {2}",
        item.Name, item.Price, taxCalc.CalculateTax( item.Price ) );
    }
  }
}

public class Item {
  public Item( string Name, double Price ) {
    this.Name = Name;
    this.Price = Price;
  }
  public double Price { get; set; }
  public string Name { get; set; }
}

public class CashRegister {
  public ITaxCalculator taxCalc;
  public IPrinter printer;

  public CashRegister( ITaxCalculator taxCalc, IPrinter printer ) {
    this.taxCalc = taxCalc;
    this.printer = printer;
  }
  public double CalculatePrice( Item[] Items ) {
    double _price = 0;
    foreach ( Item item in Items ) {
      _price += item.Price + taxCalc.CalculateTax( item.Price );
    }
    return _price;
  }
  public void PrintBill( Item[] Items ) {
    printer.PrintBill( Items, taxCalc );
  }
}

public class Program {
  public static void Main() {
    Item[] items = new Item[] {
      new Item( "mleko", 2.5 ),
      new Item( "chleb", 3.5 ),
      new Item( "masło", 5.0 )
    };

    CashRegister cashRegister = new CashRegister( new TaxCalculator(), new Printer() );

    CashRegister englishCashRegister = new CashRegister( new EnglishTaxCalculator(), new EnglishPrinter() );
   
    cashRegister.PrintBill( items );
    Console.WriteLine( "Cena do zapłaty: {0}\n-------------", cashRegister.CalculatePrice( items ) );

    englishCashRegister.PrintBill( items );
    Console.WriteLine( "Total price: {0}", englishCashRegister.CalculatePrice( items ) );
  }
}