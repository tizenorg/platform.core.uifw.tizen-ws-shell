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
 * @brief Handle for the event handler of quickpanel.
 * @since_tizen 3.0
 */
typedef struct _tzsh_quickpanel_event_handler_s *tzsh_quickpanel_event_handler_h;

/**
 * @brief Handle for the event information handler of quickpanel.
 * @since_tizen 3.0
 */
typedef struct _tzsh_quickpanel_event_info_s *tzsh_quickpanel_event_info_h;

/**
 * @brief Enumeration for event type of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_EVENT_TYPE_UNKNOWN = 0x0, /**< Unknown event type. */
   TZSH_QUICKPANEL_EVENT_TYPE_VISIBILITY = 0x1, /**< Visibility event type. */
   TZSH_QUICKPANEL_EVENT_TYPE_SCROLLABLE = 0x2, /**< Scrollable event type. */
   TZSH_QUICKPANEL_EVENT_TYPE_ORIENTATION = 0x3, /**< Orientation event type. */
   TZSH_QUICKPANEL_EVENT_TYPE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel event type. */
} tzsh_quickpanel_event_type_e;

/**
 * @brief Enumeration for visible state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_STATE_VISIBLE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_STATE_VISIBLE_SHOW = 0x1, /**< Show state. */
   TZSH_QUICKPANEL_STATE_VISIBLE_HIDE = 0x2, /**< Hide state. */
   TZSH_QUICKPANEL_STATE_VISIBLE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel visible state. */
} tzsh_quickpanel_state_visible_e;

/**
 * @brief Enumeration for scrollable state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_STATE_SCROLLABLE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_STATE_SCROLLABLE_SET = 0x1, /**< Scrollable state. */
   TZSH_QUICKPANEL_STATE_SCROLLABLE_UNSET = 0x2, /**< Not scrollable state. */
   TZSH_QUICKPANEL_STATE_SCROLLABLE_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel scrollable state. */
} tzsh_quickpanel_state_scrollable_e;

/**
 * @brief Enumeration for orientation state of quickpanel.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_QUICKPANEL_STATE_ORIENTATION_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_QUICKPANEL_STATE_ORIENTATION_0 = 0x1, /**< 0 */
   TZSH_QUICKPANEL_STATE_ORIENTATION_90 = 0x2, /**< 90 */
   TZSH_QUICKPANEL_STATE_ORIENTATION_180 = 0x3, /**< 180 */
   TZSH_QUICKPANEL_STATE_ORIENTATION_270 = 0x4, /**< 270 */
   TZSH_QUICKPANEL_STATE_ORIENTATION_MAX = 0xFFFFFFFF /**< Maximum value of quickpanel visible state. */
} tzsh_quickpanel_state_orientation_e;

/**
 * @brief The event callback function of quickpanel.
 * @since_tizen 3.0
 * @remarks A callback used by the application to handle events of a specified
 * type. The event_info handle is only valid as long as the callback function
 * is not returned. When the callback is returned, event_info handle is not valid
 * and should not be used.
 */
typedef void (*tzsh_quickpanel_event_cb)(tzsh_quickpanel_event_info_h event_info, void *data);

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
int tzsh_quickpanel_visible_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_state_visible_e *visible);

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
int tzsh_quickpanel_scrollable_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_state_scrollable_e *scrollable);

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
int tzsh_quickpanel_orientation_get(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_state_orientation_e *orientation);

/**
 * @brief Sets the callback function to be called when the quickpanel state is changed.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[out] event_handler The #tzsh_quickpanel_event_handler_h object
 * @param[in] event_type The event type
 * @param[in] callback The callback function to be called
 * @param[in] data The data associated to the callback function
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_handler_add(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_event_handler_h *event_handler, tzsh_quickpanel_event_type_e event_type, tzsh_quickpanel_event_cb callback, void *data);

/**
 * @brief Removes the registered event callback function.
 * @since_tizen 3.0
 * @param[in] quickpanel The #tzsh_quickpanel_h object
 * @param[in] event_handler The #tzsh_quickpanel_event_handler_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_handler_del(tzsh_quickpanel_h quickpanel, tzsh_quickpanel_event_handler_h event_handler);

/**
 * @brief Gets the event type.
 * @since_tizen 3.0
 * @param[in] event_info The #tzsh_quickpanel_event_info_h object
 * @param[out] event_type The #tzsh_quickpanel_event_type_e object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_type_get(tzsh_quickpanel_event_info_h event_info, tzsh_quickpanel_event_type_e *event_type);

/**
 * @brief Gets the visible state from given event info.
 * @since_tizen 3.0
 * @param[in] event_info The #tzsh_quickpanel_event_info_h object
 * @param[out] state The visible state of quickpanel
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_visible_get(tzsh_quickpanel_event_info_h event_info, tzsh_quickpanel_state_visible_e *state);

/**
 * @brief Gets the scrollable state from given event info.
 * @since_tizen 3.0
 * @param[in] event_info The #tzsh_quickpanel_event_info_h object
 * @param[out] state The scrollable state of quickpanel
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_scrollable_get(tzsh_quickpanel_event_info_h event_info, tzsh_quickpanel_state_scrollable_e *state);

/**
 * @brief Gets the orientation state from given event info.
 * @since_tizen 3.0
 * @param[in] event_info The #tzsh_quickpanel_event_info_h object
 * @param[out] state The orientation state of quickpanel
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_quickpanel_event_orientation_get(tzsh_quickpanel_event_info_h event_info, tzsh_quickpanel_state_orientation_e *state);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
