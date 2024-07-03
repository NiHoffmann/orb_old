#include "motors.h"
#include "orb/motors/ev3_motor/ev3_motor.h"


// Ensure motors_initialised is defined
MP_REGISTER_ROOT_POINTER(int orb_motors_initialised);

static mp_obj_t orb_motors___init__(void) {
    if (!MP_STATE_VM(orb_motors_initialised)) {
        // Initialize sensor only once
        MP_STATE_VM(orb_motors_initialised) = true;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(orb_motors___init___obj, orb_motors___init__);

// Sensor module globals including the submodule
static const mp_rom_map_elem_t orb_motors_global_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_orb_dot_motors) },
    { MP_ROM_QSTR(MP_QSTR___init__), MP_ROM_PTR(&orb_motors___init___obj) },
    { MP_ROM_QSTR(MP_QSTR_ev3_motor), MP_ROM_PTR(&orb_ev3_motor_type) },
};
static MP_DEFINE_CONST_DICT(orb_motors_global, orb_motors_global_dict_table);

// Define the sensor module
const mp_obj_module_t orb_module_motors = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_motors_global,
};
