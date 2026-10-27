double ternary_search(double l, double r) {
    //set the error limit here
    // number of iterations and error are directly related,
    // you can also stop the algorithm by bounding the number 
    // of iterations instead of the r - l > eps condition
    // (200 - 300 iterations are generally enough) 
    // iterations are independent of l and r
    double eps = 1e-9;              
    while (r - l > eps) {
        double m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        //evaluates the function at m1 and m2
        double f1 = func(m1), f2 = func(m2);
        if (f1 < f2)    l = m1;
        else    r = m2;
    }
    return func(l);                    //return the maximum of func(x) in [l, r]
}
//for ternary searching on an integer number line, you just need to divide 
// [l, r] into three approximately equal parts, and stop when (r - l) < 3
// at this point, just check all the values in [l, r] manually
