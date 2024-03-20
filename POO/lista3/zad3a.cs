using System;

public class TaxCalculator {
  public double CalculateTax( double Price ) {
    return Price * 0.22;
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
  public TaxCalculator taxCalc = new TaxCalculator();
  public double CalculatePrice( Item[] Items ) {
    double _price = 0;
    foreach ( Item item in Items ) {
      _price += item.Price + taxCalc.CalculateTax( item.Price );
    }
    return _price;
  }
  public void PrintBill( Item[] Items ) {
    foreach ( var item in Items ) {
      Console.WriteLine( "towar {0} : cena {1} + podatek {2}",
        item.Name, item.Price, taxCalc.CalculateTax( item.Price ) );
    }
  }
}

public class Program {
  public static void Main() {
    Item[] items = new Item[] {
      new Item( "mleko", 2.5 ),
      new Item( "chleb", 3.5 ),
      new Item( "masło", 5.0 )
    };
    CashRegister cashRegister = new CashRegister();
    cashRegister.PrintBill( items );
    Console.WriteLine( "Cena do zapłaty: {0}", cashRegister.CalculatePrice( items ) );
  }
}