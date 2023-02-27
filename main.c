#include <stdio.h>
#include <stdlib.h>

#define N 100 // Nombre maximum d'états de la chaîne de Markov

int n, t[N][N]; // Nombre d'états et matrice de transition
int recurrent[N], transitive[N]; // Classes récurrentes et transitoires

void rechercheEnProfondeur(int u, int visited[]) {
    int i;
    visited[u] = 1;
    for (i = 0; i < n; i++) {
        if (t[u][i] && !visited[i]) {
            rechercheEnProfondeur(i, visited);
        }
    }
}

void decompositionClasses() {
    int i, j, visited[N];
    for (i = 0; i < n; i++) {
        visited[i] = 0;
    }

    // Trouver les classes récurrentes
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            rechercheEnProfondeur(i, visited);
            for (j = 0; j < n; j++) {
                if (visited[j]) {
                    recurrent[j] = 1;
                }
            }
            int temp = 1;
            for (j = 0; j < n; j++) {
                if (!visited[j] && t[j][i]) {
                    temp = 0;
                    break;
                }
            }
            if (temp) {
                recurrent[i] = 1;
            }
        }
    }

    // Trouver les classes transitoires
    for (i = 0; i < n; i++) {
        if (!recurrent[i]) {
            rechercheEnProfondeur(i, visited);
            for (j = 0; j < n; j++) {
                if (visited[j] && !recurrent[j]) {
                    transitive[j] = 1;
                }
            }
        }
    }
}

int main() {
    int i, j;

    // Saisir le nombre d'états de la chaîne de Markov
    printf("Veuillez saisire le nombre d'etats : ");
    scanf("%d", &n);

    // Saisir la matrice de transition de la chaîne de Markov
    printf("Veuillez saisire la matrice de transition : \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("T[%d, %d] : ", i, j);
            scanf("%d", &t[i][j]);
        }
    }

    // Initialiser les classes récurrentes et transitoires à 0
    for (i = 0; i < n; i++) {
        recurrent[i] = 0;
        transitive[i] = 0;
    }

    // Décomposer la chaîne de Markov en classes récurrentes et transitoires
    decompositionClasses();

    // Afficher les classes récurrentes et transitoires
    printf("Classes recurrentes : { ");
    for (i = 0; i < n; i++) {
        if (recurrent[i]) {
            printf("%d ", i);
        }
    }
    printf("}\n");

    printf("Classes transitoires : {");
    for (i = 0; i < n; i++) {
        if (transitive[i]) {
            printf("%d ", i);
        }
    }
    printf("}\n");

    return 0;
}
