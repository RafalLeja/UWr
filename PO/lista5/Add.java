package expression_pack;

public class Add extends Expression {
    public Add(Expression left, Expression right) {
        super(true, 1, left, right);
    }
}
