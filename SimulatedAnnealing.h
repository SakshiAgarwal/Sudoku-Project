/** Change here for a 25*25 input **/
const static int SRN = 3;
const static int N = 9;

int randomGenerator(int num)
{
    return (int) floor((rand()%(num)));
}

class state{
    /** state description
     * A curr matrix which represents a state of the Sudoku matrix
     * f matrix : remembers the fixed elements in the initial Sudoku matrix
     * State constructor : initilializes both the matrices
     * neighbour() : find a neighbour of the curr matrix and returns the state for it
     * fitness() : evaluates the fitness of the curr state of Sudoku and return an int value
     * printState() : prints the current state matrix **/
    int curr[N][N];
    int f[N][N];
public:
    state(int a[N][N],int fix[N][N]){

        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++) {
                curr[i][j] = a[i][j];
                f[i][j] = fix[i][j];
            }
    }

    state neighbour(){
        int i,j,k1,k2,k3,k4;
        int array2[N][N];
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                array2[i][j] = curr[i][j];
//        std::cout <<"in neighbour"<< std::endl;

        i = randomGenerator(N);
        j = randomGenerator(N);

//        std::cout<<i<< " "<<j<<std::endl;
        do{
            k1 = randomGenerator(SRN);
            k2 = randomGenerator(SRN);

            k3 = randomGenerator(SRN);
            k4 = randomGenerator(SRN);
//            std::cout<<k1<< " "<<k2<<" "<<k3<<" "<<k4<<std::endl;

//            std::cout <<"searching for values to be switched No!  "<<i-(i%SRN)+k1<<" "<<j - (j%SRN) + k2<<" "<<i-(i%SRN)+k3<<" "<<j - (j%SRN) + k4<<std::endl;
        }while(f[i-i%SRN+k1][j - j%SRN + k2]||f[i-i%SRN+k3][j - j%SRN + k4]);

//        std::cout<<"switched indices - ("<<i-i%SRN+k1<<","<<j - j%SRN + k2<<") ("<<i-i%SRN+k3<<","<<j - j%SRN + k4<<"\n";

        array2[i-i%SRN+k1][j - j%SRN + k2] = curr[i-i%SRN+k3][j - j%SRN + k4];
        array2[i-i%SRN+k3][j - j%SRN + k4] = curr[i-i%SRN+k1][j - j%SRN + k2];
//        std::cout <<"values swapped"<< std::endl;
//        std::cout <<"out of neighbour"<< std::endl;

//        for(i=0;i<N;i++) {
//            for (j = 0; j < N; j++)
//                std::cout << array2[i][j] << " ";
//            std::cout<<"\n";
//        }
        state s2(array2,f);

        return s2;
    }

    int fitness(){
        int count = 0,cost;
        bool flag;
        int i,j;
        for(int k=0;k<N;k++) {
            for (i=0;i<N;i++) {
                flag = false;
                cost =0;
                for (j = 0; j < N; j++) {
                    if (curr[i][j] == k){
                        flag = true;
                        cost++;
                    }
                }

                if(flag == false)
                    cost++;
                else
                    cost--;
//                std::cout<<"Cost for row "<<i<<" "<<cost<<"\n";
                count = cost + count;
            }
        }

        cost = 0;
        for(int k=0;k<N;k++) {
            for (i=0;i<N;i++) {
                flag = false;
                cost=0;
                for (j = 0; j < N; j++) {
                    if (curr[j][i] == k) {
                        flag = true;
                        cost++;
                    }
                }
                if(flag == false)
                    cost++;
                else
                    cost--;
//                std::cout<<"Cost for col "<<i<<" "<<cost<<"\n";
                count = cost + count;

            }
        }
        return count;
    }
    void printState()
    {
        std::cout<<"Printing state matrix now ------- \n";
        for (int i = 0; i<N; i++)
        {
            for (int j = 0; j<N; j++)
                std::cout<<curr[i][j]<<" ";
            std::cout<<"\n";
        }
        std::cout<<"\n";
    }

};



class SimulatedAnnealingAlgorithm {
    /**
 * The Simulated Annealing Algorithm with :
     * Temperature T : the temperature at a given time stamp
     * Tmin : minimum temperature the algorithm should go to
     * alpha : the value mulitplied to T to decrease the temperature
     * numIterations : the number of iterations at a particular tempertaure T for which the algorithm runs
     * f : ideal fitness value for the state
     * p : threshold for probabilty if the neighbour state has worse fitness value
     * SimulatedAnnealingALgorithm : Constructor to initilaise the variables
     * run() : Simulates the algorithm
 */
    double T;
    double Tmin;
    double alpha;
    int numIterations;
    double f;
    double p;

public:
    /**
     * Create a new state with the initial temperature.
     */
    SimulatedAnnealingAlgorithm(double T, double Tmin, double a, int num,int fstop, double p) {
        this->T = T;
        this->Tmin = Tmin;
        this->alpha = a;
        this->numIterations = num;
        this->f = fstop;
        this->p = p;
    }

    state run(Sudoku *Board) {

        Board->init_solution();
        Board->printSudoku();

        state currState(Board->mat,Board->fix);
        currState.printState();

        state best = currState;
        while (T > Tmin) {
            for (int i = 0; i < numIterations; i++) {
                std::cout <<"Iteration for T = "<<T<<"-----"<<i<< std::endl;

                state next = currState.neighbour();
//                std::cout <<"Printing next state "<< std::endl;
//                next.printState();

                int e = currState.fitness() ;
//                std::cout <<"current fitness value received  "<< std::endl;

                int ep = next.fitness();
                std::cout <<"fitness current ---- "<<e << std::endl;
                std::cout <<"fitness next  ---- "<<ep << std::endl;

                double threshold = ep < e ? 1.0 : std::exp(-1.0 * (ep-e) / T);

                std::cout <<"threshold value ---- "<<threshold << std::endl;

                if (threshold > p)
                    currState = next;

                std::cout <<"Fitness value ------"<<currState.fitness() << std::endl;

                if (currState.fitness() <= f)
                    return currState;

                // Check if we are the best seen so far, and if so, copy.
                if (best.fitness() < currState.fitness()) {
                    best = currState;
                    std::cout << "Best: " << best.fitness() << '\n';
                }
            }
            T *= alpha; // Decreases T, cooling phase

        }

        return best;

    }
};
