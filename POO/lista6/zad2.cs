using System;
using System.Collections.Generic;


public class Context {
  private Dictionary<string, bool> Variables = new Dictionary<string, bool>();
  public bool GetValue( string VariableName ) { 
    if( Variables.ContainsKey( VariableName ) ) {
      return Variables[VariableName];
    } else {
      throw new ArgumentException();
    }  
  }
  public bool SetValue( string VariableName, bool Value ) { 
    if( Variables.ContainsKey( VariableName ) ) {
      return false;
    } else {
      Variables.Add( VariableName, Value );
      return Value;
    }
  }
}

public abstract class AbstractExpression {
  public abstract bool Interpret( Context context );
}
public class ConstExpression : AbstractExpression { 
  private bool Value;
  public ConstExpression( bool Value ) {
    this.Value = Value;
  }
  public override bool Interpret( Context context ) {
    return Value;
  }
}
public class VariableExpression : AbstractExpression { 
  private string VariableName;
  public VariableExpression( string VariableName ) {
    this.VariableName = VariableName;
  }
  public override bool Interpret( Context context ) {
    try {
      return context.GetValue( VariableName );
    } catch( ArgumentException ) {
      throw new ArgumentException( "Undefined variable: " + VariableName );
    }
  }
}
public class BinaryExpression : AbstractExpression { 
  private AbstractExpression Left;
  private AbstractExpression Right;
  private Func<bool, bool, bool> Operator;
  public BinaryExpression( AbstractExpression Left, AbstractExpression Right, Func<bool, bool, bool> Operator ) {
    this.Left = Left;
    this.Right = Right;
    this.Operator = Operator;
  }
  public override bool Interpret( Context context ) {
    return Operator( Left.Interpret( context ), Right.Interpret( context ) );
  }  
}
public class UnaryExpression : AbstractExpression { 
  private AbstractExpression Operand;
  private Func<bool, bool> Operator;
  public UnaryExpression( AbstractExpression Operand, Func<bool, bool> Operator ) {
    this.Operand = Operand;
    this.Operator = Operator;
  }
  public override bool Interpret( Context context ) {
    return Operator( Operand.Interpret( context ) );
  }
}

public class Client {
  public static void Main() {
    Context ctx = new Context();
    ctx.SetValue( "x", false );
    ctx.SetValue( "y", true );
    AbstractExpression exp = 
      new BinaryExpression(
        new UnaryExpression(
          new BinaryExpression( 
            new UnaryExpression( new VariableExpression( "x" ), x => !x ), 
            new VariableExpression( "y" ), 
            (x, y) => x && y 
          ),
        x => !x),
        new ConstExpression( false ),
        (x, y) => x || y);
    bool Value = exp.Interpret( ctx );
    Console.WriteLine( Value );
  }
}