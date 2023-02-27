#include <stdio.h>
#include <stdlib.h>

#define N 100

int n, t[N][N];
int recurrent[N], transitive[N];

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

    // les classes récurrentes
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

    // les classes transitoires
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

    printf("Veuillez saisire le nombre d'etats : ");
    scanf("%d", &n);


    printf("Veuillez saisire la matrice de transition : \n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("T[%d, %d] : ", i, j);
            scanf("%d", &t[i][j]);
        }
    }


    for (i = 0; i < n; i++) {
        recurrent[i] = 0;
        transitive[i] = 0;
    }

    decompositionClasses();


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
