
#include "py/runtime.h"
#include "py/objstr.h"
#include "led.h"

static void mp_orb_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    mp_printf(print, "LED(%u)", 1);
}

// for make_new
static mp_obj_t mp_orb_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    enum { ARG_id };
    //user led allows a single int as arguemnt
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_id, MP_ARG_OBJ, {.u_obj = MP_OBJ_NEW_SMALL_INT(-1) } },
    };

    // parse args
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    int led_id = args[ARG_id].u_obj;

    //TODO MAKE THIS A POINTER TO AN LED OBJECT WITH LED ID
    return MP_OBJ_FROM_PTR(NULL);
}

static const mp_rom_map_elem_t orb_led_local_dict_table[] = {
};
static MP_DEFINE_CONST_DICT(orb_led_local, orb_led_local_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    orb_led_type,
    MP_QSTR_led,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_led_make_new,
    print, mp_orb_led_make_new,
    locals_dict, &orb_led_local
    );


