template <typename T>
T function(const T & x){
    T y = sin(x*x - 2*(x+1))/exp(-x+cos(x*x));
    return y;
}
