#include "neighborhood.h"
#include "cameraRecord.h"
#include <iostream>

using namespace std;

//constructor
neighborhood::neighborhood(string name){
    this->name = name;
}
//overload operators
bool neighborhood::operator<(neighborhood& lhs){
    return  lhs.getViolations() < totalViolations;
}


//accessors
int neighborhood::getViolations(){
    return totalViolations;
}

string neighborhood::getName(){
    return name;
}
int neighborhood::getCameras(){
    return totalCameras;
}

//mutators
void neighborhood::importRecord(cameraRecord record){

    //update the total amount of cameras
    bool isFound = false;
    for(int i = 0; i < (signed)recordList.size(); i++){
        if(record.getID() == recordList[i].getID()){
            isFound = true;
            break;
        }
    }

    if(isFound == false){
        totalCameras++;
    }

    //add record to the list of records;
    recordList.push_back(record);

    //add violations
    totalViolations += record.getViolations();
}

