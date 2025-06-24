#pragma once
#include <string>
#include <iostream>

using namespace std;

class uniqueCamera {
    public:
        //constructor
        uniqueCamera(int ID, string address, string intersection, string neighborhood);
        
        //accessors
        int getID();
        string getAddress();
        string getIntersection();
        string getNeighborhood();
        void print();
        string getNeighborhoodUPPER();
    private:
        int ID;
        string address;
        string intersection;
        string neighborhood;
};