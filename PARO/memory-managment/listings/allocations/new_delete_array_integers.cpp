int main(int ac, char* av[])
{
    int* arr = new int[40];
    arr[34] = 9;
    arr[37] = 21;
    delete[] arr;

    return 0;
}
