#include "Graphe.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <queue>
#include <unordered_map>
#include <algorithm>

Graphe::Graphe(const std::string& fichierarcs, const std::string& fichiernoeuds) {
    nombredenoeuds = lecture_noeuds(fichiernoeuds);
    nombredarcs = lecture_arcs(fichierarcs);
}

Graphe::~Graphe() {
    for (auto& pair : lesnoeuds) {
        delete pair.second; // Libération de la mémoire des noeuds
    }
    for (auto& pair : lesarcs) {
        delete pair.second; // Libération de la mémoire des arcs
    }
}

// Complexité temporelle : O(E), où E est le nombre d'arcs dans le fichier. La méthode lit chaque ligne du fichier une fois, et pour chaque ligne, elle effectue des opérations de parsing qui sont en temps constant
int Graphe::lecture_arcs(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    std::string ligne;
    int count = 0;
    std::unordered_map<std::string, int> nomCompteur; // Pour gérer les doublons de noms

    while (std::getline(fichier, ligne)) {
        std::istringstream ss(ligne);
        std::string o, d, attributes;
        std::string id;

        // Lire les deux premiers champs (identifiants des noeuds)
        std::getline(ss, o, ',');
        std::getline(ss, d, ',');
        std::getline(ss, attributes);

        // Extraire les autres attributs à partir de la chaîne 'attributes'
        std::string name, highway, geometry;
        bool oneway = false, reversed = false;
        double length = 0.0, maxspeed = 0.0, speed_kph = 0.0, travel_time = 0.0;

        // Exemple d'extraction simple (vous pouvez améliorer le parsing)
        std::regex regex_name("'name': '([^']*)'");
        std::regex regex_highway("'highway': '([^']*)'");
        std::regex regex_oneway("'oneway': (true|false)");
        std::regex regex_reversed("'reversed': (true|false)");
        std::regex regex_length("'length': ([0-9]*\\.[0-9]+)");
        std::regex regex_geometry("'geometry': '([^']*)'");
        std::regex regex_maxspeed("'maxspeed': ([0-9]*\\.[0-9]+)");
        std::regex regex_speed_kph("'speed_kph': ([0-9]*\\.[0-9]+)");
        std::regex regex_travel_time("'travel_time': ([0-9]*\\.[0-9]+)");

        std::smatch match;

        // Extraction des attributs
        if (std::regex_search(attributes, match, regex_name)) {
            name = match[1];
        } else {
            // Si le nom est vide, le générer à partir des noeuds
            name = o + " to " + d; // Exemple de nom basé sur les noeuds
        }

        // Gérer les doublons de noms
        if (nomCompteur.find(name) != nomCompteur.end()) {
            nomCompteur[name]++;
            name += std::to_string(nomCompteur[name]); // Ajouter un suffixe numérique
        } else {
            nomCompteur[name] = 1; // Initialiser le compteur pour ce nom
        }

        // Extraction des autres attributs
        if (std::regex_search(attributes, match, regex_highway)) {
            highway = match[1];
        } else {
            highway = ""; // Valeur par défaut
        }
        if (std::regex_search(attributes, match, regex_oneway)) {
            oneway = (match[1] == "true");
        }
        if (std::regex_search(attributes, match, regex_reversed)) {
            reversed = (match[1] == "true");
        }
        if (std::regex_search(attributes, match, regex_length)) {
            length = std::stod(match[1]);
        }
        if (std::regex_search(attributes, match, regex_geometry)) {
            geometry = match[1];
        } else {
            geometry = ""; // Valeur par défaut
        }
        if (std::regex_search(attributes, match, regex_maxspeed)) {
            maxspeed = std::stod(match[1]);
        }
        if (std::regex_search(attributes, match, regex_speed_kph)) {
            speed_kph = std::stod(match[1]);
        }
        if (std::regex_search(attributes, match, regex_travel_time)) {
            travel_time = std::stod(match[1]);
        }

        id = name;

        // Créer un nouvel arc et l'ajouter à l'ensemble
        Arc* arc = new Arc(name, o, d, name, highway, oneway, reversed, length, geometry, maxspeed, speed_kph, travel_time);
        ajouterArc(arc);
        count++;
    }

    return count;
}


