#include "Noeud.h"
#include <iostream>

// Constructeur
Noeud::Noeud(const std::string& id, double latitude, double longitude, int street_count)
    : id(id), latitude(latitude), longitude(longitude), street_count(street_count), visite(false) {}

// Destructeur
Noeud::~Noeud() {}

// Méthode pour afficher les détails du noeud
void Noeud::affiche() const {
    std::cout << "Noeud: " << id << " at (" << latitude << ", " << longitude << "), Street Count: " << street_count << std::endl;
}