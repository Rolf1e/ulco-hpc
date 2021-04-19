#include <immintrin.h>
#include <iostream>
#include <string>

// programme d'évaluation du gain obtenu en utilisant les routines AVX
// pour le calcul de produits scalaires
// utilise les routines AVX et AVX2 (pour les doubles)
// Compilation : g++  -std=c++11 -march=native -O2 ps.cpp -o ps
//     ou      : g++  -std=c++11 -mavx -mavx2 -O2 ps.cpp -o ps

#define NB 30000     // nombre de fois où le produit scalaire est effectué
#define SIZE 100000  // taille des vecteurs utilisés

// -------------------------------------------
// Fonctions d'affichage
// -------------------------------------------
// affiche les 8 réels contenus dans un __m256
void show_v(std::string s, __m256 *v);

// -------------------------------------------
// Fonctions de calcul
// -------------------------------------------
// calcul des produits scalaires sous forme de vecteurs d'entiers
void ps_int(int size);

// calcul des produits scalaires sous forme de vecteurs de float
void ps_float(int size);

// calcul des produits scalaires sous forme de vecteurs de double
void ps_double(int size);

int main(int argc, char *argv[]) {
  ps_float(SIZE);

  return 0;
}

void show_v(std::string s, __m256 *v) {
  auto value = (float *)v;
  std::cout << s << ": ";
  for (int i = 0; i < 8; i++) {
    std::cout << value[i] << '|';
  }
  std::cout << std::endl;
}

// effectue les ps séquentiel ou avx sur des réels simple précision
// et affiche le temps de calcul correspondants
void ps_float(int size) {
  clock_t start;

  // initialisation des deux vecteurs réels
  alignas(32) float *v1, *v2;  // alignement sur 32 bits pour AVX

  v1 = (float *)_mm_malloc(size * sizeof(float), 32);
  v2 = (float *)_mm_malloc(size * sizeof(float), 32);

  // initialisation avec des valeurs aléatoires dans [0,9]
  for (int i = 0; i < size; i++) {
    v1[i] = (float)(rand() % 10);
    v2[i] = (float)(rand() % 10);
  }

  // produit scalaire séquentiel
  start = clock();

  float somme;
  __m256 sum = _mm256_setzero_ps();
  for (int n = 0; n < NB; n++) {
    somme = 0;
    if (n == 0) {
      show_v("init", &sum);
    }

    for (int i = 0; i < size; i++) {
      somme += v1[i] * v2[i];
    }

    for (size_t i = 0; i < size; i += 8) {
      // scalaire - mm256
      auto mm256_v1 = _mm256_load_ps(v1 + i);
      auto mm256_v2 = _mm256_load_ps(v2 + i);
      auto scalaire = _mm256_mul_ps(mm256_v1, mm256_v2);

      sum = _mm256_add_ps(sum, scalaire);
    }
  }

  float t1;
  std::cout << "temps ps float seq = "
            << (t1 = (clock() - start) / (double)CLOCKS_PER_SEC);
  std::cout << " secondes - valeur = " << somme << std::endl;

  float somme_awx = 0;
  show_v("end", &sum);
  for (int i = 0; i < 8; i++) {
    somme_awx += sum[0];
  }
  std::cout << "secondes - valeur = " << somme_awx << std::endl;
  // produit scalaire  avx

  // affichage du speedup

  // désallocation mémoire
  _mm_free(v1);
  _mm_free(v2);
}
