#include "PSO.h"
#include "Fitness.h"
#include <iostream>
using namespace std;



int main(){
    
    int population  = 500;
    int dimension = 2;
    double lbb[dimension] = {-1,-1};
    double ubb[dimension] ={100,100};
    int generation = 1000;
    double w = 0.5;
    double c1 = 1;
    double c2 = 2;
    double optimal;
    Swarm swarm1(dimension,generation,population,w,c1,c2,lbb,ubb, fitness);
    swarm1.create_swarm();
    swarm1.swarm_evolve();
    optimal = swarm1.get_solution();
    double * solution;
    solution = swarm1.get_state();
    cout  << "Optimal Soution is: " << optimal << endl;
    for (int i = 0; i < dimension; i++)
    {
        cout<< i <<"th solution variable is:"<<solution[i]<<endl;
    }
    
  
}