#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

#define N 1000000
#define PI 3.141592653589793238462643
#define PRECISION 0.000001;

struct Position {
  double x, y;
};

double generate_random() { return (double)(rand() % 200 - 100) / 100; }

Position generate_one_position() {
  return {generate_random(), generate_random()};
}

bool is_in_circle(Position &p, int r) { return p.x * p.x + p.y * p.y < r * r; }

int precision(std::vector<Position> &positions) {
  auto in_circle = 0;

  for (auto &p : positions) {
    if (is_in_circle(p, 1)) {
      in_circle++;
    }
  }

  return in_circle;
}

double compute_pi(std::vector<Position> &positions) {
  return (precision(positions) / (double)N) * 4;
}

bool check_precision(std::vector<Position> &positions) {
  return PI - compute_pi(positions) < PRECISION;
}

bool stop_search(unsigned int number_of_points,
                 std::vector<Position> &positions) {
  return number_of_points >= N && check_precision(positions);
}

double search_pi() {
  unsigned int number_of_points = 0;
  std::vector<Position> positions;
  positions.push_back(generate_one_position());

  while (!stop_search(number_of_points, positions)) {
    positions.push_back(generate_one_position());
    number_of_points++;
  }

  std::cout << "After :" << number_of_points << " points" <<  std::endl;
  return compute_pi(positions);
}

std::string display_position(Position &p) {
  return "(" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  auto pi = search_pi();
  std::cout << "pi: " << pi << std::endl;
}
