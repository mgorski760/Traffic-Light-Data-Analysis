/*
Program Name: Red Light Cameras
Author: MARCIN GORSKI, mgors@uic.edu, UIN: 673137078
Date: 3/26/2025

Description: 
Program that displays Red Light Camera data from user prompted inputs.

Notes:
-hi
*/

#include <iostream>
#include <fstream> //Input files
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "cameraRecord.h"
#include "neighborhood.h"
#include "uniqueCamera.h"

using namespace std;

void readFile(vector<cameraRecord>& recordList, string txtFile);
int getNumCameras(vector<cameraRecord>& recordList);
int getTotalViolations(vector<cameraRecord>& recordList);
int getMostViolations(vector<cameraRecord>& recordList);
void getNeighborhoods(vector<neighborhood>& ngbrList, vector<cameraRecord>& recordList);
void importCameraRecords(vector<neighborhood>& ngbrList, vector<cameraRecord>& recordList);
void getMonthViolations(vector<int>& monthList, vector<cameraRecord>& recordList);
void printMonthViolations(vector<int>& monthList);
void getUniqueCameras(vector<uniqueCamera>& uniCamList, vector<cameraRecord>& recordList);
void findUniqueCameras(vector<uniqueCamera>& uniCamList, string keyword);

int main() {

    using namespace std;
    
    vector<cameraRecord> recordList = {};
    vector<neighborhood> neighborhoodList = {};
    vector<int> violationsCountMonth;
    vector<uniqueCamera> uniCamList;
    violationsCountMonth.assign(12,0);
    
    bool isQuit = false;
    string txtFile;
    int input;
    string keyword;

    cout << "Enter file to use: ";
    cin >> txtFile;

    readFile(recordList, txtFile);

    while(isQuit == false){

        cout << "Select a menu option:" << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. Results by neighborhood" << endl;
        cout << "  3. Chart by month" << endl;
        cout << "  4. Search for cameras" << endl;
        cout << "  5. Exit" << endl;
        cout << "Your choice: ";

        cin >> input;
        cout << endl;

        switch(input){
            case 1: 
                //data overview
                cout << "Read file with " << recordList.size() << " records." << endl;
                cout << "There are " << getNumCameras(recordList) << " cameras." << endl;
                cout << "A total of " << getTotalViolations(recordList) << " violations." << endl;
                cout << "The most violations in one day were " << recordList[getMostViolations(recordList)].getViolations() <<
                        " on " << recordList[getMostViolations(recordList)].getDate() << 
                        " at " << recordList[getMostViolations(recordList)].getIntersection() 
                        << endl;

                break;
            case 2:
                //list most violations by neighborhood
                getNeighborhoods(neighborhoodList, recordList);
                importCameraRecords(neighborhoodList, recordList);

                sort(neighborhoodList.begin(),neighborhoodList.end());

                for(int i = 0; i < (signed)neighborhoodList.size(); i++){
                    cout << setw(25) << left << neighborhoodList[i].getName() << setw(4) << right << neighborhoodList[i].getCameras() << setw(7) << right << neighborhoodList[i].getViolations() << endl;
                }

                break;
            case 3:
                //display month data 
                getMonthViolations(violationsCountMonth, recordList);
                printMonthViolations(violationsCountMonth);

                break;
            case 4:
                //user search
                cout << endl;
                cout << "What should we search for? ";
                cin.ignore();
                getline(cin, keyword);
                getUniqueCameras(uniCamList, recordList);
                findUniqueCameras(uniCamList, keyword);

                break;
            case 5:
                //exit
                isQuit = true;
                
                break;
            default:
                break;
        }
        
    }
}

