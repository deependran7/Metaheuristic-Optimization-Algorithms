// optimisation of Booth function 

double fitness(double x[]){
    double value;
    value = (x[0] + 2*x[1]-7)*(x[0] + 2*x[1]-7) + (2*x[0] + x[1]-5)*(2*x[0] + x[1]-5);
    return value;
};

