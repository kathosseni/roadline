# Projet de Modélisation d'un Réseau Routier

## Description
Ce projet consiste à modéliser un réseau routier à partir de données fournies dans des fichiers CSV (`nodes.csv` et `arcs.csv`). Le réseau est représenté sous forme de graphe, où les noeuds représentent des intersections ou des points d'intérêt, et les arcs représentent les routes reliant ces noeuds. L'objectif est de créer des structures de données appropriées pour stocker ces informations et d'implémenter des algorithmes pour explorer le graphe.

## Objectifs
- Stocker les noeuds et les arcs dans des structures de données adaptées.
- Parcourir et interroger le graphe pour répondre à divers besoins (chemin, itinéraire, etc.).

## Structure du Projet
Le projet est organisé en plusieurs fichiers :

- **Arc.h / Arc.cpp** : Définition et implémentation de la classe `Arc`, représentant une route entre deux noeuds.
- **Noeud.h / Noeud.cpp** : Définition et implémentation de la classe `Noeud`, représentant un point d'intérêt ou une intersection.
- **Graphe.h / Graphe.cpp** : Définition et implémentation de la classe `Graphe`, qui gère les noeuds et les arcs, et fournit des méthodes pour interroger le graphe.
- **main.cpp** : Point d'entrée du programme, qui crée le graphe et exécute les fonctionnalités principales.

## Installation
1. Clonez le dépôt :
   ```bash
   git clone git@github.com:kathosseni/roadline.git
   cd roadline

2. Assurez-vous d'avoir un compilateur C++ installé (comme g++).

3. Compilez le projet :
    ``` bash
    g++ -o graphe main.cpp Graphe.cpp Noeud.cpp Arc.cpp

## Utilisation
1. Préparez vos fichiers nodes.csv et arcs.csv avec les données appropriées.

2. Exécutez le programme :
    ``` bash
    ./graphe

3. Le programme affichera les résultats des requêtes sur le graphe, y compris :
- L'existence d'un chemin entre deux noeuds.
- Le plus court chemin entre deux noeuds.
- L'itinéraire le plus court basé sur les noms des rues.

## Auteurs
- Nom : Malikath Osseni
- GitHub : https://github.com/kathosseni