//Reads txt file, and appends to the vector of cameraRecords.
//TAKES: txtFile's name and vector of cameraRecords.
void readFile(vector<cameraRecord>& recordList, string txtFile){

    string intersection;
    string address;
    string cameraID;
    string date;
    string violations;
    string neighborhood;

    ifstream fileIn; 
    fileIn.open(txtFile);

    string line;
    
    if(fileIn.is_open()){
        while(getline(fileIn, line)){//Until eof

        /*
        How this works:
        
        1. assigns current value to a substr of current line up to
        index of first ',' found
        
        2. erases the current value's section of the string, including
        the ',' index (adding +1 to find)
        */
        
        //get intersection
        intersection = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        
        //get address
        address = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);

        //get cameraID
        cameraID = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);

        //get date
        date = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);

        //get violations
        violations = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);
        
        //get neighborhood
        neighborhood = line.substr(0,line.find(','));
        line.erase(0,line.find(',')+1);

        //create cameraRecord object & store it to vector of cameraRecords
        recordList.push_back(cameraRecord(intersection,address,stoi(cameraID),date,stoi(violations),neighborhood));
        }

    fileIn.close();
    }
}

//Returns the amount of unique cameras in recordList
//TAKES: Vector of cameraRecords.
//RETURNS: Total amount of unique cameras.
int getNumCameras(vector<cameraRecord>& recordList){

    vector<int> cameraIDList = {};
    int currentID;
    bool isFound = false;
    
    for(int i = 0; i < (signed)recordList.size(); i++){

        currentID = recordList[i].getID();
        isFound = false;
        
        for(int j = 0; j < (signed)cameraIDList.size(); j++){
            if(cameraIDList[j] == currentID){
                isFound = true;
                break;
            }
        }

        if(isFound == false){
            cameraIDList.push_back(currentID);
        }

    }

    return cameraIDList.size();

}

//Returns the total amount of cameraRecord violations.
//TAKES: Vector of cameraRecords.
//RETURNS: total amount of violations.
int getTotalViolations(vector<cameraRecord>& recordList){

    int totalCount = 0;

    for(int i = 0; i < (signed)recordList.size(); i++){
        totalCount += recordList[i].getViolations();
    }

    return totalCount;
}

//Returns the first index of most violations in recordList's cameraRecords.
//TAKES: Vector of cameraRecords
//RETURNS: int of the index of most violations. 
int getMostViolations(vector<cameraRecord>& recordList){

    int highestIndex = 0; //index of highest value in camera record vector
    
    for(int i = 1; i < (signed)recordList.size(); i++){
    
        if(recordList[highestIndex].getViolations() < recordList[i].getViolations()){
            highestIndex = i;
        }  
    }

    return highestIndex;
}

//Creates neighborhood objects from the vector of cameraRecords.
//TAKES: Vector of neighborhoods (not popluated) and vector of cameraRecords.
void getNeighborhoods(vector<neighborhood>& ngbrList, vector<cameraRecord>& recordList){

    string currentNgbr;
    bool isFound;

    for(int i = 0; i < (signed)recordList.size(); i++){
        
        isFound = false;
        currentNgbr = recordList[i].getNeighborhood();
        
        for(int j = 0; j < (signed)ngbrList.size(); j++){
            if(currentNgbr == ngbrList[j].getName()){
                isFound = true;
                break;
            }
        }

        if(isFound == false){
            ngbrList.push_back(neighborhood(currentNgbr));
        }
    }
}

//Imports all camera records into their respective neighborhoods. (Requires getNeighborhoods to be ran first.)
//TAKES: Vector of neighborhood objects and vector of cameraRecords.
void importCameraRecords(vector<neighborhood>& ngbrList, vector<cameraRecord>& recordList){
    
    for(int i = 0; i < (signed)ngbrList.size(); i++){
        for(int j = 0; j < (signed)recordList.size(); j++){
            if(ngbrList[i].getName() == recordList[j].getNeighborhood()){
                ngbrList[i].importRecord(recordList[j]);
            }
        }
    }
}

