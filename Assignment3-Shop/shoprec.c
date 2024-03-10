/* File: shoprec.c */
#include "shop.h"

int rec(int i, int p, int m, int n, int *k, int **c) {
    int j, r, min;
    r = m;                                         /* Trito melos tou mathimatikou typou, anti gia else if (p - c[i][j] < 0) { r = m } mesa sto for */
    min = m;
    for (j = 0 ; j < k[i] ; j++) {
        if ((p - c[i][j] >= 0) && (i+1 == n)) {    /* Deutero melos tou mathimatikou typou */
            r = p - c[i][j];
        }
        else if (p - c[i][j] >= 0) {               /* Prwto melos tou mathimatikou typou */
            r = rec(i+1, p-c[i][j], m, n, k, c);
        }
        if (r < min) {
            min = r;
        }
    }
    return min;
}

int shop(int m, int n, int *k, int **c) {
    int R, S, P;
    P = m;
    R = rec(0, P, m, n, k, c);
    S = m - R;
    return S;
}