#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"

#include "orb/sensor/sensor.h"

const mp_obj_type_t orb_sensor_type;

//here we register all different sensor types
static const mp_rom_map_elem_t orb_sensor_global_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__),            MP_ROM_QSTR(MP_QSTR_orb_dot_sensor)},
};
static MP_DEFINE_CONST_DICT(orb_sensor_global, orb_sensor_global_dict_table);

const mp_obj_module_t orb_module_sensor = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&orb_sensor_global,
};

MP_REGISTER_MODULE(MP_QSTR_orb_dot_sensor, orb_module_sensor);
