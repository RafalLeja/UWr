import java.util.HashMap;
import java.util.Map;

public class Program {
    public static void main(String[] args) {
        Expression expr = new Pow( new Variable("x"), new Const( 5 ));

        Map<String, Integer> params = new HashMap<String, Integer>();

        params.put("x", 2);

        //System.out.println(expr.evaluate(params));
        System.out.println(expr.toString());
        System.out.println(expr.derivative().toString());
    }
}
