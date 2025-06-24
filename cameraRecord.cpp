#include "cameraRecord.h"
#include <string>

//constructor
cameraRecord::cameraRecord(std::string intersection, std::string address, int cameraID, std::string date, int violations, std::string neighborhood){
    this->intersection = intersection;
    this->address = address;
    this->cameraID = cameraID;
    this->date = date;
    this->violations = violations;
    this->neighborhood = neighborhood;
}

//accessors
string cameraRecord::getIntersection(){
    return intersection;
}

string cameraRecord::getAddress(){
    return address;
}

int cameraRecord::getID(){
    return cameraID;
}

string cameraRecord::getDate(){
    string reversedDate = date;
    string day;
    string month;
    string year;

    year = reversedDate.substr(0,reversedDate.find('-'));
    reversedDate.erase(0,reversedDate.find('-')+1);

    month = reversedDate.substr(0,reversedDate.find('-'));
    reversedDate.erase(0,reversedDate.find('-')+1);

    day = reversedDate.substr(0,reversedDate.find('-'));
    reversedDate.erase(0,reversedDate.find('-')+1);

    reversedDate = month + "-" + day + "-" + year;

    return reversedDate;
}

int cameraRecord::getViolations(){
    return violations;
}

string cameraRecord::getNeighborhood(){
    return neighborhood;
}

int cameraRecord::getMonth(){
    string tempDate = date;
    tempDate.erase(0,tempDate.find('-')+1);

    return stoi(tempDate.substr(0,tempDate.find('-')));
}
