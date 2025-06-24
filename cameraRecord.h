#pragma once
#include <string>

using namespace std;

class cameraRecord {
    public:
        //constructors
        cameraRecord(string intersection, string address, int cameraID, string date, int violations, string neighborhood);

        //accessors
        string getIntersection();
        string getAddress();
        int getID();
        string getDate();
        int getViolations();
        string getNeighborhood();
        int getMonth();
        
    private:
        string intersection;
        string address;
        int cameraID;
        string date;
        int violations;
        string neighborhood;


};
