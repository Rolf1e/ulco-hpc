#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

#include "./infra/Point.hpp"
#include "./infra/Vecteur.hpp"
#include "Image.hpp"
#include "Scene.hpp"

/**
 * \class Camera
 * Classe représentant une caméra virtuelle simplifiée, générant des images
 * à l'aide de l'algorithme de lancer de rayons.
 *
 * @author  C. Renaud
 * @version 1.0
 * @date Janvier 2021
 * @remark Cette classe fait partie de l'application de lancer de rayons
 * simplifiée développée pour servir d'exemple aux travaux pratiques dans les
 * modules "High Parallel Computing" et "Initiation à la recherche" du master
 * informatique de l'Université du Littoral Côte d'Opale.
 *
 */

struct zone {
  int x, y;              // coordonnées du coin supérieur gauche de la zone
  int largeur, hauteur;  // dimensions de la zone
};

class Camera {
 private:
  Point position; /**< Position de la caméra */
  Point cible; /**< Point visé par la caméra. Ce point sera au centre de l'image
                */
  float distance; /**< distance de l'origine de la caméra au plan image */

 public:
  /**
   * Construit une caméra positionnée aux coordonnées (0, 0, 2).
   * Le point visé est l'origine du repère (0, 0, 0) et la distance au plan
   * image est fixée à 2.
   */
  Camera();

  /**
   * Détruit la caméra.
   */
  ~Camera();

  /**
   *  Calcul de l'image d'une scène telle que vue par la caméra. La méthode
   * de calcul est le lancer de rayons récursif.
   * @param sc la scène virtuelle à utiliser pour la génération de l'image
   * @param im l'image à générer par lancer de rayons
   * @param profondeur nombre de réflexions à prendre en compte dans le
   * processus récursif.
   */
  void genererImage(const Scene& sc, Image& im, int profondeur);

  /**
   * Affichage des paramètres d'une caméra sur un flot de sortie,
   * dans un format lisible par un utilisateur humain.
   * @param out le flot de sortie
   * @param c la caméra à afficher
   * @return le flot modifié
   */
  friend ostream& operator<<(ostream& out, const Camera& c);

  void genererImageParallele(const Scene& sc, Image& im, int profondeur,
                             int nbThreads);

  static void protected_cout(std::string message) {
    std::mutex mtx;
    mtx.lock();
    std::cout << message << std::endl;
    mtx.unlock();
  }

  static void calculeZone(const Scene& sc, Image& im, int profondeur,
                          const zone& area, const Point& position) {
    protected_cout("zone x: " + std::to_string(area.x) +
                   " y:" + std::to_string(area.y) +
                   " l:" + std::to_string(area.largeur) +
                   " h:" + std::to_string(area.hauteur));
    std::mutex mtx;

    float cotePixel = 2.0 / im.getLargeur();

    // Pour chaque pixel
    auto width = area.largeur;
    auto height = area.hauteur;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        // calcul des coordonnées du centre du pixel
        float milieuX = -1 + (i + 0.5f) * cotePixel;
        float milieuY = (float)width / (float)height - (j + 0.5f) * cotePixel;

        Point centre(milieuX, milieuY, 0);

        // Création du rayon
        Vecteur dir(position, centre);
        dir.normaliser();
        Rayon ray(position, dir);

        // Lancer du rayon primaire
        Intersection inter;

        mtx.lock();
        if (sc.intersecte(ray, inter)) {
          im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
        } else {
          im.setPixel(i, j, sc.getFond());
        }
        mtx.unlock();
      }
    }

     std::cout << "thread : " << std::this_thread::get_id() << std::endl;
  }
};

#endif