// Complexité temporelle : O(1). L'ajout d'un arc dans une table de hachage est en moyenne une opération en temps constant.
void Graphe::ajouterArc(Arc* arc) {
    lesarcs[arc->id] = arc;
}

Arc* Graphe::rechercherArc(const std::string& id) const {
    auto it = lesarcs.find(id);
    return (it != lesarcs.end()) ? it->second : nullptr;
}

// Complexité temporelle : O(1) en moyenne. La recherche dans une table de hachage est en moyenne une opération en temps constant.
void Graphe::afficherArcs() const {
    for (const auto& pair : lesarcs) {
        pair.second->affiche();
    }
}

//Complexité temporelle : O(V), où V est le nombre de noeuds dans le fichier. La méthode lit chaque ligne du fichier une fois, et pour chaque ligne, elle effectue des opérations de parsing qui sont en temps constant.
int Graphe::lecture_noeuds(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    std::string ligne;
    int count = 0;

    while (std::getline(fichier, ligne)) {
        std::istringstream ss(ligne);
        std::string id, attributes;

        // Lire l'identifiant du noeud
        std::getline(ss, id, ',');
        std::getline(ss, attributes);

        // Extraire les attributs à partir de la chaîne 'attributes'
        double latitude = 0.0;
        double longitude = 0.0;
        int street_count = 0;

        // Utilisation d'expressions régulières pour extraire les valeurs
        std::regex regex_y("'y': ([0-9]*\\.[0-9]+)");
        std::regex regex_x("'x': ([0-9]*\\.[0-9]+)");
        std::regex regex_street_count("'street_count': ([0-9]+)");

        std::smatch match;

        // Extraction de la latitude
        if (std::regex_search(attributes, match, regex_y)) {
            latitude = std::stod(match[1]);
        }

        // Extraction de la longitude
        if (std::regex_search(attributes, match, regex_x)) {
            longitude = std::stod(match[1]);
        }

        // Extraction du nombre de rues
        if (std::regex_search(attributes, match, regex_street_count)) {
            street_count = std::stoi(match[1]);
        }

        // Créer un nouveau noeud et l'ajouter à l'ensemble
        Noeud* noeud = new Noeud(id, latitude, longitude, street_count);
        ajouterNoeud(noeud);
        count++;
    }

    return count;
}

// Complexité temporelle : O(1). L'ajout d'un noeud dans une table de hachage est en moyenne une opération en temps constant.
void Graphe::ajouterNoeud(Noeud* noeud) {
    lesnoeuds[noeud->id] = noeud;
}

// Complexité temporelle : O(1) en moyenne. La recherche dans une table de hachage est en moyenne une opération en temps constant.
Noeud* Graphe::rechercherNoeud(const std::string& id) const {
    auto it = lesnoeuds.find(id);
    return (it != lesnoeuds.end()) ? it->second : nullptr;
}

// Complexité temporelle : O(V). La méthode parcourt tous les noeuds pour les afficher.
void Graphe::afficherNoeuds() const {
    for (const auto& pair : lesnoeuds) {
        pair.second->affiche();
    }
}

// Complexité temporelle : O(E). La méthode parcourt tous les arcs pour mettre à jour les listes d'arcs entrants et sortants pour chaque noeud.
void Graphe::liste_incidence() {
    // Implémentation de la méthode pour mettre à jour les arcs entrants et sortants
    for (const auto& pair : lesarcs) {
        Arc* arc = pair.second;
        Noeud* origine = rechercherNoeud(arc->o);
        Noeud* destination = rechercherNoeud(arc->d);
        if (origine) {
            origine->arcs_sortants.push_back(arc);
        }
        if (destination) {
            destination->arcs_entrants.push_back(arc);
        }
    }
}

