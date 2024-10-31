#include <cstddef>
#include <cstring>
#include <utility>

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

    ~Nickname() { delete[] nick_; }

    Nickname(const Nickname& other)
        : Nickname(other.nick_) {}

    Nickname& operator=(const Nickname& other)
    {
        if (this == &other)
            return *this;

        std::size_t n = std::strlen(other.nick_) + 1;
        char* new_nick = new char[n];
        std::memcpy(new_nick, other.nick_, n);
        delete[] nick_;

        nick_ = new_nick;
        return *this;
    }

    Nickname(Nickname&& other) noexcept
        : nick_(std::exchange(other.nick_, nullptr))
    {}

    Nickname& operator=(Nickname&& other) noexcept
    {
        std::swap(nick_, other.nick_);
        return *this;
    }

private:
    char* nick_ = nullptr;
};

int main()
{
    Nickname n1("Whatever");
    // copy constructor is defined by us now
    Nickname n2(n1);
    // same for copy assignment operator
    Nickname n3 = n2;
    // ditto for move
    Nickname n4 = std::move(n3);
} // n4, n3, n2, n1 go out-of-scope; destructors called;
  // everything works correctly
