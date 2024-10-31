int foo(int a, int b)
{
    int x;
    char y[8];

    return 7;
}

int main(int ac, char* av[])
{
    int f = foo(11, 13);

    return 0;
}

/*
(main) frame has 2 parameters, int and char*, and single local variable main::f
of type int

the value of main::f is to be obtained by calling foo function, in order to do
that, a new local foo::a = 11 and foo:b = 13 are created

then foo function is called with foo::a and foo::b presented as parameters,
main::f stated as return value

foo function has two formal parameters (already placed on top of the stack) and
returns int (space is reserved on stack too) foo declares two local variables
foo::x of type int and
foo::y of type char[8] (this is stack variable despite it is de facto a pointer)

execution of foo yields in 7 written to stack address marked as return value
(main::f) and the function ends, effectively restoring stack pointer to place
where it was before foo was called

now the main::f value is 7.

*/
