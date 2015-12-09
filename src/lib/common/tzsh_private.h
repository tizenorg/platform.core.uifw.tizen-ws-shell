#ifndef _TZSH_PRIVATE_H_
#define _TZSH_PRIVATE_H_

#include "config.h"
#include "tzsh.h"
#include "tzsh_protect.h"
#include "tzsh_region.h"
#include "tzsh_protocol.h"

struct _tzsh_s
{
   struct wl_display *disp;
   struct wl_registry *registry;
   struct wl_list destroy_cb_list;
   struct wl_list registered_service_list;
   struct tizen_ws_shell *tws;
   void *backend_data;

   tzsh_toolkit_type_e toolkit_type;
   unsigned char disp_owned: 1;
};

tzsh_h         tzsh_create_internal(struct wl_display *display);
void           tzsh_destroy_internal(tzsh_h tzsh);

#ifdef HAVE_ECORE
tzsh_h         tzsh_efl_create(void);
void           tzsh_efl_destroy(tzsh_h tzsh);
#else // !HAVE_ECORE
static inline tzsh_h
tzsh_efl_create(void)
{
   ERR("ERR: this was built without efl");
   return NULL;
}

static inline void
tzsh_efl_destroy(tzsh_h tzsh)
{
}
#endif // HAVE_ECORE

#endif
