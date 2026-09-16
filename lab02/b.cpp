#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

/*+
 * @brief assign new matrix nxn (squad) or fill a existing matrix
 * 
 * @param M squad matrix pointer
 * @param n size matrix nxn
 * @param value the value assigned to each element
*/
void assign_matrix(double**& M, const int n, double value = 0.0) {
    if (!M) {
        M = new double*[n](); // the '()' or '{}' is value initialization (nullptr or 0s)
    }
    for (int i = 0; i < n; i++) {
        if (!M[i]) {
            M[i] = new double[n];
        }
        std::fill(M[i], M[i] + n, value);
    }
}


/**
 * @brief multiply matrix A by B and store the result in C
 * C = AxB
 * @param A left matrix A
 * @param B right matrix B
 * @param C resulting matrix C
*/
void classic_mult_matrix(double**& A, double**& B, double**& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void experiment() {
    double** A = nullptr;
    double** B = nullptr;
    double** C = nullptr;
    for (int n : {100, 500, 1000, 1300, 1500, 1600, 1700}) {
        std::cout << "N = " << n << std::endl;
        // init matrices
        assign_matrix(A, n, 4.0);
        assign_matrix(B, n, 9.0);
        assign_matrix(C, n);

        auto start = std::chrono::steady_clock::now();

        // multiply AxB
        classic_mult_matrix(A, B, C, n);

        auto end = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        double time = delta / 1000.0;

        std::cout << "classic multiply time: " << time << " ms" << std::endl;

        // destructor
        for (int i = 0; i < n; i++) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
        A = nullptr;
        B = nullptr;
        C = nullptr;
    }

}
int main() {
    experiment();
    return 0;
}


