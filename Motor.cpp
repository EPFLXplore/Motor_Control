#include <Motor.hpp>

using namespace std;

#ifndef ROSCPP_ROS_H
#define CONNECTION_CHECK                                      \
    if (!is_connected)                                        \
    {                                                         \
        cerr << "Node " << id << " is not connected" << endl; \
        return false;                                         \
    }
#else
#define CONNECTION_CHECK                                        \
    if (!is_connected)                                          \
    {                                                           \
        ROS_ERROR_STREAM("Node " << id << " is not connected"); \
        return false;                                           \
    }
#endif

// private functions
void print_VCS_error(unsigned int error_code, const char *func){
    static char error_msg[100];
    if (error_code)
    {
        VCS_GetErrorInfo(error_code, error_msg, 100);
#ifdef ROSCPP_ROS_H
        ROS_ERROR_STREAM("ERR 0x" << hex << error_code << dec << " : " << error_msg << " in " << func << "()");
#else
        cerr << "ERR 0x" << hex << error_code << dec << " : " << error_msg << " in " << func << "()" << endl;
#endif
    }
}

// public functions
void *open_gateway(void){
    unsigned int error_code = 0;
    void *gateway = VCS_OpenDevice((char *)"EPOS4", (char *)"MAXON SERIAL V2", (char *)"USB", (char *)"USB0", &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    // VCS_ClearFault(gateway, 0, &error_code);
    // print_VCS_error(error_code);
    return gateway;
}

void close_gateway(void *gateway){
    unsigned int error_code = 0;
    VCS_CloseDevice(gateway, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
}

// CONSTRUCTORS
Motor::Motor(void *KeyHandle, unsigned short node_id, signed char mode){
    error_code = 0;
    gateway = KeyHandle;
    id = node_id;
    pos_ref = 0;
    is_calibrated = false;

    unsigned short* motor_type(0);

    VCS_GetMotorType(gateway, id, motor_type, &error_code);
    is_connected = (error_code) ? false : true; // SDO TIMEOUT  == 0x5040000

    error_test(); // test de connection
    
    if (mode) {
        
        VCS_SetOperationMode(gateway, id, mode, &error_code);
        
        
        if (error_code)
        {
            print_VCS_error(error_code, __FUNCTION__);
            op_mode_ = 0;
        }
        else
            op_mode_ = mode;
        if (mode == OMD_PROFILE_POSITION_MODE)
            VCS_SetPositionProfile(gateway, id, max_speed_, max_accel_, max_decel_, &error_code);
        else if (mode == OMD_PROFILE_VELOCITY_MODE)
            VCS_SetVelocityProfile(gateway, id, max_accel_, max_decel_, &error_code);
        if (error_code)
        {
            print_VCS_error(error_code, __FUNCTION__);
        }
    }
    
}

// UTILITY FUNCTIONS

bool Motor::set_op_mode(ControlMode control_mode){
    CONNECTION_CHECK;

    switch (control_mode){
        case POSISTION:
            if(speed_limit_ and accel_limit_)
                VCS_SetOperationMode(gateway, id, OMD_PROFILE_POSITION_MODE, 
                                     &error_code);
            else
                VCS_SetOperationMode(gateway, id, OMD_POSITION_MODE, 
                                     &error_code);
        break;
        case SPEED:
            if(accel_limit_)
                VCS_SetOperationMode(gateway, id, OMD_PROFILE_VELOCITY_MODE, 
                                     &error_code);
            else
                VCS_SetOperationMode(gateway, id, OMD_VELOCITY_MODE, 
                                     &error_code);
        break;
        case CURRENT:
            VCS_SetOperationMode(gateway, id, OMD_CURRENT_MODE,
                                 &error_code);
            break;
    }
    
    error_test();

    control_mode_ = control_mode;
    return true;
}

bool Motor::set_output_state(bool output_active){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    VCS_ClearFault(gateway, id, &error_code); // clear fault just in case
    print_VCS_error(error_code, __FUNCTION__);

    if (output_active)
        VCS_SetEnableState(gateway, id, &error_code);
    else
        VCS_SetDisableState(gateway, id, &error_code);
    print_VCS_error(error_code, __FUNCTION__);

    return !error_code;
}

bool Motor::is_faulty(bool verbose){
    if (!is_connected)
        return true;

    unsigned int error_code = 0;
    int in_fault = false;
    VCS_GetFaultState(gateway, id, &in_fault, &error_code);
    print_VCS_error(error_code, __FUNCTION__);

    if (in_fault && !error_code && verbose){
        unsigned int device_error = 0;
        unsigned char nb_err = 0;
        VCS_GetNbOfDeviceError(gateway, id, &nb_err, &error_code);
        print_VCS_error(error_code, __FUNCTION__);
        if (nb_err && !error_code){
            static char error_msg[100];
            for (unsigned char i = 1; i <= nb_err; i++){
                VCS_GetDeviceErrorCode(gateway, id, i, &device_error, &error_code);
                VCS_GetErrorInfo(device_error, error_msg, 100);
#ifdef ROSCPP_ROS_H
                ROS_WARN_STREAM("FAULT : Node " << id << " : " << error_msg);
#else
                cerr << "FAULT : Node " << id << " : " << error_msg << endl;
#endif
            }
        }
    }

    return (in_fault || error_code);
}

bool Motor::clear_fault(){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    VCS_ClearFault(gateway, id, &error_code); // clear fault just in case
    print_VCS_error(error_code, __FUNCTION__);
    return (bool)error_code;
}

void Motor::set_calibrated(bool calibrated){
    is_calibrated = calibrated;
}

bool Motor::calibrated(){
    return is_calibrated;
}
// bool Motor::set_position_ref(long pos) {
//     CONNECTION_CHECK;

//     unsigned int    error_code  = 0;
//     if ((op_mode_ != OMD_POSITION_MODE) &&
//         !this->set_operational_mode(OMD_POSITION_MODE))
//         return false;

//     VCS_SetPositionMust(gateway, id, pos + pos_ref, &error_code);
//     print_VCS_error(error_code, __FUNCTION__);
//     return !error_code;
// }

bool Motor::set_position_ref(long pos){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    if ((op_mode_ != OMD_PROFILE_POSITION_MODE) &&
        !this->set_operational_mode(OMD_PROFILE_POSITION_MODE))
        return false;

    VCS_MoveToPosition(gateway, id, pos + pos_ref, true, true, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return !error_code;
}

bool Motor::reset_position_counter(){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int pos;
    VCS_GetPositionIs(gateway, id, &pos, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    pos_ref = pos;

    // VCS_ResetPositionMarkerCounter(gateway, id, &error_code); // not available ???
    // print_VCS_error(error_code, __FUNCTION__);
    return !error_code;
}

int Motor::get_position_is(){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int pos;
    VCS_GetPositionIs(gateway, id, &pos, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return pos - pos_ref;
}

// Profile velocity mode

bool Motor::set_velocity_ref(long vel){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    if ((op_mode_ != OMD_VELOCITY_MODE) &&
        !this->set_operational_mode(OMD_PROFILE_VELOCITY_MODE))
        return false;

    VCS_MoveWithVelocity(gateway, id, vel, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return !error_code;
}

int Motor::get_velocity_is(){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int vel;
    VCS_GetVelocityIs(gateway, id, &vel, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return vel;
}

int Motor::get_current_is(){
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int cur;
    VCS_GetCurrentIsEx(gateway, id, &cur, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return cur;
}

// fonction de gestion d'erreur
void Motor::error_test(){
    error_code = 0;
}