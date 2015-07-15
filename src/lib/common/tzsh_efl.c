#include "tzsh_private.h"

#ifdef HAVE_ECORE_WAYLAND
#include <Ecore_Wayland.h>
#endif

tzsh_h
tzsh_efl_create(void)
{
   struct wl_display *display = NULL;

#ifdef HAVE_ECORE_WAYLAND
   if (!ecore_wl_init(NULL))
     {
        ERR("");
        return NULL;
     }

   display = ecore_wl_display_get();
   if (!display)
     {
        ERR("");
        ecore_wl_shutdown();
        return NULL;;
     }
#endif

   // If HAVE_ECORE_WAYLAND is not defined, pass NULL
   return tzsh_create_internal(display);
}

void
tzsh_efl_destroy(tzsh_h tzsh)
{
   if (!tzsh)
     return;

#ifdef HAVE_ECORE_WAYLAND
   ecore_wl_shutdown();
#endif

   tzsh_destroy_internal(tzsh);
}
