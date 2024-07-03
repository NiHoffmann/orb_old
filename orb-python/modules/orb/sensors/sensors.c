/*#include "py/obj.h"

#include "py/runtime.h"
#include "py/mphal.h"
#include "orb/led/led.h"

#include "orb/sensor/sensor.h"
static mp_obj_t sensor___init__(void) {
    if (!MP_STATE_VM(sensor_initialised)) {
        // __init__ for builtins is called each time the module is imported,
        // so ensure that initialization only happens once.
        MP_STATE_VM(sensor_initialised) = true;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(sensor___init___obj, sensor___init__);

// The "initialised" state is stored on mp_state so that it is cleared on soft reset.
MP_REGISTER_ROOT_POINTER(int sensor_initialised);

//here we register all different sensor types
static const mp_rom_map_elem_t orb_sensor_global_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),            MP_ROM_QSTR(MP_QSTR_sensor)},
    { MP_ROM_QSTR(MP_QSTR___init__), MP_ROM_PTR(&sensor___init___obj) },
    { MP_ROM_QSTR(MP_QSTR_led), MP_ROM_PTR(&orb_led_type) },
};
static MP_DEFINE_CONST_DICT(orb_sensor_global, orb_sensor_global_dict_table);

const mp_obj_module_t orb_module_sensor = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_sensor_global,
};

*/
