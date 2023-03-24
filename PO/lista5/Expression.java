package expression_pack;

public class Expression {
    public boolean operator;
    public int val;
    public Expression left;
    public Expression right;

    Expression(boolean operator, int val, Expression left, Expression right) {
        this.operator = operator;
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

            default:
                return Integer.MAX_VALUE;
        }
    }

    public String toString() {
        if (!operator) {
            return Integer.toString(val);
        }

        String l = left.toString();
        String r = right.toString();

        switch (val) {
            case 0:
                return ( l + " + " + r );

            case 1:
                return ( l + " - " + r);

            case 2:
                return ( l + " * " + r );

            case 3:
                return ( l + " / " + r);

            default:
                return "";
        }
    } 

}
