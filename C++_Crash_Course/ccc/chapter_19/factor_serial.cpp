#include <array>
#include <chrono>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Stopwatch {
  Stopwatch(std::chrono::nanoseconds& result)
      : result{ result }
      , start{ std::chrono::high_resolution_clock::now() } {}
  ~Stopwatch() {
    result = std::chrono::high_resolution_clock::now() - start;
  }

  private:
  std::chrono::nanoseconds& result;
  const std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

template <typename T>
set<T> factorize(T x) {
  set<T> result{ 1 };
  for(T candidate = 2; candidate <= x; candidate++) {
    if(x % candidate == 0) {
      result.insert(candidate);
      x /= candidate;
      candidate = 1;
    }
  }
  return result;
}

string factor_task(unsigned long long x) {
  chrono::nanoseconds elapsed_ns;
  set<unsigned long long> factors;
  {
    Stopwatch stopwatch{ elapsed_ns };
    factors = factorize(x);
  }
  const auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed_ns).count();
  stringstream ss;
  ss << elapsed_ms << " ms: Factoring " << x << " ( ";
  for(auto factor : factors)
    ss << factor << " ";
  ss << ")\n";
  return ss.str();
}

array<unsigned long long, 6> numbers{ 9'699'690,     179'426'549,   1'000'000'007,
                                      4'294'967'291, 4'294'967'296, 1'307'674'368'000 };

int main() {
  chrono::nanoseconds elapsed_ns;
  {
    Stopwatch stopwatch{ elapsed_ns };
    for(auto number : numbers)
      cout << factor_task(number);
  }
  const auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed_ns).count();
  cout << elapsed_ms << "ms: total program time\n";
}
