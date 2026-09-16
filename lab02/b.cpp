#include <iostream>
#include <chrono>
#include <algorithm>

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
 * @details using i-j-k approach
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

/**
 * @brief multiply matrix A by B and store the result in C with a improvement
 * @details using i-k-j approach
 * C = AxB
 * @param A left matrix A
 * @param B right matrix B
 * @param C resulting matrix C
*/
void improvement_mult_matrix(double**& A, double**& B, double**& C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) { // swap for j with for k
            for (int j = 0; j < n; ++j) {
                // result is equal to classic multiplication
                // but taking advantage of spatial locality
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/**
 * @brief multiply matrix A by B and store the result in C using cache blocking
 * @details using block multiplication approach to optimize cache capacity usage
 * C = AxB
 * @param A left matrix A
 * @param B right matrix B
 * @param C resulting matrix C
 * @param n size matrix nxn
 * @param b size of the block
*/
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

void experiment() {
    double** A = nullptr;
    double** B = nullptr;
    double** C = nullptr;
    for (int n : {100, 500, 1000, 1300, 1400, 1500, 1600}) {
        std::cout << "N = " << n << std::endl;
        // init matrices
        assign_matrix(A, n, 4.0);
        assign_matrix(B, n, 9.0);
        assign_matrix(C, n, 0.0);

        auto start = std::chrono::steady_clock::now();

        // multiply AxB with i-j-k approach
        classic_mult_matrix(A, B, C, n);

        auto end = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        double time = delta / 1000.0;

        std::cout << "classic i-j-k multiply time: " << time << " ms" << std::endl;

        assign_matrix(C, n, 0.0);

        start = std::chrono::steady_clock::now();

        // multiply AxB with improvement i-k-j approach
        improvement_mult_matrix(A, B, C, n);

        end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        time = delta / 1000.0;

        std::cout << "performance i-k-j multiply time: " << time << " ms" << std::endl;

        assign_matrix(C, n, 0.0);

        start = std::chrono::steady_clock::now();

        // multiply AxB with block cache approach
        blocked_mult_matrix(A, B, C, n, 64); // blocks of 64x64

        end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        time = delta / 1000.0;

        std::cout << "blocked multiply time: " << time << " ms" << std::endl;

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

/**
 * @brief experiment with a N fixed and diferent b values 
*/
void blocking_n_fixed() {

    double** A = nullptr;
    double** B = nullptr;
    double** C = nullptr;

    const int n = 1600;
    std::cout << "===== N = " << n << " =====" << std::endl;

    // using L2 cache. 512 KB size in L2 cache per core (ryzen 5 5600G)
    // let f(x) = 3(x)^2 (8) bytes
    // b = f(64) -> 98 KB -> 18% of the L2
    // b = f(120) -> 66% of the L2
    // b = f(128) -> 75% of the L2
    // b = f(144) -> 497.6 KB -> 95% of the L2
    // b = f(160) -> 600 KB -> ~ 117% of the L2
    // b = f(192) -> 864 KB -> ~ 168% of the L2
    // b = f(256) -> 1.57 MB -> ~ 300% of the L2
    // b = f(384) -> 3.37 MB -> ~ 675% of the L2
    // b = f(512) -> 6.0 MB -> ~ 1200% of the L2
    for (int b : {64, 120, 128, 144, 160, 192, 256, 384, 512}) {
        std::cout << "\nb = " << b << std::endl;

        // init matrices
        assign_matrix(A, n, 4.0);
        assign_matrix(B, n, 9.0);
        assign_matrix(C, n, 0.0);

        auto start = std::chrono::steady_clock::now();

        blocked_mult_matrix(A, B, C, n, b); // variable blocks

        auto end = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        double time = delta / 1000.0;

        std::cout << "blocked multiply time: " << time << " ms" << std::endl;

    }
    // destructor
    for (int i = 0; i < n; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}

int main() {
    // experiment();
    blocking_n_fixed();
    return 0;
}

