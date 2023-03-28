/*
 * Rafał Leja
 * PO: lista5 zadanie 2 i 4, wyrażenia arytmetyczne oraz pochodna
 * jdk 20
 */

import java.util.HashMap;
import java.util.Map;

public class Program {
    public static void main(String[] args) {
        Expression expr1 = new Add( // wyrażenie f(x) = 5*x^4 + x^5
            new Mult( 
                new Const(5), 
                new Pow ( 
                    new Variable("x"), 
                    new Const(4))), 
            new Pow( 
                new Variable("x"), 
                new Const( 5 )));

        Expression expr2 = new Sub( // wyrażenie (5*8 - 5^4)
            new Mult(
                new Const(5), 
                new Const(8)), 
            new Pow(
                new Const(5), 
                new Const(4)));

        Map<String, Integer> params = new HashMap<String, Integer>(); //słownik do podawania wartościowań

        params.put("x", 2); //dodanie pary do słownika

        System.out.println("f(x) = " + expr1.toString());
        System.out.println("f(2) = " + expr1.evaluate(params));
        System.out.println("f'(x) = " + expr1.derivative().toString());

        System.out.println( expr2.evaluate() + " = " + expr2.toString());
    }
}
