/* File: shop.c */
#include <stdio.h>
#include <stdlib.h>
#include "shop.h"

/* Comments are in Greeklish */

int main(int argc, char *argv[]) {
    int M, N, i, j, *K, **C, result;

    M = atoi(argv[1]);

    scanf("%d",&N);
    K = malloc(N * sizeof(int));
    if (K == NULL) {
        return -1;
    }
    C = malloc(N * sizeof(int *));
    if (C == NULL) {
        return -1;
    }
    for (i = 0 ; i < N ; i++) {
        scanf("%d", &K[i]);
        C[i] = malloc(K[i] * sizeof(int));
        if (C[i] == NULL) {
            return -1;
        }
        for (j = 0 ; j < K[i] ; j++) {
            scanf("%d", &C[i][j]);
        }
    }

    result = shop(M, N, K, C);
    if (result > 0) {
        printf("Maximum amount spent is: %d\n",result);
    }
    else {
        printf("No solution found\n");
    }

    free(K);
    for (i = 0 ; i < N ; i++) {
        free(C[i]);
    }
    free(C);

    return 0;
}