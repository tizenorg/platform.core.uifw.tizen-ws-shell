#include "tzsh_private.h"
#include "tzsh_screensaver.h"

TZSH_USER_BASE_DATA(screensaver)

static void
_tzsh_screensaver_destroy_internal(tzsh_screensaver_h scrsaver)
{
   if (!scrsaver) return;

   tws_screensaver_release((scrsaver)->res);
   tzsh_flush((scrsaver)->tzsh);
   free(scrsaver);
}

static void
_tzsh_screensaver_cb_destroy(void *data)
{
   tzsh_screensaver_h scrsaver = data;
   _tzsh_screensaver_destroy_internal(scrsaver);
}

TZSH_EXPORT tzsh_screensaver_h
tzsh_screensaver_create(tzsh_h tzsh, tzsh_window win)
{
   tzsh_screensaver_h scrsaver;
   struct tizen_ws_shell *tws;

   if (!tzsh)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_INVALID_PARAMETER);
        return NULL;
     }

   tws = tzsh_tws_get(tzsh);
   if (!tws)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   scrsaver = calloc(1, sizeof(struct _tzsh_screensaver_s));
   if (!scrsaver)
     {
        TZSH_LAST_ERR_SET(TZSH_ERROR_OUT_OF_MEMORY);
        return NULL;
     }

   scrsaver->res = tizen_ws_shell_screensaver_get(tws, win);
   scrsaver->win = win;
   scrsaver->tzsh = tzsh;
   tzsh_destroy_callback_add(tzsh, _tzsh_screensaver_cb_destroy, scrsaver);
   tzsh_flush(tzsh);
   TZSH_ERR_SUCCESS_SET;

   return scrsaver;
}

TZSH_EXPORT int
tzsh_screensaver_destroy(tzsh_screensaver_h scrsaver)
{
   if (!scrsaver)
     TZSH_ERR_RET(TZSH_ERROR_INVALID_PARAMETER);
   tzsh_destroy_callback_remove((scrsaver)->tzsh,
                                _tzsh_screensaver_cb_destroy, scrsaver);
   _tzsh_screensaver_destroy_internal(scrsaver);
   TZSH_ERR_SUCCESS_RET;
}
