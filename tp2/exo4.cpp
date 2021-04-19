#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <mutex>
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

void add_to_result(Result &result, Result add) {
  mtx.lock();

  result = {
      result.normal = result.normal + add.normal,
      result.square = result.square + add.square,
      result.square_log = result.square_log + add.square_log,
  };

  mtx.unlock();
}

void protected_cout(std::string message) {
  mtx.lock();
  std::cout << message << std::endl;
  mtx.unlock();
}

double somme_square(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += std::sqrt(i);
  return res;
}

double somme_square_log(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += std::sqrt(i) * std::log(i);
  return res;
}

// fonction calculant la somme des entiers entre i0 et i1
double somme(int i0, int i1) {
  auto res = 0.0;
  for (int i = i0; i < i1; i++) res += i;
  return res;
}

void all_somme(Result &result, int i0, int i1) {
  auto normal = somme(i0, i1);
  auto square = somme_square(i0, i1);
  auto square_log = somme_square_log(i0, i1);

  struct Result add = {normal, square, square_log};

  add_to_result(result, add);
}

int main(int argc, char *argv[]) {
  auto number_of_execution = 10;
  auto length = N / number_of_execution;
  std::vector<std::thread> threads;

  // lancer les threads

  struct Result result = {0.0, 0.0, 0.0};
  std::cout << "==== Parallel ====" << std::endl;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  auto first_borne = 0;
  auto second_borne = first_borne + length;

  for (int i = 0; i < number_of_execution; ++i) {
    threads.push_back(std::thread(all_somme, std::ref(result), first_borne,
                                  second_borne));  // appel non bloquant
    first_borne = second_borne;
    second_borne = first_borne + length;
  }
  // attendre la fin des calculs
  for (auto &thread : threads) {
    thread.join();
  }

  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << "Parallel elapsed time: "
            << std::to_string(elapsed_seconds.count())
            << "\nres: " << result.normal << "\nres(square): " << result.square
            << "\nres(square_log): " << result.square_log << std::endl;

  std::cout << "==== Sequential ====" << std::endl;

  result = {0.0, 0.0, 0.0};
  start = std::chrono::system_clock::now();
  all_somme(result, 0, N);

  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;

  std::cout << "Sequential elapsed time: "
            << std::to_string(elapsed_seconds.count())
            << "\nres: " << result.normal << "\nres(square): " << result.square
            << "\nres(square_log): " << result.square_log << std::endl;

  std::cout << "Fin du main" << std::endl;

  return 1;
}
