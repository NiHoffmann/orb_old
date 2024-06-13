#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"

#include "port.h"
#include "portenums.h"

const mp_obj_type_t orb_port_type;

//our orb.led function table
//this registers the led.value() function with out led
static const mp_rom_map_elem_t orb_port_local_dict_table[] = {
    //led constants
    { MP_ROM_QSTR(MP_QSTR_M1), MP_ROM_INT(PORT_M1) },
    { MP_ROM_QSTR(MP_QSTR_M2), MP_ROM_INT(PORT_M2) },
    { MP_ROM_QSTR(MP_QSTR_M3), MP_ROM_INT(PORT_M3) },
    { MP_ROM_QSTR(MP_QSTR_M4), MP_ROM_INT(PORT_M4) },
    { MP_ROM_QSTR(MP_QSTR_S1), MP_ROM_INT(PORT_S1) },
    { MP_ROM_QSTR(MP_QSTR_S2), MP_ROM_INT(PORT_S2) },
    { MP_ROM_QSTR(MP_QSTR_S3), MP_ROM_INT(PORT_S3) },
    { MP_ROM_QSTR(MP_QSTR_S4), MP_ROM_INT(PORT_S4) },
};
static MP_DEFINE_CONST_DICT(orb_port_local, orb_port_local_dict_table);

//this defines our led class, use this define to add to orb module table
 MP_DEFINE_CONST_OBJ_TYPE(
    orb_port_type,
    MP_QSTR_Port,
    MP_TYPE_FLAG_NONE,
    locals_dict, &orb_port_local
    );
