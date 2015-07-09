#ifndef _TZSH_VOLUME_SERVICE_H_
#define _TZSH_VOLUME_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <tzsh.h>
#include <tzsh_region.h>

/**
 * @brief Handle for the tizen volume service.
 * @since_tizen 2.4
 */
typedef struct _tzsh_service_s * tzsh_volume_service_h;

/**
 * @internal
 * @brief Creates a new volume service handle.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the volume.
 * @return #tzsh_volume_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_volume_service_destroy()
 */
tzsh_volume_service_h tzsh_volume_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given volume service handle.
 * @since_tizen 2.4
 * @param[in] service The volume service handler to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_volume_service_create()
 */
int tzsh_volume_service_destroy(tzsh_volume_service_h service);

/**
 * @internal
 * @brief Sets the content region of the volume service handle.
 * @since_tizen 2.4
 * @param[in] service  The volume service handler
 * @param[in] angle The angle setting the region
 * @param[in] region The region of the content
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_volume_service_content_region_set(tzsh_volume_service_h service, unsigned int angle, tzsh_region_h region);

#ifdef  __cplusplus
}
#endif

#endif
