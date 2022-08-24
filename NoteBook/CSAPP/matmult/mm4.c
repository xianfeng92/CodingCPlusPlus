
for(k = 0; k < n; k++) {
    for(j = 0; j < n; j++) {
        r = B[k][j];
        for(i = 0; i < n; i++) {
            C[i][j] += A[i][k]*r;
        }
    }
}