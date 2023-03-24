package expression_pack;

public class Program {
    public static void main(String[] args) {
        Expression expr = new Add(new Const(3), new Const(7));
        System.out.println(expr.evaluate());
    }
}
