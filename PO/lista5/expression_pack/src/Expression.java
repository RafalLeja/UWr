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

    public int evaluate() {
        if (!operator) {
            return val;
        }

        int l = left.evaluate();
        int r = right.evaluate();

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

    public int evaluate(Map<String, Integer> params) {
        if (!operator) {
            return val;
        }

        if (val < 0) {
            if (params.get(var) == null) {
                return Integer.MAX_VALUE;
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

    public Expression derivative() {
        if (!operator) {
            return new Const(0);
        }

        if (val < 0) {
            return new Const(0);
        }

        Expression l = left.derivative();
        Expression r = right.derivative();

        switch (val) {
            case 0:
                return new Add(l, r);
            
            case 1:
                return new Sub(l, r);

            case 2:
                return new Mult(l, r);
                
            case 3:
                return new Div(l, r);

            case 4:
                if (left.operator && left.val < 0) {
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
                return ( "( " + l + " + " + r + " )");

            case 1:
                return ( "( " + l + " - " + r + " )");

            case 2:
                return ( "( " + l + " * " + r + " )");

            case 3:
                return ( "( " + l + " / " + r + " )");
                
            case 4:
                return ( "( " + l + "**" + r + " )");

            default:
                return "";
        }
    } 

}
