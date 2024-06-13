#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"

#include "motor.h"
#include "orb/port/portenums.h"

const mp_obj_type_t orb_motor_type;

typedef struct _orb_motor_obj_t {
    mp_obj_base_t base;
} orb_motor_obj_t;

static mp_obj_t mp_orb_motor_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    //allowed args, just id�atm
    enum { ARG_port };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_port, MP_ARG_OBJ, {.u_obj = MP_OBJ_NEW_SMALL_INT(-1) } },
    };

    //args is the array that will hold the parsed args
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    //cast argument to id value
    int motor_id =  mp_obj_get_int(args[ARG_port].u_obj);

    if(motor_id < 0 || motor_id > PORT_M4){
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid Motor Port."));
    }

    orb_motor_obj_t *self =  m_new_obj(orb_motor_obj_t);
    self->base.type = type;

    return MP_OBJ_FROM_PTR(self);
}

static const mp_rom_map_elem_t orb_motor_local_dict_table[] = {

};

static MP_DEFINE_CONST_DICT(orb_motor_local, orb_motor_local_dict_table);

 MP_DEFINE_CONST_OBJ_TYPE(
    orb_motor_type,
    MP_QSTR_Motor,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_motor_make_new,
    locals_dict, &orb_motor_local
    );
