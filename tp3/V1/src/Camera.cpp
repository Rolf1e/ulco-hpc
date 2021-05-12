#include "Camera.hpp"
#include <thread>
#include "./objects/Rayon.hpp"

Camera::Camera() {
  position = Point(0.0, 0.0, 2.0);
  ;
  cible = Point(0.0, 0.0, 0.0);
  distance = 2.0;
}

Camera::~Camera() {}

void Camera::genererImage(const Scene& sc, Image& im, int profondeur) {
  // Calcul des dimensions d'un pixel par rapport
  // à la résolution de l'image - Les pixels doivent être carrés
  // pour éviter les déformations de l'image.
  // On fixe :
  // - les dimensions en largeur de l'écran seront comprises dans [-1, 1]
  // - les dimensions en hauteur de l'écran soront comprises dans [-H/L, H/L]
  float cotePixel = 2.0 / im.getLargeur();

  // Pour chaque pixel
  for (int i = 0; i < im.getLargeur(); i++) {
    for (int j = 0; j < im.getHauteur(); j++) {
      // calcul des coordonnées du centre du pixel
      float milieuX = -1 + (i + 0.5f) * cotePixel;
      float milieuY = (float)im.getHauteur() / (float)im.getLargeur() -
                      (j + 0.5f) * cotePixel;

      Point centre(milieuX, milieuY, 0);

      // Création du rayon
      Vecteur dir(position, centre);
      dir.normaliser();
      Rayon ray(position, dir);

      // Lancer du rayon primaire
      Intersection inter;
      if (sc.intersecte(ray, inter)) {
        im.setPixel(i, j, inter.getCouleur(sc, position, profondeur));
      } else
        im.setPixel(i, j, sc.getFond());

    }  // for j

  }  // for i
}

void Camera::genererImageParallele(const Scene& sc, Image& im, int profondeur,
                                   int nbThreads) {
  std::vector<std::thread> threads;

  auto img_width = im.getLargeur();
  auto img_height = im.getHauteur();
  auto zone_height = img_height / nbThreads;

  for (int i = 0; i < img_height; i++) {
    if (i == img_width - 1 || (i != 0 && i % zone_height == 0)) {  // On arrive a la zone suivante
      threads.push_back(std::thread(calculeZone, std::ref(sc), std::ref(im),
                                    profondeur, zone{0, i, img_width, i},
                                    std::ref(this->position)));
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

ostream& operator<<(ostream& out, const Camera& c) {
  out << " position = " << c.position << " - cible = " << c.cible;
  out << " - distance = " << c.distance << flush;
  return out;
}
