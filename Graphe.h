#ifndef GRAPHE_H
#define GRAPHE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Noeud.h"
#include "Arc.h"

class Graphe {
private:
    std::unordered_map<std::string, Noeud*> lesnoeuds; // Ensemble de noeuds
    std::unordered_map<std::string, Arc*> lesarcs;     // Ensemble d'arcs
    int nombredenoeuds;
    int nombredarcs;

public:
    Graphe(const std::string& fichierarcs, const std::string& fichiernoeuds);
    ~Graphe();

    // Méthodes pour gérer les arcs
    int lecture_arcs(const std::string& nom_fichier);
    void ajouterArc(Arc* arc);
    Arc* rechercherArc(const std::string& id) const;
    void afficherArcs() const;

    // Méthodes pour gérer les noeuds
    int lecture_noeuds(const std::string& nom_fichier);
    void ajouterNoeud(Noeud* noeud);
    Noeud* rechercherNoeud(const std::string& id) const;
    void afficherNoeuds() const;

    void liste_incidence();
    void degre(int n);
    bool chemin(const std::string& o, const std::string& d);
    int pluscourtchemin(const std::string& o, const std::string& d); // Méthode pour trouver le plus court chemin
    void affiche() const; // Méthode pour afficher le graphe
};

#endif // GRAPHE_H