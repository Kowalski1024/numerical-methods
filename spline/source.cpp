#include <iostream>
#include "source.h"

spline::spline(std::size_t n) : n(n) {}

void spline::set_points(const double x[], const double y[]) {
    X = new double[n - 1]{};
    Y = new double[n - 1]{};
    A = new double[n - 1]{};
    B = new double[n - 1]{};
    C = new double[n - 1]{};
    double h[n - 1];
    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    double u[n];
    for (int i = 1; i < n - 1; ++i) {
        u[i] = 2 * (h[i - 1] + h[i]);
    }

    double v[n];
    for (int i = 1; i < n - 1; ++i) {
        v[i] = 6 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1]);
    }

    for (int i = 2; i < n - 1; ++i) {
        double w = h[i - 1] / u[i - 1];
        u[i] -= w * h[i - 1];
        v[i] -= w * v[i - 1];
    }
    double z[n];
    z[0] = 0;
    z[n - 1] = 0;
    z[n - 2] = v[n - 2] / u[n - 2];

    for (int i = n - 3; i > 0; --i) {
        z[i] = (v[i] - h[i] * z[i + 1]) / u[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        A[i] = (z[i + 1] - z[i]) / (6 * h[i]);
        B[i] = z[i] / 2;
        C[i] = (y[i + 1] - y[i]) / h[i] - h[i] * (z[i + 1] + 2 * z[i]) / 6;
        X[i] = x[i];
        Y[i] = y[i];
    }
}

spline::~spline() {
    delete A;
    delete B;
    delete C;
    delete X;
    delete Y;
}

double spline::operator()(const double x) const {
    int i = 0;
    for (int j = n - 2; j >= 0; --j) {
        if (x - X[j] >= 0) {
            i = j;
            break;
        }
    }

    long double xx = x - X[i];
    return Y[i] + xx * (C[i] + xx * (B[i] + A[i] * xx));
}