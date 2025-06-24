#include <iostream>
#include <algorithm>    
#include "uniqueCamera.h"

//constructor
uniqueCamera::uniqueCamera(int ID, string address, string intersection, string neighborhood){
    this->ID = ID;
    this->address = address;
    this->intersection = intersection;
    this->neighborhood = neighborhood;
}

//accessors
int uniqueCamera::getID(){
    return ID;
}
string uniqueCamera::getAddress(){
    return address;
}
string uniqueCamera::getIntersection(){
    return intersection;
}
string uniqueCamera::getNeighborhood(){
    return neighborhood;
}
void uniqueCamera::print(){
    cout << "Camera: " << ID << endl;
    cout << "Address: " << address << endl;
    cout << "Intersection: " << intersection << endl;
    cout << "Neighborhood: " << neighborhood << endl;
}
string uniqueCamera::getNeighborhoodUPPER(){
    string upper = neighborhood;
    transform(upper.begin(), upper.end(), upper.begin(),::toupper);

    return upper;
}


