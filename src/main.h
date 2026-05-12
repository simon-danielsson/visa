#ifndef MAIN_H
#define MAIN_H

// libraries ------------------------------------------------------------------

#include "./libs/ana.h"

// standard libraries ---------------------------------------------------------

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// semantics ------------------------------------------------------------------

#define f_inline __attribute((always_inline)) inline

typedef size_t usize;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

// suppress warnings ----------------------------------------------------------

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#pragma clang diagnostic ignored "-Wunused-function"
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

// environment variables ------------------------------------------------------

#ifndef ENV_NAME // project name
#define ENV_NAME "UNDEFINED"
#endif
#ifndef ENV_AUTHOR // author of this project
#define ENV_AUTHOR "UNDEFINED"
#endif
#ifndef ENV_CONTACT // contact info to author
#define ENV_CONTACT "UNDEFINED"
#endif
#ifndef ENV_GITHASH // git hash
#define ENV_GITHASH "UNDEFINED"
#endif
#ifndef ENV_GITTAG // git release version
#define ENV_GITTAG "UNDEFINED"
#endif
#ifndef ENV_REPO // link to git repo
#define ENV_REPO "UNDEFINED"
#endif

#endif
