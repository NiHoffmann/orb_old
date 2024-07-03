ORB_MOD_DIR := $(USERMOD_DIR)
SRC_USERMOD_C += $(ORB_MOD_DIR)/orb.c
#constants
SRC_USERMOD_C += $(ORB_MOD_DIR)/constants/constants.c
SRC_USERMOD_C += $(ORB_MOD_DIR)/constants/port/port.c
#devices
SRC_USERMOD_C += $(ORB_MOD_DIR)/devices/devices.c
SRC_USERMOD_C += $(ORB_MOD_DIR)/devices/led/led.c
#motors
SRC_USERMOD_C += $(ORB_MOD_DIR)/motors/motors.c
SRC_USERMOD_C += $(ORB_MOD_DIR)/motors/ev3_motor/ev3_motor.c
#sensors
#SRC_USERMOD_C += $(ORB_MOD_DIR)/sensors/sensors.c