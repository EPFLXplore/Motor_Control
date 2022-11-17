#include "nav_motors.hpp"

// ---------- namespaces ----------

using namespace std;

#define WINDING_RES 0.573  // [Ohm]                                        // TODO : keep updated // TODO2: make this less stupid
#define SPEED_CONSTANT 100 // [rpm/V] origin value 236                    // TODO : keep updated // TODO2: make this less stupid

#define MAX_DRIVE_ACCEL 900   // [rpm/S] // default :   900
#define MAX_DRIVE_DECEL 3000  // [rpm/s] // default :  3000
#define MAX_STEER_VEL 6000    // [rpm]   // default : 10000
#define MAX_STEER_ACCEL 10000 // [rpm/s] // default : 10000

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
void print_VCS_error(unsigned int error_code, const char *func)
{
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
void *open_gateway(void)
{
    unsigned int error_code = 0;
    void *gateway = VCS_OpenDevice((char *)"EPOS4", (char *)"MAXON SERIAL V2", (char *)"USB", (char *)"USB0", &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    // VCS_ClearFault(gateway, 0, &error_code);
    // print_VCS_error(error_code);
    return gateway;
}

void close_gateway(void *gateway)
{
    unsigned int error_code = 0;
    VCS_CloseDevice(gateway, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
}

// CONSTRUCTORS
NAV_Motor::NAV_Motor(void *KeyHandle, unsigned short node_id, unsigned short exp_type, signed char mode)
{
    unsigned int error_code = 0;
    gateway = KeyHandle;
    id = node_id;
    pos_ref = 0;
    is_calibrated = false;

    VCS_GetMotorType(gateway, id, &motor_type, &error_code);
    is_connected = (error_code) ? false : true; // SDO TIMEOUT  == 0x5040000

    if (is_connected)
    {
        if (exp_type && (motor_type != exp_type))
        {
#ifdef ROSCPP_ROS_H
            ROS_WARN_STREAM("NAV_Motor " << id << " : " << ((motor_type == MT_DC_MOTOR) ? "DC motor" : (motor_type == MT_EC_SINUS_COMMUTATED_MOTOR) ? "EC sine motor"
                                                                                                                                                    : "EC block motor"));
#else
            cerr << "NAV_Motor " << id << " : " << ((motor_type == MT_DC_MOTOR) ? "DC motor" : (motor_type == MT_EC_SINUS_COMMUTATED_MOTOR) ? "EC sine motor"
                                                                                                                                            : "EC block motor")
                 << endl;
#endif
            // throw 0;
        }
        else
        {
#ifdef ROSCPP_ROS_H
            ROS_DEBUG_STREAM("NAV_Motor " << id << " : " << ((motor_type == MT_DC_MOTOR) ? "DC motor" : (motor_type == MT_EC_SINUS_COMMUTATED_MOTOR) ? "EC sine motor"
                                                                                                                                                    : "EC block motor"));
#else
            cout << "NAV_Motor " << id << " : " << ((motor_type == MT_DC_MOTOR) ? "DC motor" : (motor_type == MT_EC_SINUS_COMMUTATED_MOTOR) ? "EC sine motor"
                                                                                                                                            : "EC block motor")
                 << endl;
#endif
        }
        if (mode)
        {
            VCS_SetOperationMode(gateway, id, mode, &error_code);
            if (error_code)
            {
                print_VCS_error(error_code, __FUNCTION__);
                op_mode = 0;
            }
            else
                op_mode = mode;
            if (mode == OMD_PROFILE_POSITION_MODE)
                VCS_SetPositionProfile(gateway, id, MAX_STEER_VEL, MAX_STEER_ACCEL, MAX_STEER_ACCEL, &error_code);
            else if (mode == OMD_PROFILE_VELOCITY_MODE)
                VCS_SetVelocityProfile(gateway, id, MAX_DRIVE_ACCEL, MAX_DRIVE_DECEL, &error_code);
            if (error_code)
            {
                print_VCS_error(error_code, __FUNCTION__);
            }
        }
    }
    else
    {
#ifdef ROSCPP_ROS_H
        ROS_WARN_STREAM("NAV_Motor " << id << " : unresponsive");
#else
        cerr << "NAV_Motor " << id << " : unresponsive" << endl;
#endif

        if (error_code != 0x5040000)
        {
            print_VCS_error(error_code, __FUNCTION__);
            // throw 0;
        }
        motor_type = 0;
    }
}

// UTILITY FUNCTIONS
unsigned short NAV_Motor::get_id()
{
    return id;
}

bool NAV_Motor::connected()
{
    return is_connected;
}

void NAV_Motor::disconnect()
{
    is_connected = false;
}

bool NAV_Motor::set_operational_mode(signed char mode)
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    VCS_SetOperationMode(gateway, id, mode, &error_code);
    if (error_code)
    {
        print_VCS_error(error_code, __FUNCTION__);
        op_mode = 0;
        return false;
    }
    op_mode = mode;
    return true;
}

bool NAV_Motor::set_output_state(bool output_active)
{
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

bool NAV_Motor::is_faulty(bool verbose)
{
    if (!is_connected)
        return true;

    unsigned int error_code = 0;
    int in_fault = false;
    VCS_GetFaultState(gateway, id, &in_fault, &error_code);
    print_VCS_error(error_code, __FUNCTION__);

    if (in_fault && !error_code && verbose)
    {
        unsigned int device_error = 0;
        unsigned char nb_err = 0;
        VCS_GetNbOfDeviceError(gateway, id, &nb_err, &error_code);
        print_VCS_error(error_code, __FUNCTION__);
        if (nb_err && !error_code)
        {
            static char error_msg[100];
            for (unsigned char i = 1; i <= nb_err; i++)
            {
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

bool NAV_Motor::clear_fault()
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    VCS_ClearFault(gateway, id, &error_code); // clear fault just in case
    print_VCS_error(error_code, __FUNCTION__);
    return (bool)error_code;
}

void NAV_Motor::set_calibrated(bool calibrated)
{
    is_calibrated = calibrated;
}

bool NAV_Motor::calibrated()
{
    return is_calibrated;
}
// bool NAV_Motor::set_position_ref(long pos) {
//     CONNECTION_CHECK;

//     unsigned int    error_code  = 0;
//     if ((op_mode != OMD_POSITION_MODE) &&
//         !this->set_operational_mode(OMD_POSITION_MODE))
//         return false;

//     VCS_SetPositionMust(gateway, id, pos + pos_ref, &error_code);
//     print_VCS_error(error_code, __FUNCTION__);
//     return !error_code;
// }

bool NAV_Motor::set_position_ref(long pos)
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    if ((op_mode != OMD_PROFILE_POSITION_MODE) &&
        !this->set_operational_mode(OMD_PROFILE_POSITION_MODE))
        return false;

    VCS_MoveToPosition(gateway, id, pos + pos_ref, true, true, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return !error_code;
}

bool NAV_Motor::reset_position_counter()
{
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

int NAV_Motor::get_position_is()
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int pos;
    VCS_GetPositionIs(gateway, id, &pos, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return pos - pos_ref;
}

// bool NAV_Motor::set_velocity_ref(long vel) {
//     CONNECTION_CHECK;

//     unsigned int    error_code  = 0;
//     if ((op_mode != OMD_VELOCITY_MODE) &&
//         !this->set_operational_mode(OMD_VELOCITY_MODE))
//         return false;

//     VCS_SetVelocityMust(gateway, id, vel, &error_code);
//     print_VCS_error(error_code, __FUNCTION__);
//     return !error_code;
// }

bool NAV_Motor::set_velocity_ref(long vel)
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    if ((op_mode != OMD_VELOCITY_MODE) &&
        !this->set_operational_mode(OMD_PROFILE_VELOCITY_MODE))
        return false;

    VCS_MoveWithVelocity(gateway, id, vel, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return !error_code;
}

int NAV_Motor::get_velocity_is()
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int vel;
    VCS_GetVelocityIs(gateway, id, &vel, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return vel;
}

int NAV_Motor::get_current_is()
{
    CONNECTION_CHECK;

    unsigned int error_code = 0;
    int cur;
    VCS_GetCurrentIsEx(gateway, id, &cur, &error_code);
    print_VCS_error(error_code, __FUNCTION__);
    return cur;
}

int NAV_Motor::get_efficiency()
{
    CONNECTION_CHECK;

    float vel = (float)this->get_velocity_is();
    float cur = (float)this->get_current_is();

    return (int)(100. / (1. + fabs((WINDING_RES * cur) / (SPEED_CONSTANT * vel))));
}
