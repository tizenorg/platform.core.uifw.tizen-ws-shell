#ifndef _TZSH_PRIVATE_H_
#define _TZSH_PRIVATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tzsh_protocol.h"

#include "tzsh.h"
#include "tzsh_region.h"
#include "tzsh_service.h"

/* GCC visibility */
#if defined(__GNUC__) && __GNUC__ >= 4
#define TZSH_EXPORT __attribute__ ((visibility("default")))
#else
#define TZSH_EXPORT
#endif

#ifdef DEBUG_MODE
# define ERR(f, x...) fprintf(stderr, "ERR: [%30.30s|%04d] " f "\n", __func__, __LINE__, ##x)
# define INF(f, x...) fprintf(stdout, "INF: [%30.30s|%04d] " f "\n", __func__, __LINE__, ##x)
#else
# define ERR(f, x...) NULL
# define INF(f, x...) NULL
#endif

#define TZSH_ERR_SUCCESS   set_last_result(TZSH_ERROR_NONE)

#define TZSH_ERR_SUCCESS_RET                    \
do {                                            \
     TZSH_ERR_SUCCESS;                          \
     return TZSH_ERROR_NONE;                    \
} while(0)

#define TZSH_ERR_SET(err_code)                  \
do {                                            \
      ERR("error code: %d", err_code);          \
      set_last_result(err_code);            \
} while(0)

#define TZSH_ERR_RET(err_code)                  \
do {                                            \
      TZSH_ERR_SET(err_code);                   \
      return err_code;                          \
} while(0)

typedef void (*tzsh_destroy_cb)(void *data);

struct tizen_ws_shell   *tzsh_tws_get(tzsh_h tzsh);
struct tws_region       *tzsh_tws_region_get(tzsh_region_h region);

tzsh_h tzsh_create_internal(struct wl_display *display);
void   tzsh_destroy_internal(tzsh_h tzsh);
void   tzsh_flush(tzsh_h tzsh);
bool   tzsh_service_exist_check(tzsh_h tzsh, const char *name);
void   tzsh_destroy_callback_add(tzsh_h tzsh, tzsh_destroy_cb func, void *data);
void   tzsh_destroy_callback_remove(tzsh_h tzsh, tzsh_destroy_cb func, void *data);

#define TZSH_USER_BASE_DATA(name)                                          \
   struct _tzsh_##name##_s                                                      \
   {                                                                       \
      tzsh_h tzsh;                                                         \
      tzsh_window win;                                                     \
      struct tws_##name *res;                                              \
   };

#define TZSH_USER_BASE_IMPL(name)                                          \
   static void                                                             \
   _tzsh_##name##_destroy_internal(tzsh_##name##_h name)                   \
   {                                                                       \
      if (!name)                                                           \
        return;                                                            \
      tws_##name##_release((name)->res);                                   \
      tzsh_flush((name)->tzsh);                                            \
      free(name);                                                          \
   }                                                                       \
                                                                           \
   static void                                                             \
   _tzsh_##name##_cb_destroy(void *data)                                   \
   {                                                                       \
      tzsh_##name##_h name = data;                                         \
      _tzsh_##name##_destroy_internal(name);                               \
   }                                                                       \
                                                                           \
   TZSH_EXPORT tzsh_##name##_h                                             \
   tzsh_##name##_create(tzsh_h tzsh, tzsh_window win)                      \
   {                                                                       \
      tzsh_##name##_h name;                                                \
      struct tizen_ws_shell *tws;                                          \
      if (!tzsh)                                                           \
        {                                                                  \
           TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      tws = tzsh_tws_get(tzsh);                                            \
      if (!tws)                                                            \
        {                                                                  \
           TZSH_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);                         \
           return NULL;                                                    \
        }                                                                  \
      if (!tzsh_service_exist_check(tzsh, #name))                          \
        {                                                                  \
           ERR("*%s* service is NOT EXISTED", #name);                      \
           TZSH_ERR_SET(TZSH_ERROR_SERVICE_NOT_EXSITED);                   \
           return NULL;                                                    \
        }                                                                  \
      name = calloc(1, sizeof(struct _tzsh_##name##_s));                   \
      if (!name)                                                           \
        {                                                                  \
           TZSH_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);                         \
           return NULL;                                                    \
        }                                                                  \
      (name)->res = tizen_ws_shell_##name##_get(tws, win);                 \
      (name)->win = win;                                                   \
      (name)->tzsh = tzsh;                                                 \
      tzsh_destroy_callback_add(tzsh, _tzsh_##name##_cb_destroy, name);    \
      tzsh_flush(tzsh);                                                    \
      TZSH_ERR_SUCCESS;                                                    \
      return name;                                                         \
   }                                                                       \
                                                                           \
   TZSH_EXPORT int                                                         \
   tzsh_##name##_destroy(tzsh_##name##_h name)                             \
   {                                                                       \
      if (!name)                                                           \
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);                        \
      tzsh_destroy_callback_remove((name)->tzsh,                           \
                                  _tzsh_##name##_cb_destroy, name);        \
      _tzsh_##name##_destroy_internal(name);                               \
      TZSH_ERR_SUCCESS_RET;                                                \
   }

#define TZSH_SERVICE_BASE_DATA(name)

#define TZSH_SERVICE_BASE_IMPL(name)                                       \
   TZSH_EXPORT tzsh_##name##_service_h                                     \
   tzsh_##name##_service_create(tzsh_h tzsh, tzsh_window win)              \
   {                                                                       \
      if (!tzsh)                                                           \
        {                                                                  \
           TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      if (!win)                                                            \
        {                                                                  \
           TZSH_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      TZSH_ERR_SUCCESS;                                                    \
      return tzsh_service_create(tzsh, win, #name);                        \
   }                                                                       \
                                                                           \
   TZSH_EXPORT int                                                         \
   tzsh_##name##_service_destroy(tzsh_##name##_service_h name)             \
   {                                                                       \
      if (!name)                                                           \
        TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);                        \
      tzsh_service_destroy((tzsh_service_h)name);                          \
      TZSH_ERR_SUCCESS_RET;                                                \
   }

#endif
