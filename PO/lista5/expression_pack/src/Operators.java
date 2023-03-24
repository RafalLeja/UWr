class Add extends Expression {
    public Add(Expression left, Expression right) {
        super(true, "", 0, left, right);
    }
}

class Sub extends Expression {
    public Sub(Expression left, Expression right) {
        super(true, "", 1, left, right);
    }
}

class Mult extends Expression {
    public Mult(Expression left, Expression right) {
        super(true, "", 2, left, right);
    }
}

class Div extends Expression {
    public Div(Expression left, Expression right) {
        super(true, "", 3, left, right);
    }
}

class Pow extends Expression {
    public Pow(Expression left, Expression right) {
        super(true, "", 4, left, right);
    }
}