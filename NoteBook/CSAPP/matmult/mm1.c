
for(int i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
        sum = 0.0;
        for(k = 0; k < n; k++) {
            sum += A[i][k]*B[k][j];
        }
        C[i][j] += sum;
    }
}