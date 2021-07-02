#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#include "./common.cpp"

#define N 1000000
#define PI 3.141592653589793238462643
#define PRECISION 0.000001


double search_pi(int n, double precision, double pi) {
  unsigned int number_of_points = 0;
  std::vector<Position> positions;
  positions.push_back(generate_one_position());

  while (!stop_search(number_of_points, positions, precision, pi, n)) {
    positions.push_back(generate_one_position());
    number_of_points++;
  }

  std::cout << "After :" << number_of_points << " points" << std::endl;
  return compute_pi(positions, n);
}

std::string display_position(Position &p) {
  return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  auto pi = search_pi(N, PRECISION, PI);
  std::cout << "pi: " << pi << std::endl;
}
