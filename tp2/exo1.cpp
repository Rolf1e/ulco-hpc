#include <iostream>
#include <thread>
#include <cmath>
#include <vector>


// compilation : g++ -std=c++11 -pthread exo1.cpp -o exo1 

#define N 10000000

// fonction calculant la somme des entiers entre i0 et i1
void somme(int id, int i0, int i1) {
  std::cout << "Début du thread: " << id  << std::endl;
  double res=0;
  for (int i=i0; i<i1; i++)
     res += i;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Fin du thread: " << id  << std::endl;
}
    
int main(int argc, char *argv[]){
  
  std::cout << "Début du main " << std::endl;

  // lancer les threads
  std::thread thread1(somme, 0, 0, N/2); // appel non bloquant
  std::thread thread2(somme, 1, N/2, N); // appel non bloquant

  std::cout << "Milieu du main " << std::endl;
  
  //attendre la fin des calculs
  thread1.join(); // appel bloquant
  thread2.join(); // appel bloquant

  std::cout << "Fin du main" << std::endl;

  return 1;
}
