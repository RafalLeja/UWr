import java.util.Map;

public class Expression {
    public boolean operator;
    public String var;
    public int val;
    public Expression left;
    public Expression right;

    Expression(boolean operator, String var, int val, Expression left, Expression right) {
        this.operator = operator;
        this.var = var;
        this.val = val;
        this.left = left;
        this.right = right;
    }

    // funkcja obliczająca wyrażenie
    public int evaluate() {
        if (!operator) { // sprawdzanie czy wyrażenie jest stałą
            return val;
        }

        // obliczanie wartości gałężi wyrażenia
        int l = left.evaluate();
        int r = right.evaluate();

        // rozpatrzenie wszystkich przypadków
        switch (val) {
            case 0:
                return ( l + r );

            case 1:
                return ( l - r);

            case 2:
                return ( l * r );

            case 3:
                return ( l / r);
                
            case 4:
                return (int) Math.pow(l, r);

            // przypadek gdy w wyrażeniu jest zmienna a nie podaliśmy wartościowania
            default:
                throw new Error(
                    "W wyrażeniu znajduje się zmienna, a nie podano wartościowania");
        }
    }

    // duplikacja funkcji, tym razem ze słownikiem wartościowań jako argument
    public int evaluate(Map<String, Integer> params) {
        if (!operator) {
            return val;
        }

        if (val < 0) { // przypadek gdy wyrażenie jest zmienną
            if (params.get(var) == null) {
                throw new Error(
                    "W wyrażeniu znajduje się zmienna, dla której nie podano wartościowania");
            }
            return (int) params.get(var);
        }

        int l = left.evaluate(params);
        int r = right.evaluate(params);

        switch (val) {
            case 0:
                return ( l + r );

            case 1:
                return ( l - r);

            case 2:
                return ( l * r );

            case 3:
                return ( l / r);

            case 4:
                return (int) Math.pow(l, r);

            default:
                return Integer.MAX_VALUE;
        }
    }

    // funkcja zwracająca pochodną
    public Expression derivative() {
        if (!operator) {
            return new Const(0);
        }

        if (val < 0) {
            return new Const(1);
        }

        Expression l = left.derivative();
        Expression r = right.derivative();

        switch (val) {
            case 0:
                return new Add(l, r);
            
            case 1:
                return new Sub(l, r);

            case 2:
                if (right.operator && right.val < 0) { // przypdek stała * x^?
                    return new Mult(left, r);
                }
                return new Mult(l, r);

            case 3:
                return new Div(l, r);

            case 4:
                if (left.operator && left.val < 0) { // przypadek x^?
                    return new Mult( right, new Pow( left, new Sub( right, new Const( 1 ) ) ) );
                }
                return new Pow( l, r );

            default:
                return new Const(0);
        }
    }

    public String toString() {
        if (!operator) {
            return Integer.toString(val);
        }

        if (val < 0) {
            return var;
        }

        String l = left.toString();
        String r = right.toString();

        switch (val) {
            case 0:
                return ( "(" + l + " + " + r + ")");

            case 1:
                return ( "(" + l + " - " + r + ")");

            case 2:
                return ( "(" + l + " * " + r + ")");

            case 3:
                return ( "(" + l + " / " + r + ")");
                
            case 4:
                return ( "(" + l + "^" + r + ")");

            default:
                return "";
        }
    } 

}
