#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

const int N = 10;
const float J = 1;
const float T = 8;
const float B = 1/T;
const int dimension = 2;
const int totalSpins = pow(N,dimension);

int getElement(vector<int> matrix, int address) {
    return matrix[address];
}

void setElement(vector<int> &matrix, int address, int val) {
    matrix[address] = val;
}

void initializeLattice(vector<int> &lattice) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 1);
    
    for (int i = 0; i < totalSpins; i++) {
        setElement(lattice,i,-1);
    }
}


vector<int> getNeighbours(int site) {
    vector<int> neighbours ={};

    int posSite, negSite;

    for (int d = 1;d <= dimension; d++) {
        
        posSite = int(pow(N,d)) * (site / int(pow(N,d)) ) + (site + int(pow(N,d-1)) + int(pow(N,dimension)) ) % ( int(pow(N,d)) );
        negSite = int(pow(N,d)) * (site / int(pow(N,d)) ) + (site - int(pow(N,d-1)) + int(pow(N,dimension)) ) % ( int(pow(N,d)) );      
        
        neighbours.push_back(posSite);
        neighbours.push_back(negSite);
        
    }
    return neighbours;
}


void showLattice(vector<int> &lattice, bool showValues = false ) {
    
    for (int site = 0; site < totalSpins; site++) {
        
        for (int dim = dimension; dim > 0; dim--){
            if (site %(int(pow(N,dim))) == 0) {
                cout << "\n";
            }            
        } 

        if (showValues){
            
            if (lattice[site] < 0){
                cout << lattice[site] << ",";
            }
            else{
                cout << " " << lattice[site] << ",";
            }
        }
        else{
            if (lattice[site] == 1) {
                cout << "+ ";
            } 
            else {
                cout << "- ";
            }
        }
    }
    
    


    int plusCount = 0, minusCount = 0;
    int agrees = 0, disagrees = 0;

    double magnetisation = 0;
    for (int site = 0; site < totalSpins; site++) {
        
        magnetisation = magnetisation + getElement(lattice,site);
        vector<int> siteNeighbours = getNeighbours(site);

        for (int dir = 0; dir < siteNeighbours.size(); dir++) {
            if (lattice[site]*lattice[siteNeighbours[dir]] ==1) {
                agrees++;
            } 
            else{
                disagrees++;
            }
        } 
    }

    
   
    

    std::cout << endl;

    std::cout << "Plus count: " << plusCount << " " <<"Minus count: " << minusCount <<"\n";
    std::cout << "Agrees: " << agrees << " " <<"Disagrees: " << disagrees <<"\n";
    std::cout << "Magnetisation: " << magnetisation << " " <<"Mean Magnetisation: " << magnetisation / (totalSpins) <<"\n";
    
}








void flipSpins(vector<int> &lattice, int site) {
        lattice[site] = -1*lattice[site];
}

void flipSpins(vector<int> &lattice, vector<int> sites) {
    for (int i = 0; i < sites.size(); i++) {
        lattice[sites[i]] = -1*lattice[sites[i]];  // flip the spin
    }
}

int main()
{
    
    
    
    
    srand( (unsigned)time( NULL ) );
    vector<int> lattice(totalSpins,0);
    initializeLattice(lattice);


    cout << "\n";

    

    int counter = 0;
    
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, totalSpins-1);    
    
    int startSite = distrib(gen);
    int startState;

    
    while (counter < 1000) {
        
        startSite = distrib(gen);
        startState = getElement(lattice,startSite);
        
        vector<int> cluster = {startSite};
        vector<int> stackOld = {startSite};
        
        
        
        while (not stackOld.empty()) {
            vector<int> stackNew = {};
            
            // For all members of stack Old
            for (int i=0;i<stackOld.size();i++) {
                
                // Get the neighbours
                vector<int> neighbs = getNeighbours(stackOld[i]);
                
                //For each neighbour
                for (int j=0;j<neighbs.size();j++) {
                    
                    //if it isn't in the cluster
                    if ( find(cluster.begin(), cluster.end(), neighbs[j]) != cluster.end() ) {
                    }
                    else {
                        // If same state as start
                        if (getElement(lattice, neighbs[j]) == startState) {
                            
                            if  ((double) rand() / (RAND_MAX) <        (1-exp(-2*B*J))){
                                stackNew.push_back(neighbs[j]);
                                cluster.push_back(neighbs[j]);
                            }
                        }
                    }
                }
                stackOld = stackNew;
            }

        }
        flipSpins(lattice, cluster);
        counter++;
    }


    showLattice(lattice);
    return 0;


}