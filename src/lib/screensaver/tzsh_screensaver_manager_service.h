#ifndef _TZSH_SCREENSAVER_MANAGER_SERVICE_H_
#define _TZSH_SCREENSAVER_MANAGER_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <tzsh.h>
#include <tzsh_region.h>

/**
 * @brief Handle for the tizen screensaver service.
 * @since_tizen 3.0
 */
typedef struct _tzsh_service_s * tzsh_screensaver_manager_service_h;

/**
 * @brief Enumeration for screensaver state.
 * @since_tizen 3.0
 */
typedef enum
{
   TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_UNKNOWN = 0x0, /**< Unknown state. */
   TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_IDLE_TIMEOUT_EXPIRED = 0x1, /**< Idle timeout expired. */
   TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_NOT_IDLE = 0x2, /**< Not idle state. User input was generated. */
   TZSH_SCREENSAVER_MANAGER_SERVICE_STATE_MAX = 0xFFFFFFFF, /**< Maximum value of screensaver state. */
} tzsh_screensaver_manager_service_state_e;

/**
 * @brief Handle for the callback function of screensaver service.
 * @since_tizen 3.0
 */
typedef void (*tzsh_screensaver_manager_service_cb)(void *data, tzsh_screensaver_manager_service_h service, int states);

/**
 * @internal
 * @brief Creates a new screensaver service handle.
 * @since_tizen 3.0
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the screensaver.
 * @return #tzsh_screensaver_manager_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_screensaver_manager_service_destroy()
 */
tzsh_screensaver_manager_service_h tzsh_screensaver_manager_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given screensaver service handle.
 * @since_tizen 3.0
 * @param[in] service The screensaver service handle to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_screensaver_manager_service_create()
 */
int tzsh_screensaver_manager_service_destroy(tzsh_screensaver_manager_service_h service);

/**
 * @internal
 * @brief Sets the callback function to be called when the screensaver state is changed.
 * @since_tizen 3.0
 * @param[in] service The screensaver service handle
 * @param[in] cb_func The callback function to be called
 * @param[in] data The data associated to the callback function
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_screensaver_manager_service_state_change_cb_set(tzsh_screensaver_manager_service_h service, tzsh_screensaver_manager_service_cb cb_func, void *data);

/**
 * @internal
 * @brief Sets the number of idle milliseconds since the last input was received from the user.
 * @since_tizen 3.0
 * @param[in] service The screensaver service handle
 * @param[in] time The number of idle milliseconds to be used as screensaver timeout period
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_screensaver_manager_service_state_change_cb_set()
 */
int tzsh_screensaver_manager_service_idle_timeout_set(tzsh_screensaver_manager_service_h service, unsigned int time);

#ifdef  __cplusplus
}
#endif

#endif
