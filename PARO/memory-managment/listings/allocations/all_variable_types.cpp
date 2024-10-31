int global_variable = 11;

int main(int ac, char* av[])
{
    static int static_variable = 22;
    int automatic_variable = 33;
    int* heap_variable = new int(44);
    delete heap_variable;

    return 0;
}
