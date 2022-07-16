#include <iostream>
#include <cstdio>
#include <cmath>

typedef void (*FuncPointer)(const double *x, double *y, double *Df);

const int ITER = 200;

void printVector(const double *x, unsigned N) {
    for (unsigned i = 0; i < N; ++i)
        printf("%17.17f ", x[i]);
    printf("\n");
}

int findCurve(FuncPointer f, double *x, unsigned int k, double h) {
    double XX[3] = {x[0], x[1], x[2]}, YY[2], DF[6];
    for (int i = 1; i <= k; ++i) {
        XX[2] += h;
        for (int j = 1; j <= ITER; ++j) {
            f(XX, YY, DF);
            double det = DF[0] * DF[4] - DF[1] * DF[3];

            if (std::max(std::abs(YY[0]), std::abs(YY[1])) <= 1e-14) {
                break;
            }

            if (std::abs(det) < 1e-14 || j == ITER) {
                return i;
            }

            XX[0] -= (YY[0] * DF[4] - YY[1] * DF[1]) / det;
            XX[1] -= (YY[1] * DF[0] - YY[0] * DF[3]) / det;
        }
        printVector(XX, 3);
    }
    return 0;
}

int findSurface(FuncPointer f, double *x, unsigned k1, unsigned k2, double h1, double h2) {
    double XX[3] = {x[0], x[1], x[2]}, YY[1], DF[3];
    double p = x[2];
    for (int i = 1; i <= k1; ++i) {
        XX[1] += h1;
        XX[2] = p;
        for (int j = 1; j <= k2; ++j) {
            XX[2] += h2;
            for (int k = 1; k <= ITER; ++k) {
                f(XX, YY, DF);

                if (std::abs(YY[0]) <= 1e-14) {
                    break;
                }

                if (std::abs(DF[0]) < 1e-14 || k == ITER) {
                    return i * k1 + j;
                }

                XX[0] -= YY[0] / DF[0];
            }
            printVector(XX, 3);
        }
        std::cout << std::endl;
    }
    return 0;
}

// g(x, y) = f(x, y) - (x, y)
int findFixedPoints(FuncPointer f, double *x, unsigned k1, unsigned k2, double h1, double h2) {
    double XX[4] = {x[0], x[1], x[2], x[3]}, YY[2], DF[8];
    double p = x[3];
    for (int i = 1; i <= k1; ++i) {
        XX[2] += h1;
        XX[3] = p;
        for (int j = 1; j <= k2; ++j) {
            XX[3] += h2;
            for (int k = 1; k <= ITER; ++k) {
                f(XX, YY, DF);
                DF[0] -= 1;
                DF[5] -= 1;
                double det = DF[0] * DF[5] - DF[1] * DF[4];

                if (std::max(std::abs(YY[0] - XX[0]), std::abs(YY[1] - XX[1])) <= 1e-14) {
                    break;
                }

                if (std::abs(det) < 1e-14 || k == ITER) {
                    return i * k1 + j;
                }

                XX[0] -= ((YY[0] - XX[0]) * DF[5] - (YY[1] - XX[1]) * DF[1]) / det;
                XX[1] -= ((YY[1] - XX[1]) * DF[0] - (YY[0] - XX[0]) * DF[4]) / det;
            }
            printVector(XX, 4);
        }
        std::cout << std::endl;
    }
    return 0;
}



