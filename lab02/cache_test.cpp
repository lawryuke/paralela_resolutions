#include <iostream>
#include <algorithm>

void assign_matrix(double**& M, const int n, double value = 0.0) {
    if (!M) M = new double*[n]();
    for (int i = 0; i < n; i++) {
        if (!M[i]) M[i] = new double[n];
        std::fill(M[i], M[i] + n, value);
    }
}

void classic_mult_matrix(double**& A, double**& B, double**& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void blocked_mult_matrix(double**& A, double**& B, double**& C, int n, int b = 64) {
    for (int ii = 0; ii < n; ii += b) {
        for (int kk = 0; kk < n; kk += b) {
            for (int jj = 0; jj < n; jj += b) {
                int iMax = std::min(ii + b, n);
                int kMax = std::min(kk + b, n);
                int jMax = std::min(jj + b, n);
                for (int i = ii; i < iMax; ++i) {
                    for (int k = kk; k < kMax; ++k) {
                        double aik = A[i][k];
                        for (int j = jj; j < jMax; ++j) {
                            C[i][j] += aik * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n = 500;
    double** A = nullptr;
    double** B = nullptr;
    double** C = nullptr;
    assign_matrix(A, n, 1.0);
    assign_matrix(B, n, 2.0);
    assign_matrix(C, n, 0.0);

    classic_mult_matrix(A, B, C, n);
    
    assign_matrix(C, n, 0.0);
    blocked_mult_matrix(A, B, C, n, 128);

    // Esto evita que g++ -O3 elimine las funciones por ser "código muerto"
    std::cout << "Resultado: " << C[0][0] << std::endl;

    return 0;
}
