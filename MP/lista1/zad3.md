1. ```(* (+ 2 2) 5)``` ok -> 20
2. ```(* (+ 2 2) (5))``` błąd -> not a procedure (5)
3. ```(*(+(2 2) 5))``` błąd -> not a procedure (2 2)
4. ```(*(+ 2 2)5)``` ok -> 20
5. ```(5 * 4)``` błąd -> not a procedure (5 * 4)
6. ```(5 * (2 + 2))``` błąd -> not a procedure (2 + 2)
7. ```((+ 2 3))``` błąd -||-
8. ```(* 2 +)``` ok -> 12
9. ```(five)``` ok -> 5
10. ```four``` ok -> 4
11. ```five``` ok -> #<procedure:five>
12. ```(four)``` błąd -> not a procedure








