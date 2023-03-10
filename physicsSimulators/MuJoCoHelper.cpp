//
// Created by dave on 01/03/23.
//

#include "MuJoCoHelper.h"

// Empty constructor
MuJoCoHelper::MuJoCoHelper(vector<robot> _robots, vector<string> _bodies): physicsSimulator(_robots, _bodies) {
    std::cout << "created mujoco helper" << std::endl;
}

// ------------------------------------    ROBOT UTILITY   --------------------------------------------
// Checks whether a robot of this name exists in the simulation
bool MuJoCoHelper::isValidRobotName(string robotName, int &robotIndex, string &robotBaseJointName){
    bool validRobot = false;
    for(int i = 0; i < robots.size(); i++){
        if(robots[i].name == robotName){
            validRobot = true;
            robotBaseJointName = robots[i].jointNames[0];
            robotIndex = i;
        }
    }

    return validRobot;
}

// Sets a robot joint positions the given values
bool MuJoCoHelper::setRobotJointsPositions(string robotName, vector<double> jointPositions){

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        if(jointPositions.size() != robots[robotIndex].numActuators){
            cout << "Invalid number of joint positions\n";
            return false;
        }
    }
    else{
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());
    cout << "body id: " << jointId << endl;

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_qposadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < jointPositions.size(); i++){
        mdata->qpos[startIndex + i] = jointPositions[i];
    }

    return true;
}

// Sets a robot joint velocities the given values
bool MuJoCoHelper::setRobotJointsVelocities(string robotName, vector<double> jointVelocities){

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        if(jointVelocities.size() != robots[robotIndex].numActuators){
            cout << "Invalid number of joint positions\n";
            return false;
        }
    }
    else{
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < jointVelocities.size(); i++){
        mdata->qvel[startIndex + i] = jointVelocities[i];
    }

    return true;
}

bool MuJoCoHelper::setRobotJointsControls(string robotName, vector<double> jointControls){

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        if(jointControls.size() != robots[robotIndex].numActuators){
            cout << "Invalid number of joint positions\n";
            return false;
        }
    }
    else{
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < jointControls.size(); i++){
        mdata->ctrl[startIndex + i] = jointControls[i];
    }

    return true;
}

bool MuJoCoHelper::getRobotJointsPositions(string robotName, vector<double> &jointPositions){

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(!isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < robots[robotIndex].jointNames.size(); i++){
        jointPositions.push_back(mdata->qpos[startIndex + i]);
    }

    return true;
}

bool MuJoCoHelper::getRobotJointsVelocities(string robotName, vector<double> &jointVelocities) {

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(!isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < robots[robotIndex].jointNames.size(); i++){
        jointVelocities.push_back(mdata->qvel[startIndex + i]);
    }

    return true;
}

bool MuJoCoHelper::getRobotJointsAccelerations(string robotName, vector<double> &jointAccelerations){
    int robotIndex;
    string robotBaseJointName;
    if(!isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < robots[robotIndex].jointNames.size(); i++){
        jointAccelerations.push_back(mdata->qacc[startIndex + i]);
    }

    return true;
}

bool MuJoCoHelper::getRobotJointsControls(string robotName, vector<double> &jointControls) {

    // Check if the robot exists in the simulation
    int robotIndex;
    string robotBaseJointName;
    if(!isValidRobotName(robotName, robotIndex, robotBaseJointName)){
        cout << "That robot doesnt exist in the simulation\n";
        return false;
    }

    // Get the body id of the base link of the robot
    int jointId = mj_name2id(model, mjOBJ_JOINT, robotBaseJointName.c_str());

    if(jointId == -1){
        cout << "Base link of robot not found\n";
        return false;
    }
    int startIndex = model->jnt_dofadr[jointId];

    if(startIndex == -1){
        cout << "Invalid bodyId for robot\n";
        return false;
    }

    for(int i = 0; i < robots[robotIndex].jointNames.size(); i++){
        jointControls.push_back(mdata->ctrl[startIndex + i]);
    }

    return true;
}
// --------------------------------- END OF ROBOT UTILITY ---------------------------------------

// ------------------------------------- BODY UTILITY -------------------------------------------
bool MuJoCoHelper::isValidBodyName(string bodyName, int &bodyIndex){
    for(int i = 0; i < bodies.size(); i++){
        if(bodies[i] == bodyName){
            bodyIndex = i;
            return true;
        }
    }
    return false;
}

