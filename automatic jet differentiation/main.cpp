#include <iostream>
#include <cmath>
#include <vector>
#include "function.h"

class Jet {
public:
    std::vector<double> derivatives;
    static int size;

    Jet() = default;

    Jet &operator=(const Jet &g) = default;

    Jet(std::vector<double> dx) : derivatives(dx) {}

    Jet(const Jet &other) : derivatives(other.derivatives) {}

    Jet(double x, bool var = false) {
        derivatives = std::vector<double>(size);
        derivatives[0] = x;
        if (var) {
            derivatives[1] = 1;
        }
    };

    friend std::ostream &operator<<(std::ostream &output, const Jet &jet) {
        output.precision(16);
        for (int i = 0; i < jet.derivatives.size(); ++i) {
            output << jet.derivatives[i] * tgamma(i + 1) << ' ';
        }
        output << std::endl;
        return output;
    }

    friend Jet operator+(const Jet &f, const Jet &g) {
        Jet jet = Jet(f);
        for (int i = 0; i < f.derivatives.size(); ++i) {
            jet.derivatives[i] += g.derivatives[i];
        }
        return jet;
    }

    friend Jet operator-(const Jet &f, const Jet &g) {
        Jet jet = Jet(f);
        for (int i = 0; i < f.derivatives.size(); ++i) {
            jet.derivatives[i] -= g.derivatives[i];
        }
        return jet;
    }

    friend Jet operator-(const Jet &f) {
        Jet jet = Jet(f);
        for (int i = 0; i < f.derivatives.size(); ++i) {
            jet.derivatives[i] *= -1;
        }
        return jet;
    }

    friend Jet operator*(const Jet &f, const Jet &g) {
        Jet jet = Jet(std::vector<double>(f.derivatives.size()));
        for (int k = 0; k < f.derivatives.size(); ++k) {
            for (int i = 0; i <= k; ++i) {
                jet.derivatives[k] += f.derivatives[i] * g.derivatives[k - i];
            }
        }
        return jet;
    }

    friend Jet operator/(const Jet &f, const Jet &g) {
        Jet jet = Jet(std::vector<double>(f.derivatives.size()));
        for (int i = 0; i < f.derivatives.size(); ++i) {
            double sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += jet.derivatives[j] * g.derivatives[i - j];
            }
            jet.derivatives[i] = (1 / g.derivatives[0]) * (f.derivatives[i] - sum);
        }
        return jet;
    }

    friend Jet trigonometry(const Jet &f, bool type) {
        Jet sin_jet = Jet(0);
        Jet cos_jet = Jet(0);
        sin_jet.derivatives[0] = std::sin(f.derivatives[0]);
        cos_jet.derivatives[0] = std::cos(f.derivatives[0]);
        for (int i = 0; i < f.derivatives.size(); ++i) {
            for (int j = 1; j <= i; ++j) {
                cos_jet.derivatives[i] += (-1.0 / i) * j * f.derivatives[j] * sin_jet.derivatives[i - j];
                sin_jet.derivatives[i] += (1.0 / i) * j * f.derivatives[j] * cos_jet.derivatives[i - j];
            }
        }
        return type ? sin_jet : cos_jet;
    }

    friend Jet sin(const Jet &f) {
        return trigonometry(f, true);
    }

    friend Jet cos(const Jet &f) {
        return trigonometry(f, false);
    }

    friend Jet exp(const Jet &f) {
        Jet jet = Jet(0);
        jet.derivatives[0] = std::exp(f.derivatives[0]);
        for (int i = 0; i < f.derivatives.size(); ++i) {
            for (int j = 1; j <= i; ++j) {
                jet.derivatives[i] += (1.0 / i) * j * f.derivatives[j] * jet.derivatives[i - j];
            }
        }
        return jet;
    }
};

int Jet::size = 1;

int main() {
    int n, m;
    double x;
    std::cin >> n >> m;
    Jet::size = n + 1;
    for (int i = 0; i < m; ++i) {
        std::cin >> x;
        Jet jet(x, true);
        std::cout << function(jet);
    }
}