#include <iostream>
#include <cstdlib> 

// Fonction pour afficher le plateau de jeu avec des couleurs
void afficherPlateau(char plateau[3][3]) {
    for (int ligne = 0; ligne < 3; ++ligne) {
        for (int colonne = 0; colonne < 3; ++colonne) {
            char symbole = plateau[ligne][colonne];
            if (symbole == 'X') {
                std::cout << "\x1b[31m" << symbole << "\x1b[0m"; // Rouge pour 'X'
            }
            else if (symbole == 'O') {
                std::cout << "\x1b[34m" << symbole << "\x1b[0m"; // Bleu pour 'O'
            }
            else {
                int numeroCase = ligne * 3 + colonne + 1;
                std::cout << numeroCase;
            }

            if (colonne < 2) {
                std::cout << " | ";  // Séparateur entre les colonnes
            }
        }
        std::cout << std::endl;

        if (ligne < 2) {
            std::cout << "---------" << std::endl;  // Séparateur entre les lignes
        }
    }
}

// Fonction pour réinitialiser le plateau de jeu
void reinitialiserPlateau(char plateau[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            plateau[i][j] = ' ';
        }
    }
}

// Fonction pour vérifier si un joueur a gagné
bool verifierGagnant(char plateau[3][3], char symbole) {
    // Vérification des lignes et des colonnes
    for (int i = 0; i < 3; ++i) {
        if ((plateau[i][0] == symbole && plateau[i][1] == symbole && plateau[i][2] == symbole) ||
            (plateau[0][i] == symbole && plateau[1][i] == symbole && plateau[2][i] == symbole)) {
            return true;  // Gagné sur une ligne ou une colonne
        }
    }

    // Vérification des diagonales
    if ((plateau[0][0] == symbole && plateau[1][1] == symbole && plateau[2][2] == symbole) ||
        (plateau[0][2] == symbole && plateau[1][1] == symbole && plateau[2][0] == symbole)) {
        return true;  // Gagné sur une diagonale
    }

    return false;  // Aucun gagnant
}

// Fonction principale
int main() {
    char plateau[3][3];
    char symboleJoueur;
    int numeroCase;
    char reponse;
    bool joueurCommenceParX = true;
    int scoreX = 0, scoreO = 0;  // Scores des joueurs

    // Afficher un message de bienvenue et demander si les joueurs veulent jouer
    std::cout << "Welcome to the best TicTacToe in Visual Script fully code by Alexandre Cardot !\n(that's not totally true, pls Remi dont kill me)\n\nDo you want to play a game? :) (Y/N): ";
    std::cin >> reponse;

    if (reponse != 'Y' && reponse != 'y') {
        std::cout << "But... that's the point of the exercise... I'm sad... see you next time:(" << std::endl;
        return 0;
    }

    // Boucle externe pour permettre aux joueurs de jouer plusieurs parties
    do {
        // Effacer l'écran de la console (seulement sur Windows)
#ifdef _WIN32
        system("cls");
#endif

        // Réinitialiser le plateau de jeu
        reinitialiserPlateau(plateau);

        // Déterminer le joueur qui commence
        symboleJoueur = joueurCommenceParX ? 'X' : 'O';
        joueurCommenceParX = !joueurCommenceParX; // Inverser le joueur qui commence pour la prochaine partie

        // Boucle principale du jeu
        while (true) {
            // Effacer l'écran de la console (seulement sur Windows)
#ifdef _WIN32
            system("cls");
#endif

            // Afficher le plateau de jeu
            afficherPlateau(plateau);

            // Afficher les scores
            std::cout << "\nScores:\nPlayer X: " << scoreX << "  |  Player O: " << scoreO << "\n" << std::endl;

            // Demander au joueur actuel de faire un mouvement
            std::cout << "Player " << symboleJoueur << ", enter the number of the cell (1 to 9) where you want to place your symbol: ";
            std::cin >> numeroCase;

            // Convertir le numéro de la case en indices de ligne et de colonne
            int ligne = (numeroCase - 1) / 3;
            int colonne = (numeroCase - 1) % 3;

            // Vérifier si la case est valide
            if (numeroCase >= 1 && numeroCase <= 9 && plateau[ligne][colonne] == ' ') {
                // Effectuer le mouvement
                plateau[ligne][colonne] = symboleJoueur;

                // Vérifier si le joueur actuel a gagné
                if (verifierGagnant(plateau, symboleJoueur)) {
                    afficherPlateau(plateau);
                    std::cout << "The player " << symboleJoueur << " wins! Congratulations! :)" << std::endl;

                    // Mettre à jour le score
                    if (symboleJoueur == 'X') {
                        scoreX++;
                    }
                    else {
                        scoreO++;
                    }

                    break;
                }

                // Vérifier s'il y a égalité
                bool egalite = true;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (plateau[i][j] == ' ') {
                            egalite = false;
                            break;
                        }
                    }
                    if (!egalite) {
                        break;
                    }
                }
                if (egalite) {
                    afficherPlateau(plateau);
                    std::cout << "It's a draw! :/" << std::endl;
                    break;
                }

                // Changer de joueur
                symboleJoueur = (symboleJoueur == 'X') ? 'O' : 'X';
            }
            else {
                std::cout << "Invalid cell number. Please enter a number from 1 to 9 corresponding to an empty cell." << std::endl;
            }
        }

        // Demander si les joueurs veulent rejouer
        std::cout << "Do you want to play again? (Y/N): ";
        std::cin >> reponse;

        // Si la réponse n'est pas 'Y' ou 'y', quitter la boucle externe
        if (reponse != 'Y' && reponse != 'y') {
            break;
        }

    } while (true); // Boucle externe infinie pour rejouer ou quitter

    std::cout << "Thanks for playing to the best TicTacToe in Visual Script fully coded by Alexandre Cardot! \n(Once again no one will believe me ... hm ... well... See you next time! :)" << std::endl;

    return 0;
}
