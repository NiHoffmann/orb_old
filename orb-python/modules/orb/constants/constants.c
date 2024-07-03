#include "constants.h"
#include "orb/constants/port/port.h"

// Ensure sensor_initialised is defined
MP_REGISTER_ROOT_POINTER(int orb_constants_initialised);

// Initialization function for sensor module
static mp_obj_t orb_constants___init__(void) {
    if (!MP_STATE_VM(orb_constants_initialised)) {
        // Initialize sensor only once
        MP_STATE_VM(orb_constants_initialised) = true;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(orb_constants___init___obj, orb_constants___init__);

// Sensor module globals including the submodule
static const mp_rom_map_elem_t orb_constants_global_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_orb_dot_constants) },
    { MP_ROM_QSTR(MP_QSTR___init__), MP_ROM_PTR(&orb_constants___init___obj) },
    { MP_ROM_QSTR(MP_QSTR_port), MP_ROM_PTR(&orb_port_type) },
};
static MP_DEFINE_CONST_DICT(orb_constants_global, orb_constants_global_dict_table);

// Define the sensor module
const mp_obj_module_t orb_module_constants = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_constants_global,
};
