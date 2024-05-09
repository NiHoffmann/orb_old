// Check examples/usercmodule for more info about how this works.

#include "py/runtime.h"
#include "py/objstr.h"

#ifndef ORB_FIRMWARE
//link to an empty function here
static mp_obj_t c_hello_hello() {
    return NULL;
}
#else
//link to the cpp function here
static mp_obj_t c_hello_hello() {
    static const MP_DEFINE_STR_OBJ(hello_str, "Hello!");
    return MP_OBJ_FROM_PTR(&hello_str);
}
#endif

static MP_DEFINE_CONST_FUN_OBJ_0(c_hello_hello_obj, c_hello_hello);
	
static mp_obj_t c_hello2_hello() {
    static const MP_DEFINE_STR_OBJ(hello2_str, "Hello again!");
    return MP_OBJ_FROM_PTR(&hello2_str);
}
static MP_DEFINE_CONST_FUN_OBJ_0(c_hello_hello2_obj, c_hello2_hello);


static const mp_rom_map_elem_t c_hello_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_c_hello) },
    { MP_ROM_QSTR(MP_QSTR_hello), MP_ROM_PTR(&c_hello_hello_obj) },
	{ MP_ROM_QSTR(MP_QSTR_hello2), MP_ROM_PTR(&c_hello_hello2_obj) },
};
static MP_DEFINE_CONST_DICT(c_hello_module_globals, c_hello_module_globals_table);


const mp_obj_module_t c_hello_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&c_hello_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_c_hello, c_hello_module);