#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <wayland-server.h>

#include "tzsh-protocol.h"

struct daemon
{
   struct wl_display *wl_display;
};

struct daemon *d = NULL;

static void
_tizen_ws_shell_cb_destroy(struct wl_client *client, struct wl_resource *resource)
{
   wl_resource_destroy(resource);
}

static void
_service_cb_destroy(struct wl_client *client,
                    struct wl_resource *resource)
{
   wl_resource_destroy(resource);
}

static void
_indicator_service_cb_destroy(struct wl_client *client,
                              struct wl_resource *resource)
{
   wl_resource_destroy(resource);
}

static const struct tws_service_indicator_interface _indicator_service_implementation = {
     _indicator_service_cb_destroy
};

static void
_service_cb_indicator_get(struct wl_client *client,
                          struct wl_resource *resource,
                          uint32_t id)
{
   struct wl_resource *res;

   res = wl_resource_create(client, &tws_service_indicator_interface, 1, id);
   if (!res)
     {
        wl_client_post_no_memory(client);
        assert(0 && "Out of memory");
     }

   wl_resource_set_implementation(res, &_indicator_service_implementation, NULL, NULL);

   tws_service_indicator_send_property_change(res, 90, 1);
}

static const struct tws_service_interface _service_implementation = {
     _service_cb_destroy,
     NULL,
     _service_cb_indicator_get,
     NULL
};

static void
_tizen_ws_shell_cb_service_create(struct wl_client *client, struct wl_resource *resource, uint32_t id, uint32_t win, const char *name)
{
   struct wl_resource *res;

   res = wl_resource_create(client, &tws_service_interface, 1, id);
   if (!res)
     {
        wl_client_post_no_memory(client);
        assert(0 && "Out of memory");
     }

   wl_resource_set_implementation(res, &_service_implementation, NULL, NULL);
}

static void
_tizen_ws_shell_cb_region_create(struct wl_client *client, struct wl_resource *resource, uint32_t id)
{

}

static void
_tizen_ws_shell_cb_quickpanel_get(struct wl_client *client, struct wl_resource *resource, uint32_t id, uint32_t win)
{

}

static const struct tizen_ws_shell_interface _tizen_ws_shell_implementation = {
     _tizen_ws_shell_cb_destroy,
     _tizen_ws_shell_cb_service_create,
     _tizen_ws_shell_cb_region_create,
     _tizen_ws_shell_cb_quickpanel_get
};

static void
_tizen_ws_shell_cb_bind(struct wl_client *client, void *data, uint32_t ver, uint32_t id)
{
   struct wl_resource *res;

   res = wl_resource_create(client, &tizen_ws_shell_interface, ver, id);
   if (!res)
     {
        wl_client_post_no_memory(client);
        assert(0 && "Out of memory");
     }

   wl_resource_set_implementation(res, &_tizen_ws_shell_implementation, data, NULL);

   /* dummy service */
   tizen_ws_shell_send_service_register(res, "quickpanel");
   tizen_ws_shell_send_service_register(res, "volume");
   tizen_ws_shell_send_service_register(res, "lockscreen");
   tizen_ws_shell_send_service_register(res, "call");
}

void
daemon_run(void)
{
   assert(d && "daemon_run() called without daemon_create()");

   wl_display_run(d->wl_display);

   wl_display_destroy(d->wl_display);
   free(d);
   d = NULL;
}

void
daemon_create(void)
{
   int stat;
   struct wl_global *g;

   d = calloc(1, sizeof *d);
   assert(d && "Out of memory");

   d->wl_display = wl_display_create();
   assert(d->wl_display && "Creating display failed");

   stat = wl_display_add_socket(d->wl_display, NULL);
   assert(stat == 0 && "Failed adding socket");

   g = wl_global_create(d->wl_display, &tizen_ws_shell_interface,
                                1, d, _tizen_ws_shell_cb_bind);
   assert(g && "Creating test global failed");
}
