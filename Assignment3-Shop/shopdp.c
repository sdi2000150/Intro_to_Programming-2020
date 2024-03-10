/* File: shopdp.c */
#include <stdlib.h>
#include <stdio.h>
#include "shop.h"
//#define COSTS

int shop(int m, int n, int *k, int **c) {
    int S, **DP, i, j, l, min, *IC;
    min = m;

    DP = malloc(n * sizeof(int *));
    if (DP == NULL) {
        exit(1);
    }
    for (i = 0 ; i < n ; i++) {
        DP[i] = malloc((m+1) * sizeof(int));
        if (DP[i] == NULL) {
            exit(1);
        }
        for (j = 0 ; j < m+1 ; j++) {
            DP[i][j] = 0;
        }
    }

    for (i = 0 ; i < n ; i++) {
        if (i == 0) {                                   /* Gia tin prwth grammh */
            for (j = 0 ; j < k[i] ; j++) {
                if (c[i][j] >= 0 && c[i][j] <= m) {
                    DP[i][m-c[i][j]] = c[i][j];         /* Anti gia 1 bazw ston pinaka to kostos wste na me boithisei sto bonus */
                }
            }
        }
        else {                                          /* Gia tis ypoloipes grammes */
            for (j = 0 ; j < m+1 ; j++) {               /* Diatrexoume oles tis sthles tis grammhs */
                if (DP[i-1][j] != 0) {                  /* Ean yparxei stoixeio stin prohgoumenh grammh */
                    for (l = 0 ; l < k[i] ; l++) {
                        if (j-c[i][l] >= 0 && c[i][l] <= m) {
                            DP[i][j-c[i][l]] = c[i][l]; /* Anti gia 1 bazw ston pinaka to kostos wste na me boithisei sto bonus */
                        }
                    }
                }
            }
        }
    }

    for (l = 0 ; l < m+1 ; l++) {   /* Diatrexoume oles tis sthles tis teleutaias grammhs */
        if (DP[n-1][l] != 0) {      /* O deikths ths sthlhs pou brisketai to prwto mh mhdeniko stoixeio sthn teleutaia grammh (n-1) antistoixei sto min */
            min = l;
            break;
        }
    }
    S = m - min;

    if (S > 0) {                                /* An yparxei solution */
        #ifdef COSTS
            IC = malloc(n * sizeof(int));       /* Pinakas twn Item Costs */
            if (IC == NULL) {
                exit(1);
            }

            j = min;                            /* To j ksekinaei apo to elaxisto poso pou mporei na mas apomeinei */
            l = 0;
            IC[l] = DP[n-1][j];                 /* To prwto item cost(ta pairnoume antistrofa) einai gnwsto apo prin (efoson exoume apothikeusei ta kosth ston DP anti gia ta 1) */
            for (i = n-2 ; i >= 0 ; i--) {      /* Diatrexoume ton pinaka DP apo katw pros ta panw */
                l++;
                IC[l] = DP[i][DP[i+1][j] + j];  /* To deutero(klp) item cost einai iso me to stoixeio tou DP stin sthlh pou isoutai me to prohgoumeno item cost + j */
                j = DP[i+1][j] + j;             /* To j auksanetai kata to kostos tou prohgoumenou item */
            }
            
            printf("Item costs: ");
            for (l = n-1 ; l >= 0 ; l--) {      /* Ektypwnoume ta Item Costs me tin swsth seira(afou ta eixame apothikseusei me tin antitheth) */
                printf("%d ", IC[l]);
            }
            printf("\n");
        #endif
    }

    for (i = 0 ; i < n ; i++) {
        free(DP[i]);
    }
    free(DP);

    return S;
}