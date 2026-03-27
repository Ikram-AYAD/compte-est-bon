# arithmetic-solver-c.
Logiciel de résolution arithmétique optimisé en C : Algorithmique et IA symbolique.
# 🧮 IA Symbolique : Solveur Arithmétique (Langage C)

## 📌 Présentation du projet
Ce projet consiste en l'implémentation d'un solveur intelligent pour le jeu "Le Compte est Bon". L'objectif est de trouver la combinaison arithmétique exacte (ou la plus proche) pour atteindre une cible donnée à partir d'un tirage de six nombres.

## 🧠 Logique d'Intelligence Artificielle
Plutôt qu'une simple recherche aléatoire, le programme utilise une **IA symbolique** basée sur :
* **Recherche en profondeur (Backtracking) :** Exploration exhaustive de l'arbre des combinaisons possibles.
* **Algorithme récursif optimisé :** Une fonction récursive teste chaque opération (+, -, *, /) tout en respectant les contraintes mathématiques (pas de nombres négatifs ou de divisions non entières).
* **Mise à jour dynamique :** Le programme mémorise en temps réel la meilleure solution trouvée pour garantir un résultat, même si la cible exacte n'est pas atteignable.

## 🛠️ Spécifications Techniques
* **Langage :** C (Standard ISO)
* **Gestion de la mémoire :** Utilisation de structures de données (`struct`) pour stocker l'historique des calculs et optimiser les ressources.
* **Complexité :** Gestion d'un grand espace d'états (plusieurs milliers de combinaisons possibles) avec un temps de réponse instantané.

## 🚀 Installation et Utilisation
1. Compiler le programme :
   ```bash
   gcc main.c -o solver
