#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <wayland-server.h>

#include "tzsh-protocol.h"

struct daemon
{
   struct wl_display *wl_display;
   struct wl_global *global;
};

struct daemon *d = NULL;

static void
_tizen_ws_shell_cb_destroy(struct wl_client *client, struct wl_resource *resource)
{
   (void)client;
   (void)resource;
}

static void
_tizen_ws_shell_cb_service_create(struct wl_client *client, struct wl_resource *resource, uint32_t id, uint32_t win, char *name)
{

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
   exit(EXIT_SUCCESS);
}

void
daemon_create(void)
{
   struct wl_global *g;
   int stat;

   d = calloc(1, sizeof *d);
   assert(d && "Out of memory");

   d->wl_display = wl_display_create();
   assert(d->wl_display && "Creating display failed");

   stat = wl_display_add_socket(d->wl_display, NULL);
   assert(stat == 0 && "Failed adding socket");

   d->global = wl_global_create(d->wl_display, &tizen_ws_shell_interface,
                                1, d, _tizen_ws_shell_cb_bind);
   assert(d->global && "Creating test global failed");
}
