#include "main.h"
#include "globals.hpp"

void initialize() {
	lcd::initialize();
	auton_init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	as::kill();
	controller.rumble(".");
	as::call_selected_auton();
	controller.rumble(".");
}

void opcontrol() {
	as::kill();
	while (true) {
		
		delay(CONTROLLER_DELAY);
	}
}
