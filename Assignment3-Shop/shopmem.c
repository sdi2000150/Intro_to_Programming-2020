/* File: shopmem.c */
#include <stdlib.h>
#include <stdio.h>
#include "shop.h"
//#define COSTS

int mem(int **Rpi, int i, int p, int m, int n, int *k, int **c) {
    int j, r, min;
    r = m;                                         /* Trito melos tou mathimatikou typou, anti gia else if (p - c[i][j] < 0) { r = m } mesa sto for */
    min = m;
    for (j = 0 ; j < k[i] ; j++) {
        if ((p - c[i][j] >= 0) && (i+1 == n)) {    /* Deutero melos tou mathimatikou typou */
            Rpi[i+1][p-c[i][j]] = p - c[i][j];
            r = Rpi[i+1][p-c[i][j]];
        }
        else if (p - c[i][j] >= 0) {               /* Prwto melos tou mathimatikou typou */
            if (Rpi[i+1][p-c[i][j]] >= 0) {
                r = Rpi[i+1][p-c[i][j]];
            }
            else {
                Rpi[i+1][p-c[i][j]] = mem(Rpi, i+1, p-c[i][j], m, n, k, c);
                r = Rpi[i+1][p-c[i][j]];
            }
        }
        if (r < min) {
            min = r;
        }
    }
    return min;
}

int shop(int m, int n, int *k, int **c) {
    int S, **Rpi, i, j, pm;

    Rpi = malloc((n+1) * sizeof(int *));
    if (Rpi == NULL) {
        exit(1);
    }
    for (i = 0 ; i < n+1 ; i++) {
        Rpi[i] = malloc((m+1) * sizeof(int));
        if (Rpi[i] == NULL) {
            exit(1);
        }
        for (j = 0 ; j < m+1 ; j++) {
            Rpi[i][j] = -1;
        }
    }

    Rpi[0][m] = mem(Rpi, 0, m, m, n, k, c);
    S = m - Rpi[0][m];

    if (S > 0) {                                   /* An yparxei solution */
        #ifdef COSTS
            pm = m;                                /* To diathesimo xrhmatiko poso ksekinaei apo m */
            printf("Item costs: ");
            for (i = 0 ; i < n+1 ; i++) {
                for (j = 0 ; j < pm ; j++) {
                    if (Rpi[i][j] == Rpi[0][m]) {  /* An to trexon stoixeio tou pinaka einai iso me to min */
                        printf("%d ",pm-j);        /* Ektypwse to diathesimo xrhmatiko poso - to poso pou menei apo tin teleutaia agora, (ara to kostos tou montelou) */
                        pm = j;                    /* To diathesimo xrhmatiko poso ginetai iso me to poso pou menei apo tin teleutaia agora */
                    }
                }
            }
            printf("\n");
        #endif
    }

    for (i = 0 ; i < n+1 ; i++) {
        free(Rpi[i]);
    }
    free(Rpi);

    return S;
}