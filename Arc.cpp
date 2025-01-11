#include "Arc.h"

// Constructeur
Arc::Arc(const std::string& id, const std::string& o, const std::string& d, const std::string& name, 
         const std::string& highway, bool oneway, bool reversed, 
         double length, const std::string& geometry, double maxspeed, 
         double speed_kph, double travel_time)
    : id(id), o(o), d(d), name(name), highway(highway), oneway(oneway), 
      reversed(reversed), length(length), geometry(geometry), 
      maxspeed(maxspeed), speed_kph(speed_kph), travel_time(travel_time) {}

// Destructeur
Arc::~Arc() {}

// Méthode pour afficher les détails de l'arc
void Arc::affiche() const {
    std::cout << "Arc ID: " << id << ", From: " << o << ", To: " << d 
              << ", Name: " << name << ", Highway: " << highway 
              << ", Length: " << length << "m, Max Speed: " << maxspeed 
              << " km/h, Travel Time: " << travel_time << "s" << std::endl;
}