bool MuJoCoHelper::setBodyPose_quat(string bodyName, pose_7 pose){

    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qposIndex = model->jnt_qposadr[jointIndex];

    for(int i = 0; i < 3; i++){
        mdata->qpos[qposIndex + i] = pose.position(i);
    }

    for(int i = 0; i < 4; i++){
        mdata->qpos[qposIndex + 3 + i] = pose.quat(i);
    }

    mj_step(model, mdata);

    return true;
}

bool MuJoCoHelper::setBodyPose_angle(string bodyName, pose_6 pose){

    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qposIndex = model->jnt_qposadr[jointIndex];

    m_quat q = eul2Quat(pose.orientation);

    for(int i = 0; i < 3; i++){
        mdata->qpos[qposIndex + i] = pose.position(i);
    }

    for(int i = 0; i < 4; i++){
        mdata->qpos[qposIndex + 3 + i] = q(i);
    }

    return true;
}

bool MuJoCoHelper::setBodyVelocity(string bodyName, pose_6 velocity){

        int bodyIndex;
        if(!isValidBodyName(bodyName, bodyIndex)){
            cout << "That body doesnt exist in the simulation\n";
            return false;
        }

        int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
        const int jointIndex = model->body_jntadr[bodyId];
        const int qvelIndex = model->jnt_dofadr[jointIndex];

        for(int i = 0; i < 3; i++){
            mdata->qvel[qvelIndex + i] = velocity.position(i);
        }

        for(int i = 0; i < 3; i++){
            mdata->qvel[qvelIndex + 3 + i] = velocity.orientation(i);
        }

        return true;
}

bool MuJoCoHelper::getBodyPose_quat(string bodyName, pose_7 &pose){
    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qposIndex = model->jnt_qposadr[jointIndex];

    for(int i = 0; i < 3; i++){
        pose.position(i) = mdata->qpos[qposIndex + i];
    }

    for(int i = 0; i < 4; i++){
        pose.quat(i) = mdata->qpos[qposIndex + 3 + i];
    }

    return true;
}

bool MuJoCoHelper::getBodyPose_angle(string bodyName, pose_6 &pose){
    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qposIndex = model->jnt_qposadr[jointIndex];

    for(int i = 0; i < 3; i++){
        pose.position(i) = mdata->qpos[qposIndex + i];
    }

    m_quat tempQuat;

    for(int i = 0; i < 4; i++){
        tempQuat(i) = mdata->qpos[qposIndex + 3 + i];
    }

    m_point euler = quat2Eul(tempQuat);

    for(int i = 0; i < 3; i++){
        pose.orientation(i) = euler(i);
    }

    return true;
}

bool MuJoCoHelper::getBodyVelocity(string bodyName, pose_6 &velocity){
    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qvelIndex = model->jnt_dofadr[jointIndex];

    for(int i = 0; i < 3; i++){
        velocity.position(i) = mdata->qvel[qvelIndex + i];
    }

    for(int i = 0; i < 3; i++){
        velocity.orientation(i) = mdata->qvel[qvelIndex + 3 + i];
    }

    return true;
}

bool MuJoCoHelper::getBodyAcceleration(string bodyName, pose_6 &acceleration){
    int bodyIndex;
    if(!isValidBodyName(bodyName, bodyIndex)){
        cout << "That body doesnt exist in the simulation\n";
        return false;
    }

    int bodyId = mj_name2id(model, mjOBJ_BODY, bodyName.c_str());
    const int jointIndex = model->body_jntadr[bodyId];
    const int qvelIndex = model->jnt_dofadr[jointIndex];

    for(int i = 0; i < 3; i++){
        acceleration.position(i) = mdata->qacc[qvelIndex + i];
    }

    for(int i = 0; i < 3; i++){
        acceleration.orientation(i) = mdata->qacc[qvelIndex + 3 + i];
    }

    return true;
}
// --------------------------------- END OF BODY UTILITY ---------------------------------------

// ------------------------------- System State Functions -----------------------------------------------
bool MuJoCoHelper::appendCurrentSystemStateToEnd(){

    mjData *d = mj_makeData(model);
    cpMjData(model, d, mdata);
    string goalObj = "goal";
    pose_6 goalObjPose;
    getBodyPose_angle(goalObj, goalObjPose);
    cout << "goalObjPose: " << goalObjPose.position(0) << ", " << goalObjPose.position(1) << ", " << goalObjPose.position(2) << endl;

    savedSystemStatesList.push_back(d);
}

