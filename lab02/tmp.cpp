
void analisis(std::vector<double>& partial_a, std::vector<double>& partial_b) {
    // n = {4000,8000, 10000} -> doubles
    // n = {128MB, 512MB, 800MB} -> MB en RAM
    int i = 0;
    for (const int n : {4000, 8000, 10000}) {
        std::cout << "N = " << n << std::endl;
        // ==== FIRST LOOP =======
        // init
        double** A = nullptr;
        double* x = nullptr;
        double* y = nullptr; 
        assign_matrix(A, n, 0);
        assign_array(x, n, 1.0);
        assign_array(y, n, 0.0);

        auto start = std::chrono::steady_clock::now();

        // execution 
        first_loops(A, x, y, n);

        auto end = std::chrono::steady_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        double time = delta / 1000.0;

        // result
        std::cout << "consume time first loop: " << time  << " ms" << std::endl;
        partial_a[i] += time;


        // ==== SECOND LOOP =======
        // init
        assign_array(y, n, 0.0);

        start = std::chrono::steady_clock::now();

        // execution 
        second_loops(A, x, y, n);

        end = std::chrono::steady_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        time = delta / 1000.0;

        // result
        std::cout << "consume time second loop: " << time  << " ms" << std::endl;
        partial_b[i] += time;

        // ===== DESTRUCT =======
        for (int i = 0; i < n; i++) {
            delete[] A[i];
        }
        delete[] A;
        delete[] x;
        delete[] y;

        i++;
    }
}




int main() {
    int iter; std::cin >> iter;
    std::vector<double> partial_a(3);
    std::vector<double> partial_b(3);
    for (int i = 0; i < iter; ++i) {
        std::cout << "\n======= INTERACION: " << i << " ========" << std::endl;
        analisis(partial_a, partial_b);
    }

    int div = static_cast<double>(iter);
    for (int i = 0; i < 3; ++i) {
        partial_a[i] /= div;
        partial_b[i] /= div;
    }
    std::cout << "\n====== avergage for iter="<< iter << " =========" << std::endl;
    std::cout << "first loop" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "N=" << i << ": " << partial_a[i] << " ms" << std::endl;
    }
    std::cout << '\n';
    std::cout << "second loop" << std::endl;
    int size_n[3] = {4000, 8000, 10000};
    for (int i = 0; i < 3; ++i) {
        std::cout << "N=" << size_n[i] << ": " << partial_b[i] << " ms" << std::endl;
    }

    return 0;
}
