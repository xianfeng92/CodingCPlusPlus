
for(j = 0; j < n; j++) {
    for(i = 0; i < n; i++) {
        sum = 0.0;
        for(k = 0; k < n; k++) {
            sum += A[i][k] * B[k][j];
        }
        C[i][j] += sum;
    }
}