#include "Motor.hpp"
#include <iostream>

using namespace std;

bool Motor::error_test(){
    return true;
}

bool Motor::is_faulty(bool verbose){
    if (!is_connected)
        return true;

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
    // CONNECTION_CHECK;

    VCS_ClearFault(gateway, id, &error_code); // clear fault just in case
    print_VCS_error(error_code, __FUNCTION__);
    return (bool)error_code;
}


bool Motor::set_output_state(bool output_active){
    // CONNECTION_CHECK;

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