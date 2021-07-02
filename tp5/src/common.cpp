#include <iostream>
#include <vector>

struct Position {
  double x, y;
};

double generate_random() { return (double)(rand() % 200 - 100) / 100; }

Position generate_one_position() {
  return {generate_random(), generate_random()};
}

std::vector<Position> generate_n_positions(int n) {
  std::vector<Position> positions;
  for (unsigned int i = 0; i < n; ++n) {
    positions.push_back(generate_one_position());
  }
  return positions;
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

double compute_pi(std::vector<Position> &positions, int n) {
  return (precision(positions) / (double)n) * 4;
}

bool check_precision(std::vector<Position> &positions, double precision,
                     double pi, int n) {
  return pi - compute_pi(positions, n) < precision;
}

bool stop_search(unsigned int number_of_points,
                 std::vector<Position> &positions, double precision, double pi,
                 int n) {
  return number_of_points >= n && check_precision(positions, precision, pi, n);
}