//Populates a vector on integers with violations corresponding to the month from vector cameraRecords (EXAMPLE: monthList[0] -> All the violations in january)
//TAKES: int Vector with 12 elements and vector of cameraRecords.
void getMonthViolations(vector<int>& monthList, vector<cameraRecord>& recordList){

    monthList.assign(12,0);
    int currentM;
    
    for(int i = 0; i < (signed)recordList.size(); i++){

        currentM = recordList[i].getMonth();
        
        switch(currentM){
            case 1:
                monthList[0] += recordList[i].getViolations();
                break;
            case 2:
                monthList[1] += recordList[i].getViolations();
                break;
            case 3:
                monthList[2] += recordList[i].getViolations(); 
                break;
            case 4:
                monthList[3] += recordList[i].getViolations();
                break;
            case 5:
                monthList[4] += recordList[i].getViolations();
                break;
            case 6:
                monthList[5] += recordList[i].getViolations();
                break;
            case 7:
                monthList[6] += recordList[i].getViolations();
                break;
            case 8:
                monthList[7] += recordList[i].getViolations();
                break;
            case 9:
                monthList[8] += recordList[i].getViolations();
                break;
            case 10:
                monthList[9] += recordList[i].getViolations();
                break;
            case 11:
                monthList[10] += recordList[i].getViolations();
                break;
            case 12:
                monthList[11] += recordList[i].getViolations();
                break;
        }
    }    
}

//Print's violation data by month in accordance to project instructions.
//TAKES: Pre-populated vector on integers with violations corresponding to the month from vector cameraRecords (EXAMPLE: monthList[0] -> All the violations in january)
void printMonthViolations(vector<int>& monthList){
    
    for(int i = 0; i < (signed)monthList.size(); i++){
        monthList[i] = monthList[i]/1000;
    }

    cout << "January        " << string(monthList[0],'*') << endl;
    cout << "February       " << string(monthList[1],'*') << endl;
    cout << "March          " << string(monthList[2],'*') << endl;
    cout << "April          " << string(monthList[3],'*') << endl;
    cout << "May            " << string(monthList[4],'*') << endl;
    cout << "June           " << string(monthList[5],'*') << endl;
    cout << "July           " << string(monthList[6],'*') << endl;
    cout << "August         " << string(monthList[7],'*') << endl;
    cout << "September      " << string(monthList[8],'*') << endl;
    cout << "October        " << string(monthList[9],'*') << endl;
    cout << "November       " << string(monthList[10],'*') << endl;
    cout << "December       " << string(monthList[11],'*') << endl;
}

//Populates the uniCamList with unique cameras found in recordList
//TAKES: Vector of uniqueCamera and cameraRecord
void getUniqueCameras(vector<uniqueCamera>& uniCamList, vector<cameraRecord>& recordList){

    bool isFound;
    
    for(int i = 0; i < (signed)recordList.size(); i++){

        isFound = false;
        
        for(int j = 0; j < (signed)uniCamList.size(); j++){
            if(uniCamList[j].getID() == recordList[i].getID()){
                isFound = true;
                break;
            }
        }

        if(isFound == false){
            uniCamList.push_back(uniqueCamera(recordList[i].getID(), recordList[i].getAddress(), recordList[i].getIntersection(), recordList[i].getNeighborhood()));
        }
    }
}

//Prints any unique camera objects that relate to the keyword.
//TAKES: Pre-popluated vector of unique camera objects and user's keyword.
void findUniqueCameras(vector<uniqueCamera>& uniCamList, string keyword){

    transform(keyword.begin(), keyword.end(), keyword.begin(),::toupper); //Sets keyword to all caps

    int searchCount = 0;
    
    for(int i = 0; i < (signed)uniCamList.size(); i++){

        if(uniCamList[i].getNeighborhoodUPPER().find(keyword) != string::npos){ //keyword found in neighborhood 
            uniCamList[i].print();
            searchCount++;
        } else if(uniCamList[i].getIntersection().find(keyword) != string::npos){ //keyword found in intersection
            uniCamList[i].print();
            searchCount++;
        }
    }
    
    if(searchCount == 0){
        cout << "No cameras found." << endl;
    }
}