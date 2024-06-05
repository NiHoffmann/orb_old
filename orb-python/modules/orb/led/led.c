
#include "py/runtime.h"
#include "py/objstr.h"
#include "led.h"

#if ORB_FIRMWARE == 1
    #include "led/LedWrapper.h"
#endif // ORB_FIRMWARE

const mp_obj_type_t orb_led_type;

//this is our led representation
typedef struct _orb_led_obj_t {
    mp_obj_base_t base;
#if ORB_FIRMWARE == 1
    struct LedWrapper* wrapper;
#endif
} orb_led_obj_t;

enum LEDS {
    LED_POWER = 0,
    LED_1     = 1,
    LED_2     = 2,
};

//when creating a pin instance this is called
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

    if(led_id < 0 || led_id > 2){
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid led id."));
    }
#if ORB_FIRMWARE == 1
    //get pointer from led const array (shared objects for user leds)
    orb_led_obj_t *my_led_ptr =  m_new_obj(orb_led_obj_t);
    my_led_ptr->base.type = type;
    my_led_ptr->wrapper = createLedWrapper(10);

    //TODO MAKE THIS A POINTER TO AN LED OBJECT WITH LED ID
    return MP_OBJ_FROM_PTR(my_led_ptr);
#else
    return NULL;
#endif
    //check if mode is selected
  /*
    if(args[ARG_mode].u_obj != mp_const_none){
        self->value = 255;
    }
  */
}

// pin.value function callback
static mp_obj_t orb_led_value(size_t n_args, const mp_obj_t *args) {

    orb_led_obj_t *self = MP_OBJ_TO_PTR(args[0]);

    mp_arg_check_num(n_args, 0, 1, 2, true);

#if ORB_FIRMWARE == 1
    //access the wrapper here
    if(n_args == 1){
        return MP_OBJ_NEW_SMALL_INT(getValueLedWrapper(self->wrapper));
    }else{
        return MP_OBJ_NEW_SMALL_INT(setValueLedWrapper(self->wrapper, mp_obj_get_int(args[1]) > 0));
    }
#else
    return NULL;
#endif // ORB_FIRMWARE
}
//register pin.value function
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(orb_led_value_obj, 1, 2, orb_led_value);

//our orb.led function table
//this registers the led.value() function with out led
static const mp_rom_map_elem_t orb_led_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&orb_led_value_obj) },
    //led constants
    { MP_ROM_QSTR(MP_QSTR_LED_POWER), MP_ROM_INT(LED_POWER) },
    { MP_ROM_QSTR(MP_QSTR_LED_1), MP_ROM_INT(LED_1) },
    { MP_ROM_QSTR(MP_QSTR_LED_2), MP_ROM_INT(LED_2) },
};
static MP_DEFINE_CONST_DICT(orb_led_local, orb_led_local_dict_table);

//this defines our led class, use this define to add to orb module table
 MP_DEFINE_CONST_OBJ_TYPE(
    orb_led_type,
    MP_QSTR_led,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_led_make_new,
    locals_dict, &orb_led_local
    );
