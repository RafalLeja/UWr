import java.util.HashMap;
import java.util.Map;

public class Program {
    public static void main(String[] args) {
        Expression expr = new Add(
            new Const(7), 
            new Pow( 
                new Const(3), 
                new Variable("x")));

        Map<String, Integer> params = new HashMap<String, Integer>();

        params.put("x", 7);

        System.out.println(expr.evaluate(params));
        System.out.println(expr.toString());
    }
}
