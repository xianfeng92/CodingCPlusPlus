
for(k = 0; k < n; k++) {
    for( i = 0; i < n; i++ ) {
        r = A[i][k];
        for( j = 0; j < n; j++ ) {
            C[i][j] += r * B[k][j];
        }
    }
}