#ifndef _TZSH_SCREENSAVER_SERVICE_H_
#define _TZSH_SCREENSAVER_SERVICE_H_

/**
 * @addtogroup TIZEN_WS_SHELL_SCREENSAVER_SERVICE_MODULE
 * @{
 */

#include <tzsh.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen screensaver service.
 * @since_tizen 3.0
 */
typedef struct _tzsh_service_s * tzsh_screensaver_service_h;

/**
 * @internal
 * @brief Creates a new screensaver service handle.
 * @since_tizen 3.0
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the screensaver.
 * @return #tzsh_screensaver_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_screensaver_service_destroy()
 */
tzsh_screensaver_service_h tzsh_screensaver_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given screensaver service handle.
 * @since_tizen 3.0
 * @param[in] service The screensaver service handle to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_screensaver_service_create()
 */
int tzsh_screensaver_service_destroy(tzsh_screensaver_service_h service);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
