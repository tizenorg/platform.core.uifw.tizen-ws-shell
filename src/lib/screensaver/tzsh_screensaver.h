#ifndef _TZSH_SCREENSAVER_H_
#define _TZSH_SCREENSAVER_H_

/**
 * @addtogroup TIZEN_WS_SHELL_SCREENSAVER_MODULE
 * @{
 */

#include <tzsh.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen screensaver client.
 * @since_tizen 3.0
 */
typedef struct _tzsh_screensaver_s * tzsh_screensaver_h;

/**
 * @brief Creates the #tzsh_screensaver_h object which handles the screensaver service.
 * @since_tizen 3.0
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window
 * @return #tzsh_screensaver_h object on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_SERVICE_NOT_EXSITED Service not exist
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_screensaver_destroy()
 */
tzsh_screensaver_h tzsh_screensaver_create(tzsh_h tzsh, tzsh_window win);

/**
 * @brief Destroys the given #tzsh_screensaver_h object.
 * @since_tizen 3.0
 * @param[in] screensaver The #tzsh_screensaver_h object to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_screensaver_create()
 */
int tzsh_screensaver_destroy(tzsh_screensaver_h screensaver);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
