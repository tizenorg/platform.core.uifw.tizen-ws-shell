#ifndef _TZSH_INDICATOR_SERVICE_H_
#define _TZSH_INDICATOR_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <tzsh.h>

/**
 * @brief Handle for the tizen indicator service.
 * @since_tizen 2.4
 */
typedef struct _tzsh_service_s * tzsh_indicator_service_h;

/**
 * @brief Handle for the callback function of indicator service.
 * @since_tizen 2.4
 */
typedef void (*tzsh_indicator_service_cb)(void *data, tzsh_indicator_service_h service, int angle, int opacity);

/**
 * @internal
 * @brief Creates a new indicator service handle.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the indicator.
 * @return #tzsh_indicator_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_indicator_service_destroy()
 */
tzsh_indicator_service_h tzsh_indicator_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given indicator service handle.
 * @since_tizen 2.4
 * @param[in] service The indicator service handle to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_indicator_service_create()
 */
int tzsh_indicator_service_destroy(tzsh_indicator_service_h service);

/**
 * @internal
 * @brief Sets the content region of the indicator service handle.
 * @since_tizen 2.4
 * @param[in] service  The indicator service handle
 * @param[in] angle The angle set the region
 * @param[in] region The region of the content
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_indicator_service_content_region_set(tzsh_indicator_service_h service, unsigned int angle, tzsh_region_h region);

/**
 * @internal
 * @brief Sets the callback function to be called when the indicator property changed.
 * @since_tizen 2.4
 * @param[in] service The indicator service handle
 * @param[in] cb_func The callback function to be called
 * @param[in] data The data associated to the callback function
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_indicator_service_property_change_cb_set(tzsh_indicator_service_h service, tzsh_indicator_service_cb cb_func, void *data);

#ifdef  __cplusplus
}
#endif

#endif
