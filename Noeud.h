#ifndef NOEUD_H
#define NOEUD_H

#include <string>
#include <vector>
#include "Arc.h"

class Noeud {
public:
    std::string id; // Identifiant du noeud
    double latitude; // Latitude du noeud
    double longitude; // Longitude du noeud
    int street_count; // Nombre de rues passant par ce noeud
    std::vector<Arc*> arcs_sortants; // Liste des arcs sortants
    std::vector<Arc*> arcs_entrants;  // Liste des arcs entrants
    bool visite; // Attribut pour marquer si le noeud a été visité

    // Constructeur
    Noeud(const std::string& id, double latitude, double longitude, int street_count);
    
    // Destructeur
    ~Noeud();

    // Méthode pour afficher les détails du noeud
    void affiche() const;
};

#endif // NOEUD_H