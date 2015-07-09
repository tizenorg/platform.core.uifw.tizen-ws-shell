#ifndef _TZSH_SERVICE_H_
#define _TZSH_SERVICE_H_

typedef struct _tzsh_service_s * tzsh_service_h;

enum tzsh_service_region_type_e
{
   TZSH_SERVICE_REGION_TYPE_HANDLER = TWS_SERVICE_REGION_TYPE_HANDLER,
   TZSH_SERVICE_REGION_TYPE_CONTENT = TWS_SERVICE_REGION_TYPE_CONTENT
};

tzsh_service_h tzsh_service_create(tzsh_h tzsh, tzsh_window window, char *name);
void           tzsh_service_destroy(tzsh_service_h service);
int            tzsh_service_region_set(tzsh_service_h service, int type,
                                       unsigned int angle, tzsh_region_h region);

#endif
