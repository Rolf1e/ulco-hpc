#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// compilation : g++ -std=c++11 -pthread exo2.cpp -o exo2

#define N 10000000

std::mutex mtx;

struct Result {
  double normal;
  double square;
  double square_log;
};

void somme_sqare(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += std::sqrt(i);
}

void somme_sqare_log(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += std::sqrt(i) * std::log(i);
}

// fonction calculant la somme des entiers entre i0 et i1
void somme(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += i;
}

int main(int argc, char *argv[]) {
  auto number_of_execution = 3;
  std::vector<std::thread> threads;

  // lancer les threads

  std::cout << "Parallel" << std::endl;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  threads.push_back(std::thread(somme, 0, N));
  threads.push_back(std::thread(somme_sqare, 0, N));
  threads.push_back(std::thread(somme_sqare_log, 0, N));
  // attendre la fin des calculs
  for (auto &thread : threads) {
    thread.join();
  }

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Parallel elapsed time: "
            << std::to_string(elapsed_seconds.count()) << std::endl;

  std::cout << "Sequential" << std::endl;

  start = std::chrono::system_clock::now();

  somme(0, N);
  somme_sqare(0, N);
  somme_sqare_log(0, N);

  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;

  std::cout << "Sequential elapsed time: "
            << std::to_string(elapsed_seconds.count()) << std::endl;

  std::cout << "Fin du main" << std::endl;

  return 1;
}
