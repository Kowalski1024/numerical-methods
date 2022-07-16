#ifndef SPLINE_SOURCE_H
#define SPLINE_SOURCE_H

class spline {
    const std::size_t n;
    double *X, *Y, *A, *B, *C;
public:
    spline(std::size_t n);
    ~spline();
    void set_points(const double x[], const double y[]);
    double operator()(const double x) const;
};


#endif //SPLINE_SOURCE_H
