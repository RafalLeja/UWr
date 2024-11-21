#pragma once
#include <queue>

struct Queue
{
public:
  struct Entry
  {
    unsigned n_;
    bool     isPrime_;
  };

private:
  using Container = std::queue<Entry>;

public:
  using size_type  = Container::size_type;
  using value_type = Container::value_type;

  void push(const value_type v)
  {
    q_.push(v);
  }

  value_type pop()
  {
    const auto tmp = q_.front();
    q_.pop();
    return tmp;
  }

  bool empty() const
  {
    return q_.empty();
  }

  size_type size() const
  {
    return q_.size();
  }

private:
  Container q_;
};
