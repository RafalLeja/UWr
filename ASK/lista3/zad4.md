$a = 3.984375\cdot 10^{-1} = 0.3984375 = 0.0110011111_{(2)} = 1.1001111100_{(2)} \cdot 2^{-2}$

$b = 3.4375 \cdot 10^{-1} = 0.34375 = 0.0101111111_{(2)} = 1.0111111100 \cdot 2^{-2}$

$c = 1.771 \cdot 10^3 = 1771 = 11011101011_{(2)} = 1.1011101011 \cdot 2^{10}$

$(a + b) = 11.000111100 * 2^{-2} = 1.1000111100 * 2^{-1}$

$1.1000111100 * 2^{-1} + 1.1011101011 * 2^{10} = 
(1.1000111100 + 110111010110) * 2^{-1} = 
110111010111.1000111100 * 2^{-1} = 1.1011101011 * 2^{10} = 1772$

``` 0 11001 101110110 ```

$a+(b+c) = c$

``` 0 11001 1011101011```

guard = ostatni pozostały bit
round = pierwszy usunięty bit
sticky = ^ ucinanych bitów

r & (g | s)