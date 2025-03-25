#pragma once

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"

// firebird template
#include "firebird_template/lcd/lcd.h"
#include "firebird_template/auton_selector/as.h"

// QOL
inline auto CCW_COUNTERCLOCKWISE = lemlib::AngularDirection::CCW_COUNTERCLOCKWISE;
inline auto CW_CLOCKWISE = lemlib::AngularDirection::CW_CLOCKWISE;
inline void delay(const uint32_t milliseconds) { pros::delay(milliseconds); }
inline const int CONTROLLER_DELAY = 10;

// bot configuration
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);
inline pros::MotorGroup left_motors({10, -8, -9}, pros::MotorGearset::blue);
inline pros::MotorGroup right_motors({-19, 6, 5}, pros::MotorGearset::blue);
inline pros::Imu imu(15);
/*
inline pros::Rotation vert(-17);
inline pros::Rotation horiz(16);
*/

// Lemlib Configuration
inline float track_width = 11;
inline float wheel_diameter = lemlib::Omniwheel::NEW_275;
inline float rpm = 450.0;
inline float horizontal_drift = 2.0;
/*
inline lemlib::TrackingWheel vert_tracking(&vert, 2, 1.125, 1.0);
inline lemlib::TrackingWheel horiz_tracking(&horiz, 2, -2.75, 1.0);
*/

// drivetrain controller
inline lemlib::Drivetrain
    drivetrain(
        &left_motors,
        &right_motors,
        track_width,
        wheel_diameter,
        rpm, 
        horizontal_drift
    );

// sensors controller
inline lemlib::OdomSensors
    sensors(
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        &imu
    );

// lateral PID controller
inline lemlib::ControllerSettings
    lateral_controller(
        10,  // proportional gain (kP)
        0,   // integral gain (kI)
        3,   // derivative gain (kD)
        3,   // anti windup
        1,   // small error range, in inches
        100, // small error range timeout, in milliseconds
        3,   // large error range, in inches
        500, // large error range timeout, in milliseconds
        20   // maximum acceleration (slew)
    );

// angular PID controllerk
inline lemlib::ControllerSettings
    angular_controller(
        2,   // proportional gain (kP)
        0,   // integral gain (kI)
        10,  // derivative gain (kD)
        3,   // anti windup
        1,   // small error range, in degrees
        100, // small error range timeout, in milliseconds
        3,   // large error range, in degrees
        500, // large error range timeout, in milliseconds
        0    // maximum acceleration (slew)
    );

// chassis controller
inline lemlib::Chassis
    chassis(
        drivetrain,
    lateral_controller,
    angular_controller,
        sensors
    );

// Autons
#include "autons/auton.h"
inline void auton_init() {
    as::c = &chassis;

    as::add_auton(as::Auton("Auton", auton));
    
    as::init();
}