#ifndef _TZSH_QUICKPANEL_SERVICE_H_
#define _TZSH_QUICKPANEL_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <tzsh.h>
#include <tzsh_region.h>

/**
 * @brief Handle for the tizen quickpanel service.
 * @since_tizen 2.4
 */
typedef struct _tzsh_service_s * tzsh_quickpanel_service_h;

/**
 * @internal
 * @brief Creates a new quickpanel service handle.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the quickpanel
 * @return #tzsh_quickpanel_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_quickpanel_service_destroy()
 */
tzsh_quickpanel_service_h tzsh_quickpanel_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given quickpanel service handle.
 * @since_tizen 2.4
 * @param[in] service The quickpanel service handle to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_quickpanel_service_create()
 */
int tzsh_quickpanel_service_destroy(tzsh_quickpanel_service_h service);

/**
 * @internal
 * @brief Sets the content region of the quickpanel service handle.
 * @since_tizen 2.4
 * @param[in] service  The quickpanel service handle
 * @param[in] angle The angle setting the region
 * @param[in] region The region of the content
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_service_content_region_set(tzsh_quickpanel_service_h service, unsigned int angle, tzsh_region_h region);

/**
 * @internal
 * @brief Sets the handler region of the quickpanel service handle.
 * @since_tizen 2.4
 * @remark The handler means the region which is scrolled to show or hide the quickpanel window by the user.
 * @param[in] service  The quickpanel service handle
 * @param[in] angle The angle setting the region
 * @param[in] region The region of the handler
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_service_handler_region_set(tzsh_quickpanel_service_h service, unsigned int angle, tzsh_region_h region);

/**
 * @internal
 * @brief Requests to show the quickpanel service window.
 * @since_tizen 2.4
 * @param[in] service  The quickpanel service handle
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_service_show(tzsh_quickpanel_service_h service);

/**
 * @internal
 * @brief Requests to hide the quickpanel service window.
 * @since_tizen 2.4
 * @param[in] service  The quickpanel service handle
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_service_hide(tzsh_quickpanel_service_h service);

#ifdef  __cplusplus
}
#endif

#endif