bool MuJoCoHelper::saveSystemStateToIndex(int listIndex){
    mjData *d = mj_makeData(model);
    savedSystemStatesList[listIndex] = d;
}

bool MuJoCoHelper::loadSystemStateFromIndex(int listIndex){
    cpMjData(model, mdata, savedSystemStatesList[listIndex]);
    string goalObj = "goal";
    pose_6 goalObjPose;
    getBodyPose_angle(goalObj, goalObjPose);
    cout << "goalObjPose: " << goalObjPose.position(0) << ", " << goalObjPose.position(1) << ", " << goalObjPose.position(2) << endl;
}

bool MuJoCoHelper::deleteSystemStateFromIndex(int listIndex){
    mj_deleteData(savedSystemStatesList[listIndex]);
    savedSystemStatesList.erase(savedSystemStatesList.begin() + listIndex);
}

bool MuJoCoHelper::clearSystemStateList(){
    for(int i = 0; i < savedSystemStatesList.size(); i++){
        mj_deleteData(savedSystemStatesList[i]);
    }
    savedSystemStatesList.clear();
}

void MuJoCoHelper::cpMjData(const mjModel* m, mjData* d_dest, const mjData* d_src){
    d_dest->time = d_src->time;
    mju_copy(d_dest->qpos, d_src->qpos, m->nq);
    mju_copy(d_dest->qvel, d_src->qvel, m->nv);
    mju_copy(d_dest->qacc, d_src->qacc, m->nv);
    mju_copy(d_dest->qacc_warmstart, d_src->qacc_warmstart, m->nv);
    mju_copy(d_dest->qfrc_applied, d_src->qfrc_applied, m->nv);
    mju_copy(d_dest->xfrc_applied, d_src->xfrc_applied, 6*m->nbody);
    mju_copy(d_dest->ctrl, d_src->ctrl, m->nu);
}
// ------------------------------- END OF SYSTEM STATE FUNCTIONS ----------------------------------------

bool MuJoCoHelper::stepSimulator(int steps){
    for(int i = 0; i < steps; i++){
        mj_step(model, mdata);
    }
    return true;
}

// --------------------------------- Visualization Functions ---------------------------------------
void MuJoCoHelper::initVisualisation() {

    // initialize visualization data structures
    mjv_defaultCamera(&cam);
    //mjv_defaultPerturb(&pert);				// what data type for pert?
    mjv_defaultOption(&opt);
    mjr_defaultContext(&con);

    cam.distance = 5;
    cam.azimuth = 110.9;
    cam.elevation = -19.9;
    cam.lookat[0] = 0.396;
    cam.lookat[1] = -0.0629;
    cam.lookat[2] = 0.1622;

    // create scene and context
    mjv_makeScene(model, &scn, 2000);
    mjr_makeContext(model, &con, mjFONTSCALE_150);
}

void MuJoCoHelper::updateScene(GLFWwindow *window){
    // update scene and render
    mjrRect viewport = {0, 0, 0, 0};
    glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
    mjv_updateScene(model, mdata, &opt, NULL, &cam, mjCAT_ALL, &scn);
    mjr_render(viewport, &scn, &con);
}

void MuJoCoHelper::mouseMove(double dx, double dy, bool button_left, bool button_right,  GLFWwindow *window){
// get current window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // get shift key state
    bool mod_shift = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
                      glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);

    //determine action based on mouse button
    mjtMouse action;
    if (button_right)
        action = mod_shift ? mjMOUSE_MOVE_H : mjMOUSE_MOVE_V;
    else if (button_left)
        action = mod_shift ? mjMOUSE_ROTATE_H : mjMOUSE_ROTATE_V;
    else
        action = mjMOUSE_ZOOM;

    // move camera
    mjv_moveCamera(model, action, dx / height, dy / height, &scn, &cam);
}

void MuJoCoHelper::scroll(double yoffset){
    mjv_moveCamera(model, mjMOUSE_ZOOM, 0, -0.05 * yoffset, &scn, &cam);
}

// --------------------------------- END OF VISUALIZATION FUNCTIONS ---------------------------------------

void MuJoCoHelper::initSimulator(double timestep, const char* fileName){
    char error[1000];

    model = mj_loadXML(fileName, NULL, error, 1000);

    model->opt.timestep = timestep;

    if( !model ) {

        printf("%s\n", error);
    }

    // make data corresponding to model
    mdata = mj_makeData(model);

    //model->opt.gravity[2] = 0;
}
