// Tomasz Wojnar
#include <iostream>
#include <vector>


double get(std::vector<std::vector<double>> &mat, int M, int row, int column) {
    return mat[M - std::abs(row - column)][std::min(row, column)];
}


int main() {
    int N, M, L;
    double w;

    std::cin >> N >> M;
    std::vector<std::vector<double>> matrix(M + 1);
    std::vector<double> Y(N);
    std::vector<double> X(N);

    auto m = M;
    for (int i = 0; i <= M; ++i) {
        auto s = N - m;
        matrix[i].resize(s);
        for (auto &x: matrix[i]) {
            std::cin >> x;
        }
        m--;
    }

    for (auto &x: Y) {
        std::cin >> x;
    }
    for (auto &x: X) {
        std::cin >> x;
    }

    std::cin >> w >> L;

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < N; ++j) {
            auto sum = Y[j];
            for (int k = std::max(j - M, 0); k <= std::min(j + M, N); ++k) {
                if (j != k) {
                    sum -=  get(matrix, M, j, k) * X[k];
                }
            }
            X[j] = (1 - w) * X[j] + w * sum / get(matrix, M, j, j);
        }
    }

    std::cout.precision(10);
    std::cout << std::scientific;
    for (auto x: X) {
        std::cout << x << std::endl;
    }
}