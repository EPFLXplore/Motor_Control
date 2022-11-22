#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <iostream>
#include <math.h>

#include "EposCmd.h"

enum ControlMode {POSISTION, PROFILE_POSITION, VELOCITY, PROFILE_VELOCITY,
                    CURRENT};

class Motor {
private :
    void*           gateway;
    unsigned short  id;

    ControlMode     control_mode_;

    unsigned int error_code;

// Profil moteur
    bool is_ppm_set = 0;
    bool is_pvm_set = 0;


    /*unsigned int max_pos_;
    unsigned int min_pos_;
    bool pos_limit_;*/
 
    unsigned int max_speed_;
    bool speed_limit_;

    unsigned int max_accel_;
    unsigned int max_decel_;
    bool accel_limit_;


// intern error managment
    bool error_test(void); // all that error related (to se later)


// intern fonction
/* set_op_mode
* brief :  set the operational mode of the controller (position / velocity, etc)
*/
    bool set_op_mode(ControlMode control_mode);


public :
    /* Motor
        * brief :  class of objects to represent a NAV motor
        * param    KeyHandle   handle to the USB gateway
        * param    node_id     CAN Node ID of the controller
        * param    exp_type    expected motor type (0 for no expected type)
        */
    Motor(void* KeyHandle, unsigned short node_id, ControlMode mode,
        unsigned int max_speed, unsigned int max_accel, unsigned int max_decel);
    Motor(void* KeyHandle, unsigned short node_id, ControlMode mode,
        unsigned int max_accel, unsigned int max_decel);
    Motor(void* KeyHandle, unsigned short node_id, ControlMode mode);
    
// getter/setter simple

    /* get_id
        * brief :  return the CAN id of the node
        */
    unsigned short get_id();

    /* get_id
        * brief :  return wheather the node is connected
        */
    bool connected();

    /* disconnect
        * brief :  manually disconnect a motor
        */
    void disconnect();
    
    bool set_pos_limit(unsigned int min_pos, unsigned int max_pos);
    bool get_pos_limit(unsigned int &min_pos, unsigned int &max_pos);
    
    bool set_speed_limit(unsigned int max_speed);
    bool get_speed_limit(unsigned int &max_speed);
    
    bool set_accel_limit(unsigned int max_accel, unsigned int max_decel);
    bool get_accel_limit(unsigned int &max_accel, unsigned int &max_decel);
    
// initialisation des mode

bool init_pvm_mode(unsigned int max_accel, unsigned int max_decel);

bool init_ppm_mode(unsigned int max_speed, unsigned int max_accel,
                    unsigned int max_decel);





    /* set_output_state
        * brief :  set the output state to active / inactive
        */
    bool set_output_state(bool output_active);

    /* is_faulty
        * brief :  check if the device is currently in a fault state
        * param :  verbose     ouput the faults onto the terminal
        * return : in_fault    if the device is faulty
        */
    bool is_faulty(bool verbose);

    bool clear_fault();

    void set_calibrated(bool calibrated);
    bool calibrated();

    /* set_position_ref
        * brief :  set the position reference for the motor to track
        *          if the motor is not yet in the correct mode, this function
        *          automatically sets the controller into the right mode
        */
    bool set_position_ref(long pos);

    /* reset_position_counter
        * brief :  reset the internal position reference
        */
    bool reset_position_counter();

    /* get_position_is
        * brief :  get the current position
        */
    int  get_position_is();

    /* set_velocity_ref
        * brief :  set the position reference for the motor to track
        *          if the motor is not yet in the correct mode, this function
        *          automatically sets the controller into the right mode
        */
    bool set_velocity_ref(long vel);

    /* get_velocity_is
        * brief :  get the current velocity
        */
    int  get_velocity_is();

    /* get_current_is
        * brief :  get the current current in [mA]
        */
    int get_current_is();

    /* get_efficiency
        * brief :  get the current efficiency in %
        */
    int  get_efficiency();

};

/* open_gateway
 * brief :  open a gateway through which to adress a maxon CANopen bus
 */
void* open_gateway(void);

/* close_gateway
 * brief :  safely close a gateway which was used to adress a maxon CANopen bus
 */
void  close_gateway(void* gateway);


#endif
