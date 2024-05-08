using System;

public abstract class CoffeeMachineState
{
    protected CoffeeMachine coffeeMachine { get; set; }

    public abstract void RefillCoffee();
    public abstract void SelectBeverage();
    public abstract void DispenseBeverage();
}

public class NoCoffeeState : CoffeeMachineState
{
    public NoCoffeeState(CoffeeMachine coffeeMachine)
    {
        this.coffeeMachine = coffeeMachine;
    }

    public override void RefillCoffee()
    {
        Console.WriteLine("Coffe refilled.");
        this.coffeeMachine.SetState(new StanbyState(this.coffeeMachine));
    }

    public override void SelectBeverage()
    {
        Console.WriteLine("Please refill coffee.");
    }

    public override void DispenseBeverage()
    {
        Console.WriteLine("Please refill coffee.");
    }
}

public class StanbyState : CoffeeMachineState
{
    public StanbyState(CoffeeMachine coffeeMachine)
    {
        this.coffeeMachine = coffeeMachine;
    }

    public override void RefillCoffee()
    {
        Console.WriteLine("Coffee full.");
    }

    public override void SelectBeverage()
    {
        Console.WriteLine("Beverage selected.");
        this.coffeeMachine.SetState(new DispensingState(this.coffeeMachine));
    }

    public override void DispenseBeverage()
    {
        Console.WriteLine("Please select a beverage first.");
    }
}

public class DispensingState : CoffeeMachineState
{
    public DispensingState(CoffeeMachine coffeeMachine)
    {
        this.coffeeMachine = coffeeMachine;
    }

    public override void RefillCoffee()
    {
        Console.WriteLine("Cannot refill coffee while dispensing.");
    }

    public override void SelectBeverage()
    {
        Console.WriteLine("Cannot select beverage while dispensing.");
    }

    public override void DispenseBeverage()
    {
        Console.WriteLine("Beverage dispensed.");
        this.coffeeMachine.SetState(new StanbyState(this.coffeeMachine));
    }
}

public class CoffeeMachine
{
    private CoffeeMachineState currentState;

    public CoffeeMachine()
    {
        currentState = new NoCoffeeState(this);
    }

    public void SetState(CoffeeMachineState state)
    {
        currentState = state;
    }

    public void RefillCoffee()
    {
        currentState.RefillCoffee();
    }

    public void SelectBeverage()
    {
        currentState.SelectBeverage();
    }

    public void DispenseBeverage()
    {
        currentState.DispenseBeverage();
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        CoffeeMachine coffeeMachine = new CoffeeMachine();

        coffeeMachine.DispenseBeverage();
        coffeeMachine.SelectBeverage();
        coffeeMachine.RefillCoffee();
        coffeeMachine.DispenseBeverage();
        coffeeMachine.SelectBeverage();
        coffeeMachine.DispenseBeverage();
        coffeeMachine.DispenseBeverage();
    }
}