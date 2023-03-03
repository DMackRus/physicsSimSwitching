//
// Created by dave on 03/03/23.
//

#ifndef PHYSICSSIMSWITCHING_MODELTRANSLATOR_H
#define PHYSICSSIMSWITCHING_MODELTRANSLATOR_H

#include "../stdInclude/stdInclude.h"

#include "../physicsSimulators/MuJoCoHelper.h"

struct bodyStateVec{
    string name;
    bool activeLinearDOF[3];
    bool activeAngularDOF[3];
};

struct stateVectorList{
    vector<robot> robots;
    vector<bodyStateVec> bodiesStates;
};

class modelTranslator {
public:
    modelTranslator(physicsSimulator &_physicsSimulator, stateVectorList _stateVector);

    MatrixXd returnStateVector();

    int stateVectorSize;
    struct stateVectorList mystateVector;

private:
    physicsSimulator &myPhysicsSimulator;

};

#endif //PHYSICSSIMSWITCHING_MODELTRANSLATOR_H