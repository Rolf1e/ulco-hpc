#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
#include <mutex>
#include <string>


// compilation : g++ -std=c++11 -pthread exo2.cpp -o exo2

#define N 10000000

std::mutex mtx;

void protected_cout(std::string message) {
  mtx.lock();  
  std::cout << message << std::endl;
  mtx.unlock();  
}

// fonction calculant la somme des entiers entre i0 et i1
void somme(int id, int i0, int i1) {
  auto s_id = std::to_string(id);
  protected_cout("Début du thread: " + s_id);
  double res=0;
  for (int i=i0; i<i1; i++)
     res += i;

  std::this_thread::sleep_for(std::chrono::seconds(1));
  protected_cout("Fin du thread: " + s_id);
}

    
int main(int argc, char *argv[]){
  
  std::vector<std::thread> threads;
  std::cout << "Début du main " << std::endl;

  // lancer les threads
  for(int i = 0; i < 10; ++i) {
      threads.push_back(std::thread(somme, i, 0, N/2)); // appel non bloquant
  }

  std::cout << "Milieu du main " << std::endl;
  
  //attendre la fin des calculs
  for(auto &thread: threads) {
    thread.join();
  }
  std::cout << "Fin du main" << std::endl;

  return 1;
}
