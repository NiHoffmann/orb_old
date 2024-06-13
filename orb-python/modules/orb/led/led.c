#include "py/obj.h"
#include "py/runtime.h"
#include "py/mphal.h"

#include "led.h"
#include "ledenums.h"

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

//when creating a pin instance this is called
static mp_obj_t mp_orb_led_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    //allowed args, just id�atm
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

    if(led_id < 0 || led_id > LED_2){
        mp_raise_ValueError(MP_ERROR_TEXT("Invalid led id."));
    }
#if ORB_FIRMWARE == 1
    //get pointer from led const array (shared objects for user leds)
    orb_led_obj_t *self =  m_new_obj(orb_led_obj_t);
    self->base.type = type;
    self->wrapper = createLedWrapper(led_id);

    //TODO MAKE THIS A POINTER TO AN LED OBJECT WITH LED ID
    return MP_OBJ_FROM_PTR(self);
#else
    return mp_const_none;
#endif
}

// pin.value function callback
static mp_obj_t orb_led_value(size_t n_args, const mp_obj_t *args) {

    orb_led_obj_t *self = MP_OBJ_TO_PTR(args[0]);

    mp_arg_check_num(n_args, 0, 1, 2, true);
#if ORB_FIRMWARE == 1
    //access the wrapper here
    if(n_args == 1){
        return MP_OBJ_NEW_SMALL_INT(getLedValue(self->wrapper));
    }else{
        int value = mp_obj_get_int(args[1]) > 0;
        setLedValue(self->wrapper, value);

        return MP_OBJ_NEW_SMALL_INT(value);
    }
#else
    return mp_const_none;
#endif // ORB_FIRMWARE
}
//register pin.value function
static MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(orb_led_value_obj, 1, 2, orb_led_value);

static mp_obj_t orb_led_blink(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {
    enum { ARG_interval, ARG_duration };

    // Define the allowed arguments
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_interval, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
        { MP_QSTR_duration, MP_ARG_REQUIRED | MP_ARG_INT, {.u_int = 0} },
    };

    // Parse the arguments
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1  , pos_args + 1 , kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);

    // Retrieve the arguments
    int interval = args[ARG_interval].u_int;
    int duration = args[ARG_duration].u_int;

    orb_led_obj_t *self = MP_OBJ_TO_PTR(pos_args[0]);

    // Retrieve the self object
    //int duration =  mp_obj_get_int(args[ARG_duration].u_obj);

#if ORB_FIRMWARE == 1
    blinkLed(self->wrapper, interval, duration);
#endif
    return MP_OBJ_FROM_PTR(self);
}
static MP_DEFINE_CONST_FUN_OBJ_KW(orb_led_blink_obj, 0, orb_led_blink);


//our orb.led function table
//this registers the led.value() function with out led
static const mp_rom_map_elem_t orb_led_local_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_value), MP_ROM_PTR(&orb_led_value_obj) },
    { MP_ROM_QSTR(MP_QSTR_blink), MP_ROM_PTR(&orb_led_blink_obj) },
    //led constants
    { MP_ROM_QSTR(MP_QSTR_LED_POWER), MP_ROM_INT(LED_POWER) },
    { MP_ROM_QSTR(MP_QSTR_LED_1), MP_ROM_INT(LED_1) },
    { MP_ROM_QSTR(MP_QSTR_LED_2), MP_ROM_INT(LED_2) },
};
static MP_DEFINE_CONST_DICT(orb_led_local, orb_led_local_dict_table);

//this defines our led class, use this define to add to orb module table
 MP_DEFINE_CONST_OBJ_TYPE(
    orb_led_type,
    MP_QSTR_Led,
    MP_TYPE_FLAG_NONE,
    make_new, mp_orb_led_make_new,
    locals_dict, &orb_led_local
    );
