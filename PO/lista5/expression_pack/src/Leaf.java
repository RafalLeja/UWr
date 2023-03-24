class Const extends Expression {
    public Const(int val){
        super(false, "", val, null, null);
    }
}

class Variable extends Expression {
    public Variable(String name) {
        super(true, name, -1, null, null);
    }
}
