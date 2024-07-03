#include "orb/devices/devices.h"
#include "orb/devices/led/led.h"

// Ensure sensor_initialised is defined
MP_REGISTER_ROOT_POINTER(int devices_initialised);

// Initialization function for sensor module
static mp_obj_t devices___init__(void) {
    if (!MP_STATE_VM(devices_initialised)) {
        // Initialize sensor only once
        MP_STATE_VM(devices_initialised) = true;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(devices___init___obj, devices___init__);

// Sensor module globals including the submodule
static const mp_rom_map_elem_t orb_devices_global_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_orb_dot_devices) },
    { MP_ROM_QSTR(MP_QSTR___init__), MP_ROM_PTR(&devices___init___obj) },
    { MP_ROM_QSTR(MP_QSTR_led), MP_ROM_PTR(&orb_led_type) },
};
static MP_DEFINE_CONST_DICT(orb_devices_global, orb_devices_global_dict_table);

// Define the sensor module
const mp_obj_module_t orb_module_devices = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_devices_global,
};

