#include "Motor.hpp"

unsigned short Motor::get_id(){return id;}

bool Motor::connected(){return is_connected;}

void Motor::disconnect(){is_connected = false;}

void Motor::set_calibrated(bool calibrated){is_calibrated = calibrated;}

bool Motor::calibrated(){return is_calibrated;}

bool Motor::set_pos_limit(unsigned int min_pos, unsigned int max_pos){
    if(min_pos >= max_pos){
        min_pos_ = 0;
        max_pos_ = 0;
        pos_limit_ = false;
        
        return 1;
    }

    min_pos_ = min_pos;
    max_pos_ = max_pos;
    pos_limit_ = true;

    return 0;
}
bool Motor::get_pos_limit(unsigned int &min_pos, unsigned int &max_pos){
    min_pos = min_pos_;
    max_pos = max_pos_;

    return pos_limit_;
}

bool Motor::set_speed_limit(unsigned int max_speed){
    if(max_speed_ <= 0){
        max_speed_ = 0;
        speed_limit_ = false;
        return 1;
    }
    
    max_speed_ = max_speed;
    speed_limit_ = true;
    return 0;
}
bool Motor::get_speed_limit(unsigned int &max_speed){
    max_speed = max_speed_;
    return speed_limit_;
}

bool Motor::set_accel_limit(unsigned int max_accel, unsigned int max_decel){
    if(max_accel <=0 or max_decel <=0){
        speed_limit_ = false;
        max_accel_ = 0;
        max_decel_ = 0;
        return 1;
    }

    speed_limit_ = true;
    max_accel_ = max_accel;
    max_decel_ = max_decel;
    return 0;

}
bool Motor::get_accel_limit(unsigned int &max_accel, unsigned int &max_decel){
    max_accel = max_accel_;
    max_decel = max_decel_;
    return accel_limit_;
}
