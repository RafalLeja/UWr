## Kiedy w systemie zachodzi potrzeba przełączenia przestrzeni adresowej?
Przestrzeń adresową przełączamy, gdy zmienia się kontekst: jeden proces zostaje wywłaszczony, ładujemy drugi, który ma swoją własną przestrzeń adresową.

## Czemu należałoby wtedy wyczyścić zawartość TLB?
Jeśli nie wyczyścimy TLB, to proces Y może zacząć grzebać w adresach fizycznych procesu X (bo w TLB będą dane procesu X).

## Czemu chcielibyśmy tego unikać?
Chcemy tego unikać, bo to zwiększyłoby liczbę chybień w TLB, a zatem - wydłużyło czas pracy programu.

## Jak ten problem rozwiązuje wprowadzenie identyfikatorów przestrzeni adresowych
Identyfikatory przestrzeni adresowych rozwiązują ten problem: część wpisu TLB stanowi identyfikator powiązany z procesem. Gdy inny proces będzie próbował sięgnąć do TLB i trafi we właściwy adres wirtualny, ale powiązany z innym procesem, to zostanie to uznane za chybienie.