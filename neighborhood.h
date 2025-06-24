#pragma once
#include <string>
#include <vector>
#include "cameraRecord.h"


using namespace std;

class neighborhood {
    public:
        //constructors
        neighborhood(string name);

        //overload operators
        bool operator<(neighborhood& lhs);

        //accessors
        int getViolations();
        string getName();
        int getCameras();

        //mutators
        void importRecord(cameraRecord);

    private:
        string name;
        int totalCameras = 0;
        int totalViolations = 0;
        vector<cameraRecord> recordList = {};
};
