#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"

#include "orb/motor/motor.h"
#include "orb/port/portenums.h"

#if ORB_FIRMWARE == 1
    #include "motor/MotorWrapper.h"
#endif // ORB_FIRMWARE

const mp_obj_type_t orb_motor_type;

typedef struct _orb_motor_obj_t {
    mp_obj_base_t base;
#if ORB_FIRMWARE == 1
    struct MotorWrapper* wrapper;
#endif
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

#if ORB_FIRMWARE == 1
    self->wrapper = createMotorWrapper(motor_id);
#endif

    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t orb_motor_free(mp_obj_t self_in) {
    orb_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
#if ORB_FIRMWARE == 1
    motorFree(self->wrapper);
#endif
    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_1(orb_motor_free_obj, orb_motor_free);

static mp_obj_t orb_motor_brake(mp_obj_t self_in) {
    orb_motor_obj_t *self = MP_OBJ_TO_PTR(self_in);
#if ORB_FIRMWARE == 1
    motorBrake(self->wrapper);
#endif
    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_1(orb_motor_brake_obj, orb_motor_brake);

// pin.value function callback
static mp_obj_t orb_motor_dc(size_t n_args, const mp_obj_t *args) {
    mp_arg_check_num(n_args, 0, 2, 2, true);
    orb_motor_obj_t *self = MP_OBJ_TO_PTR(args[0]);

#if ORB_FIRMWARE == 1
    int value = mp_obj_get_int(args[1]);
    motorDc(self->wrapper, value);
#endif

    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(orb_motor_dc_obj, 2, 2, orb_motor_dc);

static const mp_rom_map_elem_t orb_motor_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_free), MP_ROM_PTR(&orb_motor_free_obj) },
    { MP_ROM_QSTR(MP_QSTR_brake), MP_ROM_PTR(&orb_motor_brake_obj) },
    { MP_ROM_QSTR(MP_QSTR_dc), MP_ROM_PTR(&orb_motor_dc_obj) },
    //{ MP_ROM_QSTR(MP_QSTR_move_to), MP_ROM_PTR(&orb_motor_move_to_obj) },
};

static MP_DEFINE_CONST_DICT(orb_motor_local, orb_motor_local_dict_table);

 MP_DEFINE_CONST_OBJ_TYPE(
    orb_motor_type,
    MP_QSTR_Motor,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_motor_make_new,
    locals_dict, &orb_motor_local
    );
