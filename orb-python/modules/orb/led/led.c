
#include "py/runtime.h"
#include "py/objstr.h"
#include "led.h"

const mp_obj_type_t orb_led_type;

typedef struct _orb_led_obj_t {
    mp_obj_base_t base;
    uint8_t id;
    uint8_t value;
} orb_led_obj_t;

static orb_led_obj_t orb_led_obj[] = {
    {{&orb_led_type}, .id = 0, .value = 0},
    {{&orb_led_type}, .id = 1, .value = 0},
    {{&orb_led_type}, .id = 2, .value = 0},
};

static void mp_orb_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    const orb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "LED(%u)", self->id);
}

// for make_new
static mp_obj_t mp_orb_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    //allowed args, just id´atm
    enum { ARG_id, ARG_mode };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_id, MP_ARG_OBJ, {.u_obj = MP_OBJ_NEW_SMALL_INT(-1) } },
        { MP_QSTR_mode, MP_ARG_OBJ, {.u_obj = mp_const_none} },
    };

    //args is the array that will hold the parsed args
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    //cast argument to id value
    int led_id =  mp_obj_get_int(args[ARG_id].u_obj);
    //get pointer from led const array (shared objects for user leds)
    orb_led_obj_t *self = &orb_led_obj[led_id];

    //check if mode is selected
    if(args[ARG_mode].u_obj != mp_const_none){
        self->value = 255;
    }
    //TODO MAKE THIS A POINTER TO AN LED OBJECT WITH LED ID
    return MP_OBJ_FROM_PTR(self);
}

// pin.value([value])
static mp_obj_t orb_led_value(size_t n_args, const mp_obj_t *args) {

    orb_led_obj_t *self = args[0];

    mp_arg_check_num(n_args, 0, 1, 2, true);

    if(n_args == 1){
        return MP_OBJ_NEW_SMALL_INT(self->value);
    }else{
        uint8_t new_value = mp_obj_get_int(args[1]);
        return MP_OBJ_NEW_SMALL_INT(self->value = new_value);
    }
}
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(orb_led_value_obj, 1, 2, orb_led_value);


static const mp_rom_map_elem_t orb_led_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&orb_led_value_obj) },
};
static MP_DEFINE_CONST_DICT(orb_led_local, orb_led_local_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    orb_led_type,
    MP_QSTR_led,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_led_make_new,
    print, mp_orb_led_print,
    locals_dict, &orb_led_local
    );


