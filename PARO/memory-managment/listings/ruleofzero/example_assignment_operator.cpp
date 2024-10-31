#include <cstddef>
#include <cstring>

struct Nickname
{
    Nickname(const char* input)
    {
        if (input) {
            std::size_t n = std::strlen(input) + 1;
            nick_ = new char[n];
            std::memcpy(nick_, input, n);
        }
    }
    Nickname(const Nickname& other) {
        if (other.nick_) {
            std::size_t n = std::strlen(other.nick_) + 1;
            nick_ = new char[n];
            std::memcpy(nick_, other.nick_, n);
        }
    }
    Nickname& operator=(const Nickname& other) {
        if (other.nick_) {
            std::size_t n = std::strlen(other.nick_) + 1;
            nick_ = new char[n];
            std::memcpy(nick_, other.nick_, n);
        }
        return *this;
    }
    ~Nickname() { if (nick_) delete[] nick_; }

private:
    char* nick_ = nullptr;
};

int main()
{
    Nickname n1("Whatever");
    // copy constructor written by hand
    Nickname n2(n1);
    // copy assignment written by hand
    Nickname n3 = n2;
} // n3, n2, n1 go out-of-scope; destructors called;
  // everything works fine... for now...
