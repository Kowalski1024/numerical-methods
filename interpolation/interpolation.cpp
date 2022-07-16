#include <iostream>
#include <vector>

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<double> X(M);
    std::vector<double> Y(M);
    int map[M];
    for(auto &x: X) {
        std::cin >> x;
    }
    for (int i = 0; i < M; ++i) {
        std::cin >> Y[i];
        map[i] = i > 0 && X[i] == X[i-1] ? map[i-1] : i;
    }


    for (int i = 1; i < M; ++i) {
        for (int j = M-1; j >= i; --j) {
            double p;
            if (j-map[j-1] >= i) {
                p = Y[map[j-1]+i-1];
            } else {
                p = Y[j-1];
            }
            Y[j] = X[j] - X[j-i] == 0 ? Y[j]/i : (p - Y[j])/(X[j-i] - X[j]);
        }
    }

    std::cout.precision(16);
    std::cout << std::scientific << std::fixed;
    for(auto &x: Y) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < N; ++i) {
        long double x;
        long double sum = 1;
        long double res = 0;
        std::cin >> x;
        for (int j = 0; j < M; ++j) {
            res += Y[j] * sum;
            sum *= x - X[j];
        }
        std::cout << res << " ";
    }
    std::cout << std::endl;
}