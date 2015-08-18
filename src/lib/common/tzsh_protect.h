#ifndef _TZSH_PROTECT_H_
#define _TZSH_PROTECT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dlog.h"
#undef LOG_TAG
#define LOG_TAG "TZSH"

#include "tzsh.h"
#include "tzsh_region.h"
#include "tzsh_protocol.h"

/* GCC visibility */
#if defined(__GNUC__) && __GNUC__ >= 4
#define TZSH_EXPORT __attribute__ ((visibility("default")))
#else
#define TZSH_EXPORT
#endif

#define ERR(f, x...) LOGE("ERR: " f , ##x)
#define INF(f, x...) LOGI("INF: " f , ##x)

#define TZSH_LAST_ERR_SET(err_code) set_last_result(err_code)
#define TZSH_ERR_SUCCESS_SET   TZSH_LAST_ERR_SET(TZSH_ERROR_NONE)
#define TZSH_ERR_SUCCESS_RET                    \
do {                                            \
     TZSH_ERR_SUCCESS_SET;                      \
     return TZSH_ERROR_NONE;                    \
} while(0)
#define TZSH_ERR_RET(err_code)                  \
do {                                            \
      ERR("error code: %d", err_code);          \
      TZSH_LAST_ERR_SET(err_code);              \
      return err_code;                          \
} while(0)

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
           TZSH_LAST_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      tws = tzsh_tws_get(tzsh);                                            \
      if (!tws)                                                            \
        {                                                                  \
           TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);                         \
           return NULL;                                                    \
        }                                                                  \
      if (!tzsh_service_exist_check(tzsh, #name))                          \
        {                                                                  \
           ERR("*%s* service is NOT EXISTED", #name);                      \
           TZSH_LAST_ERR_SET(TZSH_ERROR_SERVICE_NOT_EXSITED);                   \
           return NULL;                                                    \
        }                                                                  \
      name = calloc(1, sizeof(struct _tzsh_##name##_s));                   \
      if (!name)                                                           \
        {                                                                  \
           TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);                         \
           return NULL;                                                    \
        }                                                                  \
      (name)->res = tizen_ws_shell_##name##_get(tws, win);                 \
      (name)->win = win;                                                   \
      (name)->tzsh = tzsh;                                                 \
      tzsh_destroy_callback_add(tzsh, _tzsh_##name##_cb_destroy, name);    \
      tzsh_flush(tzsh);                                                    \
      TZSH_ERR_SUCCESS_SET;                                                \
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

#define TZSH_SERVICE_BASE_IMPL(name)                                       \
   TZSH_EXPORT tzsh_##name##_service_h                                     \
   tzsh_##name##_service_create(tzsh_h tzsh, tzsh_window win)              \
   {                                                                       \
      if (!tzsh)                                                           \
        {                                                                  \
           TZSH_LAST_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      if (!win)                                                            \
        {                                                                  \
           TZSH_LAST_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);                     \
           return NULL;                                                    \
        }                                                                  \
      TZSH_ERR_SUCCESS_SET;                                                \
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

typedef struct _tzsh_service_s * tzsh_service_h;

typedef void (*tzsh_destroy_cb)(void *data);
typedef void (*tzsh_service_destroy_cb)(void *data);

struct _tzsh_service_s
{
   tzsh_h tzsh;
   tzsh_window window;
   struct tws_service *tws_service;
   struct wl_list destroy_cb_list;
   void *private_data;
};

enum tzsh_service_region_type_e
{
   TZSH_SERVICE_REGION_TYPE_HANDLER = TWS_SERVICE_REGION_TYPE_HANDLER,
   TZSH_SERVICE_REGION_TYPE_CONTENT = TWS_SERVICE_REGION_TYPE_CONTENT
};

struct tizen_ws_shell   *tzsh_tws_get(tzsh_h tzsh);
struct tws_region       *tzsh_tws_region_get(tzsh_region_h region);

int            tzsh_flush(tzsh_h tzsh);
bool           tzsh_service_exist_check(tzsh_h tzsh, const char *name);
void           tzsh_destroy_callback_add(tzsh_h tzsh, tzsh_destroy_cb func, void *data);
void           tzsh_destroy_callback_remove(tzsh_h tzsh, tzsh_destroy_cb func, void *data);
tzsh_service_h tzsh_service_create(tzsh_h tzsh, tzsh_window window, char *name);
void           tzsh_service_destroy(tzsh_service_h service);
int            tzsh_service_region_set(tzsh_service_h service, int type,
                                       unsigned int angle, tzsh_region_h region);
void           tzsh_service_destroy_callback_add(tzsh_service_h service,
                                                 tzsh_service_destroy_cb cb_func,
                                                 void *data);

#endif
