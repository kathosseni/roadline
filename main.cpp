#include <iostream>
#include "Graphe.h"

void afficherMenu() {
    std::cout << "==================== Menu ====================" << std::endl;
    std::cout << "1. Afficher tous les noeuds" << std::endl;
    std::cout << "2. Afficher tous les arcs" << std::endl;
    std::cout << "3. Trouver un chemin entre deux noeuds" << std::endl;
    std::cout << "4. Trouver le plus court chemin entre deux noeuds" << std::endl;
    std::cout << "5. Afficher les n noeuds de plus fort degré" << std::endl;
    std::cout << "6. Quitter" << std::endl;
    std::cout << "===============================================" << std::endl;
}

int main() {
    // Initialisation du graphe avec les fichiers de données
    Graphe graphe("arcs.csv", "noeuds.csv");

    int choix;
    do {
        afficherMenu();
        std::cout << "Veuillez entrer votre choix: ";
        std::cin >> choix;

        switch (choix) {
            case 1: {
                std::cout << "Affichage des noeuds:" << std::endl;
                graphe.afficherNoeuds();
                break;
            }
            case 2: {
                std::cout << "Affichage des arcs:" << std::endl;
                graphe.afficherArcs();
                break;
            }
            case 3: {
                std::string origine, destination;
                std::cout << "Entrez l'identifiant du noeud d'origine: ";
                std::cin >> origine;
                std::cout << "Entrez l'identifiant du noeud de destination: ";
                std::cin >> destination;
                graphe.chemin(origine, destination);
                break;
            }
            case 4: {
                std::string origine, destination;
                std::cout << "Entrez l'identifiant du noeud d'origine: ";
                std::cin >> origine;
                std::cout << "Entrez l'identifiant du noeud de destination: ";
                std::cin >> destination;
                int nombreArcs = graphe.pluscourtchemin(origine, destination);
                if (nombreArcs > 0) {
                    std::cout << "Le plus court chemin utilise " << nombreArcs << " arcs." << std::endl;
                } else {
                    std::cout << "Aucun chemin trouvé." << std::endl;
                }
                break;
            }
            case 5: {
                int n;
                std::cout << "Entrez le nombre de noeuds à afficher: ";
                std::cin >> n;
                graphe.degre(n);
                break;
            }
            case 6: {
                std::cout << "Au revoir!" << std::endl;
                break;
            }
            default: {
                std::cout << "Choix invalide, veuillez réessayer." << std::endl;
                break;
            }
        }
        std::cout << std::endl; // Ligne vide pour une meilleure lisibilité
    } while (choix != 6);

    return 0;
}