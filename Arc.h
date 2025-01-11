#ifndef ARC_H
#define ARC_H

#include <string>
#include <iostream>

class Arc {
public:
    std::string id;      // Identifiant de l'arc
    std::string o;       // Noeud d'origine
    std::string d;       // Noeud de destination
    bool oneway;         // Indique si la route est à sens unique
    int lanes;           // Nombre de voies de la route
    std::string name;    // Nom de la route
    std::string highway; // Type de route (autoroute, résidentiel, etc.)
    bool reversed;       // Indique le sens de la route si à sens unique
    double length;       // Longueur en mètres de la route
    std::string geometry; // Suite de points constituant la route
    double maxspeed;     // Vitesse maximale sur la route (en km/h)
    double speed_kph;    // Vitesse moyenne si maxspeed n'est pas indiquée
    double travel_time;  // Temps de trajet sur la route

    // Constructeur
    Arc(const std::string& id, const std::string& o, const std::string& d, const std::string& name = "", 
        const std::string& highway = "", bool oneway = false, bool reversed = false, 
        double length = 0.0, const std::string& geometry = "", double maxspeed = 0.0, 
        double speed_kph = 0.0, double travel_time = 0.0);
    
    // Destructeur
    ~Arc();

    // Méthode pour afficher les détails de l'arc
    void affiche() const;
};

#endif // ARC_H