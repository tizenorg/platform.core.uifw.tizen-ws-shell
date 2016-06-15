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
 * @brief Handle for state changed event for the quickpanel.
 * @since_tizen 3.0
 */
typedef struct _tzsh_quickpanel_event_s *tzsh_quickpanel_event_h;

/**
 * @brief Enumeration for scrollable state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_SCROLLABLE_STATE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_SCROLLABLE_STATE_SET = 0x1, /**< Scrollable state. */
   TZSH_QUICKPANEL_SCROLLABLE_STATE_UNSET = 0x2, /**< Not scrollable state. */
   TZSH_QUICKPANEL_SCROLLABLE_STATE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel scrollable state. */
} tzsh_quickpanel_scrollable_state_e;

/**
 * @brief Enumeration for visible state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_VISIBLE_STATE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_VISIBLE_STATE_SHOW = 0x1, /**< Show state. */
   TZSH_QUICKPANEL_VISIBLE_STATE_HIDE = 0x2, /**< Hide state. */
   TZSH_QUICKPANEL_VISIBLE_STATE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel visible state. */
} tzsh_quickpanel_visible_state_e;

/**
 * @brief Enumeration for orientation state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_ORIENTATION_STATE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_ORIENTATION_STATE_0 = 0x1, /**< 0 */
   TZSH_QUICKPANEL_ORIENTATION_STATE_90 = 0x2, /**< 90 */
   TZSH_QUICKPANEL_ORIENTATION_STATE_180 = 0x4, /**< 180 */
   TZSH_QUICKPANEL_ORIENTATION_STATE_270 = 0x8, /**< 270 */
   TZSH_QUICKPANEL_ORIENTATION_STATE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel visible state. */
} tzsh_quickpanel_orientation_state_e;

/**
 * @brief Handle for the callback function of quickpanel.
 * @since_tizen 3.0
 */
typedef void (*tzsh_quickpanel_cb)(void *data, tzsh_quickpanel_h quickpanel, tzsh_quickpanel_h event);

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
 * @brief Requests to show the quickpanel service window if it is currently scrollable.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_show(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests to hide the quickpanel service window if it is currently scrollable.
 * @since_tizen 2.4
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_hide(tzsh_quickpanel_h quickpanel);

/**
 * @brief Gets the visible state of the quickpanel.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[out] visible The visible state of the quickpanel service window
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_visible_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_visible_state_e *visible);

/**
 * @deprecated Deprecated since 3.0. Renamed to tzsh_quickpanel_scrollable_set().
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
 * @deprecated Deprecated since 3.0. Renamed to tzsh_quickpanel_scrollable_unset().
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

/**
 * @brief Requests to be scrollable the quickpanel service window.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_scrollable_set(tzsh_quickpanel_h quickpanel);

/**
 * @brief Requests to be not scrollable the quickpanel service window.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_scrollable_unset(tzsh_quickpanel_h quickpanel);

/**
 * @brief Checks if the quickpanel service window is scrollable.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[out] scrollable The scrollable state of the quickpanel service window
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_scrollable_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_scrollable_state_e *scrollable);

/**
 * @brief Gets the orientation of the quickpanel.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[out] orientation The orientation of the quickpanel service window
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_quickpanel_orientation_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_orientation_state_e *orientation);

/**
 * @brief Sets the callback function to be called when the quickpanel state is changed.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[in] cb_func The callback function to be called
 * @param[in] data The data associated to the callback function
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_state_change_cb_set(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_cb cb_func, void *data);

/**
 * @brief Removes the registered event callback function.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_state_change_cb_unset(tzsh_quickpanel_h quickpanel);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