// Complexité temporelle : O(V log V) pour le tri des noeuds par degré, où V est le nombre de noeuds. Le calcul du degré est O(V), mais le tri des noeuds est O(V log V).
void Graphe::degre(int n) {
    // Afficher les n premiers noeuds de plus fort degré
    std::vector<std::pair<Noeud*, int>> degres;
    for (const auto& pair : lesnoeuds) {
        Noeud* noeud = pair.second;
        int degre = noeud->arcs_sortants.size() + noeud->arcs_entrants.size();
        degres.push_back({noeud, degre});
    }

    std::sort(degres.begin(), degres.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (int i = 0; i < std::min(n, static_cast<int>(degres.size())); ++i) {
        std::cout << "Noeud: " << degres[i].first->id << " Degré: " << degres[i].second << std::endl;
    }
}

// Complexité temporelle : O(V + E) dans le pire des cas, où V est le nombre de noeuds et E est le nombre d'arcs. La méthode utilise un parcours en largeur (BFS) pour explorer le graphe.
bool Graphe::chemin
(const std::string& o, const std::string& d) {
    Noeud* noeudOrigine = rechercherNoeud(o);
    Noeud* noeudDestination = rechercherNoeud(d);

    if (!noeudOrigine || !noeudDestination) {
        std::cout << "Noeud d'origine ou de destination introuvable." << std::endl;
        return false;
    }

    std::unordered_map<Noeud*, bool> visite;
    std::queue<Noeud*> file;
    file.push(noeudOrigine);
    visite[noeudOrigine] = true;

    while (!file.empty()) {
        Noeud* courant = file.front();
        file.pop();

        if (courant == noeudDestination) {
            std::cout << "Un chemin existe entre " << o << " et " << d << "." << std::endl;
            return true;
        }

        for (Arc* arc : courant->arcs_sortants) {
            Noeud* voisin = rechercherNoeud(arc->d);
            if (voisin && !visite[voisin]) {
                file.push(voisin);
                visite[voisin] = true;
            }
        }
    }

    std::cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << std::endl;
    return false;
}

// Complexité temporelle : O(V + E) dans le pire des cas, où V est le nombre de noeuds et E est le nombre d 'arcs. La méthode utilise également un parcours en largeur (BFS) pour trouver le plus court chemin.
int Graphe::pluscourtchemin(const std::string& o, const std::string& d) {
    Noeud* noeudOrigine = rechercherNoeud(o);
    Noeud* noeudDestination = rechercherNoeud(d);

    if (!noeudOrigine || !noeudDestination) {
        std::cout << "Noeud d'origine ou de destination introuvable." << std::endl;
        return 0;
    }

    for (auto& pair : lesnoeuds) {
        pair.second->visite = false; // Réinitialiser l'attribut visite
    }

    std::queue<Noeud*> file;
    file.push(noeudOrigine);
    noeudOrigine->visite = true;

    std::unordered_map<Noeud*, Arc*> parentArc;
    parentArc[noeudOrigine] = nullptr;

    while (!file.empty()) {
        Noeud* courant = file.front();
        file.pop();

        if (courant == noeudDestination) {
            std::vector<std::string> cheminUtilise;
            Noeud* temp = courant;

            while (temp != noeudOrigine) {
                Arc* arcUtilise = parentArc[temp];
                if (arcUtilise) cheminUtilise.push_back(arcUtilise->id);
                temp = rechercherNoeud(arcUtilise->o);
            }

            std::reverse(cheminUtilise.begin(), cheminUtilise.end());
            std::cout << "Le plus court chemin trouvé : " << std::endl;
            for (const auto& arcNom : cheminUtilise) {
                std::cout << arcNom << " -> ";
            }
            std::cout << d << std::endl;
            return cheminUtilise.size();
        }

        for (Arc* arc : courant->arcs_sortants) {
            Noeud* voisin = rechercherNoeud(arc->d);
            if (voisin && !voisin->visite) {
                file.push(voisin);
                voisin->visite = true;
                parentArc[voisin] = arc;
            }
        }
    }

    std::cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << std::endl;
    return 0;
}

// Complexité temporelle : O(V + E). Cette méthode appelle afficherNoeuds() et afficherArcs(), qui parcourent respectivement tous les noeuds et tous les arcs.
void Graphe::affiche() const {
    std::cout << "Affichage des noeuds :" << std::endl;
    afficherNoeuds();
    std::cout << "Affichage des arcs :" << std::endl;
    afficherArcs();
}