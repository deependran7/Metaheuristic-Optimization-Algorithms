#include<iostream>
#include<random>
#include<chrono>
using namespace std;

struct Optimal
{
    double cost_solution;
    int dimension;
    
    //double* state_variable [];
};



class Particle {
   public:
           
      int dimension;    //dimension of problem
      double * position;     
      double * velocity;
      double * upperbound;
      double * lowerbound;
      double w,c1,c2;
      
    
    Particle(int adimension, double aubound[],double albound[],double aw, double ac1, double ac2){
        dimension = adimension;
        upperbound = aubound;
        lowerbound = albound;
        position = new double [dimension];
        velocity = new double [dimension];
        w = aw;
        c1 = ac1;
        c2 = ac2;

        //converting the upper and lower bound in 2d array
        double bounds[dimension][2];
        for (int i = 0; i < dimension; i++)
        {
            bounds[i][0] = lowerbound[i];
            bounds[i][1] = upperbound[i];
        }

        //generating random positions and velocity of particles
        for (int i = 0; i < dimension; i++)
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator (seed);
            uniform_real_distribution<double> distribution(bounds[i][0],bounds[i][1]);
            position[i] = distribution(generator);
            velocity[i] = distribution(generator);
        }
        
    };

    void particle_move(){
        for (int i = 0; i < dimension; i++)
        {
            position[i] = position[i]+velocity[i];

        }
        
    }
    void update_velocity(double pbest[], double gbest[]){
        for (int i = 0; i < dimension; i++)
        {   
            double rand1;
            double rand2;
            double vel_social;
            double vel_cognitive;
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            default_random_engine generator (seed);
            uniform_real_distribution<double> distribution(0,1);
            rand1 = distribution(generator);
            rand2 = distribution(generator);

            vel_social=c2*rand2*(gbest[i]-position[i]);
            vel_cognitive=c1*rand1*(pbest[i]-position[i]);
            
            velocity[i]=w*velocity[i]+ vel_cognitive + vel_social;

        }
    }  
};

class Swarm {
  
    public:
        int dimension;
        int population;   // total population of the swarm
        double * upper_bound;  // upper bound for the particle position
        double * lower_bound;  // lower bound for the particle position
        double w;
        double c1;
        double c2;
        Particle* Particle_Swarm;
        double (*fitness_function) (double x[]);
        int generation;
        double g_best_cost;
        double* g_best_position;
        
        
    
    Swarm(int adimension, int apopulation, int agenerations,double aw,double ac1,double ac2,double aubound[],double albound[], double (*func)(double x[])) {     // Constructor
      dimension = adimension;
      population = apopulation;
      generation = agenerations;
      upper_bound = aubound;
      lower_bound = albound;
      fitness_function = func;
      w = aw;
      c1 = ac1;
      c2 = ac2;

      g_best_cost = 1000000000;
      g_best_position = (double*)malloc(sizeof(double) * dimension);
      
      
      

    }

    void create_swarm(void){
            Particle* swarm_data = (Particle*)malloc(sizeof(Particle) * population);
            for (int i = 0; i < population; i++) {
                swarm_data[i] =  Particle(dimension,upper_bound,lower_bound,w,c1,c2);
                        
                            }
                
            Particle_Swarm = swarm_data;
    };

    void get_swarm_position(void){
       
        for (int i = 0; i < population; i++)
        {
            for (int j = 0; j < dimension ; j++)
            {
                cout << Particle_Swarm[i].position[j];
                
                cout<< ",";
            }
            cout << endl;
        }
        
    };

    void  swarm_evolve(){
        
        for (int epoch = 0; epoch < generation; epoch++)
        {
            /* optimising the loop */
            double p_best_cost = g_best_cost;
            double p_best_position [dimension];
            double* var;
            double value [dimension];
            double cost;

            for (int particle = 0; particle < population; particle++)
            {   //datatype conversion
                var = Particle_Swarm[particle].position;
                for (int p = 0; p < dimension; p++)
                {
                    value[p] = var[p];
                }
        
                cost = fitness_function(value);
                if (cost<p_best_cost)
                {
                    p_best_cost = cost;
                    for (int i = 0; i < dimension; i++)
                    {
                        p_best_position[i] = value[i];
                        //cout<<p_best_position[i]<<endl;
                    }
                }
                //update the particle velocity and postion
                
                
                    Particle_Swarm[particle].update_velocity(p_best_position,g_best_position);
                    Particle_Swarm[particle].particle_move(); 
                
                

            }

            if (p_best_cost< g_best_cost)
            {
                g_best_cost = p_best_cost;
                for (int i = 0; i < dimension; i++)
                    {
                        g_best_position[i]=p_best_position[i] ;
                        
                    }
            }
            
            
        }
            cout<<"Optimization Successful"<<endl;
            
    }
        
    double get_solution(){
        return g_best_cost;
    }

    double * get_state(){
         double* r = (double*)malloc(sizeof(double) * dimension);
        for (int i = 0; i < dimension; i++)
        {
            r[i] = g_best_position[i];
        }
        
        return r;
    }

    double eval_fitness(double x[],double (*function)(double x[])){
        cout<<function(x);
            return function(x);
    }
};