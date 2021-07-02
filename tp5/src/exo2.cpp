#include <mpi.h>
#include <iostream>
#include <vector>

#include "./common.cpp"

#define N 100000
#define PI 3.141592653589793238462643
#define PRECISION 0.000001

int get_number_workers() {
  int number_process;
  MPI_Comm_size(MPI_COMM_WORLD, &number_process);
  return number_process;
}

int id_worker(MPI_Comm groupe) {
  int my_id;
  MPI_Comm_rank(groupe, &my_id);
  return my_id;
}

bool search_stop(int in_circle, int number_of_points) {
  std::cout << id_worker(MPI_COMM_WORLD) << ":" <<  in_circle << " " << number_of_points << std::endl;
  return PI - (in_circle / number_of_points) * 4 < PRECISION;
}

int main(int argc, char *argv[]) {
  // initialiser mpi
  int global_in_circle;
  int global_number_of_points;
  std::vector<Position> global_positions;
  MPI_Init(&argc, &argv);

  do {
    auto number_of_point = 1;
    Position local_positions = generate_one_position();
      global_positions.push_back(local_positions);

    int in_circle = is_in_circle(local_positions, 1);

    // some with all process
    MPI_Reduce(&number_of_point, &global_number_of_points, 1, MPI_INT, MPI_SUM,
               0, MPI_COMM_WORLD);
    std::cout << global_number_of_points << std::endl;

    MPI_Reduce(&in_circle, &global_in_circle, 1, MPI_INT, MPI_SUM, 0,
               MPI_COMM_WORLD);

  } while (search_stop(global_in_circle, global_number_of_points));

  // terminer  les instructions MPI
  MPI_Finalize();

  double pi = (global_in_circle / global_number_of_points) * 4;
  std::cout << "pi:" << pi << std::endl;
}
