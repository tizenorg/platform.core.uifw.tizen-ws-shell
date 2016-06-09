#ifndef _TZSH_QUICKPANEL_H_
#define _TZSH_QUICKPANEL_H_

/**
 * @addtogroup TIZEN_WS_SHELL_QUICKPANEL_MODULE
 * @{
 */

#include <tzsh.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen quickpanel client.
 * @since_tizen 2.4
 */
typedef struct _tzsh_quickpanel_s * tzsh_quickpanel_h;

/**
 * @brief Creates the #tzsh_quickpanel_h object which handles the quickpanel service.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window
 * @return #tzsh_quickpanel_h object on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_SERVICE_NOT_EXSITED Service not exist
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_quickpanel_destroy()
 */
tzsh_quickpanel_h tzsh_quickpanel_create(tzsh_h tzsh, tzsh_window win);

/**
 * @brief Destroys the given #tzsh_quickpanel_h object.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_quickpanel_create()
 */
int tzsh_quickpanel_destroy(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests to show the quickpanel service window.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_show(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests to hide the quickpanel service window.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_hide(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests to be able to show or hide the quickpanel service window.
 * @details This API can show or hide the quickpanel service window as long as the window is shown.
 *          This property applies all quickpanel object by default.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_enable(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests not to be able to show the quickpanel service window.
 * @details This API is useful if the application does not need to show the quickpanel service window.
 *          If the application call this API, the quickpanel service window cannot be shown on the screen
 *          as long as the window is shown.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_disable(tzsh_quickpanel_h quickpanel);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
