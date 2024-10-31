#include <paro/Data.h>

Data* create() { return new Data(0x19); }

void use(Data* p)
{
    if (p) {
        use_data_the_intended_way(p);
        delete p;
    }
}

int main(int argc, char const* argv[])
{
    Data* data = create();
    use(data);
    // ...
    use(data); // data is not NULL!
    return 0;
}
