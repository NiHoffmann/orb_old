// Include MicroPython API.
#include "py/runtime.h"
#include "led/led.h"
#include "port/port.h"
#include "motor/motor.h"

static mp_obj_t orb___init__(void) {
    if (!MP_STATE_VM(orb_initialised)) {
        // __init__ for builtins is called each time the module is imported,
        //   so ensure that initialisation only happens once.
        MP_STATE_VM(orb_initialised) = true;
    }
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_0(orb___init___obj, orb___init__);

// The "initialised" state is stored on mp_state so that it is cleared on soft
// reset.
MP_REGISTER_ROOT_POINTER(int orb_initialised);

// Define all attributes of the top-level package (orb).
static const mp_rom_map_elem_t orb_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_orb) },
    { MP_ROM_QSTR(MP_QSTR___init__), MP_ROM_PTR(&orb___init___obj) },
    //register orb.led class, this makes led callable and you can instantiate a led variable
    { MP_ROM_QSTR(MP_QSTR_Led), MP_ROM_PTR(&orb_led_type) },
    { MP_ROM_QSTR(MP_QSTR_Port), MP_ROM_PTR(&orb_port_type) },
    { MP_ROM_QSTR(MP_QSTR_Motor), MP_ROM_PTR(&orb_motor_type) },
};
static MP_DEFINE_CONST_DICT(orb_globals, orb_globals_table);

// Define orb module object.
const mp_obj_module_t orb_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_globals,
};

// Register the module to make it available in Python.
// Note: subpackages should not be registered with MP_REGISTER_MODULE.
//instead they are added to the orb_globals table
MP_REGISTER_MODULE(MP_QSTR_orb, orb_module);
