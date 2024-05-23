/* This file is part of the MicroPython project, http://micropython.org/
 * The MIT License (MIT)
 * Copyright (c) 2022-2023 Damien P. George
 */

// Include common MicroPython embed configuration.
#include <port/mpconfigport_common.h>

// Use the minimal starting configuration (disables all optional features).
#define MICROPY_CONFIG_ROM_LEVEL                (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

// MicroPython configuration.
#define MICROPY_ENABLE_GC                       (1)
#define MICROPY_PY_GC                           (1)
#define MICROPY_FLOAT_IMPL                      (MICROPY_FLOAT_IMPL_FLOAT)
#define MICROPY_FLOAT                           (1)
//enable mpy
#define MICROPY_PERSISTENT_CODE_LOAD            (1)
//disable string execution
#define MICROPY_ENABLE_COMPILER                 (1)

/**
#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_NONE)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_NONE)
#define MICROPY_PY_IO_BYTESIO (0)
#define MICROPY_PY_SYS_MODULES (0)
#define MICROPY_PY_SYS_EXIT (0)
#define MICROPY_PY_SYS_PATH (0)
#define MICROPY_PY_SYS_ARGV (0)
#define MICROPY_PY_ERRNO_ERRORCODE (0)
#define MICROPY_PY_SELECT_SELECT (0)
#define MICROPY_PY_UCTYPES_NATIVE_C_TYPES (0)
#define MICROPY_PY_JSON_SEPARATORS (0)
#define MICROPY_PY_HASHLIB_SHA256 (0)

//builtins
#define MICROPY_PY_BUILTINS_INPUT (0)
#define MICROPY_PY_BUILTINS_HELP (0)
#define MICROPY_PY_BUILTINS_EXECFILE (0)
#define MICROPY_PY_BUILTINS_EVAL_EXEC (0)
#define MICROPY_PY_BUILTINS_COMPILE (0)
#define MICROPY_PY_BUILTINS_NOTIMPLEMENTED (0)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (0)

//not sure if these do anything
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_PY_BUILTINS_COMPLEX (0)
#define MICROPY_PY_GENERATOR_PEND_THROW (0)
#define MICROPY_PY_MATH             (0)
#define MICROPY_PY_FRAMEBUF         (0)
#define MICROPY_PY_USOCKET          (0)
#define MICROPY_PY_NETWORK          (0)
#define MICROPY_PY_STM              (0)
#define MICROPY_PY_PYB_LEGACY       (0)
#define MICROPY_PY_UZLIB            (0)
#define MICROPY_PY_UHEAPQ           (0)
#define MICROPY_PY_UTIMEQ           (0)
#define MICROPY_HAS_FILE_READER     (0)
#define MICROPY_PERSISTENT_CODE_SAVE (0)
**/
