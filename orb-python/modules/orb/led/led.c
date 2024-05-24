
#include "py/runtime.h"
#include "py/objstr.h"
#include "led.h"

const mp_obj_type_t orb_led_type;

typedef struct _orb_led_obj_t {
    mp_obj_base_t base;
    uint8_t id;
} orb_led_obj_t;

static const orb_led_obj_t orb_led_obj[] = {
    {{&orb_led_type}, .id = 0},
    {{&orb_led_type}, .id = 1},
    {{&orb_led_type}, .id = 2},
};

static void mp_orb_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    const orb_led_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_printf(print, "LED(%u)", self->id);
}

// for make_new
static mp_obj_t mp_orb_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    //check if only one arg
    mp_arg_check_num(n_args, n_kw, 1, 1, true);

    //cast argument to id value
    int led_id =  mp_obj_get_int(all_args[0]);
    //get pointer from led const array (shared objects for user leds)
    const orb_led_obj_t *self = &orb_led_obj[led_id];

    //TODO MAKE THIS A POINTER TO AN LED OBJECT WITH LED ID
    return MP_OBJ_FROM_PTR(self);
}

static const mp_rom_map_elem_t orb_led_local_dict_table[] = {
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


