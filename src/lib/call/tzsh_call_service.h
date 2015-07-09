#ifndef _TZSH_CALL_SERVICE_H_
#define _TZSH_CALL_SERVICE_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <tzsh.h>

/**
 * @brief Handle for the tizen call service.
 * @since_tizen 2.4
 */
typedef struct _tzsh_service_s * tzsh_call_service_h;

/**
 * @internal
 * @brief Creates a new call service handle.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window to provide service of the call.
 * @return #tzsh_call_service_h handle on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_call_service_destroy()
 */
tzsh_call_service_h tzsh_call_service_create(tzsh_h tzsh, tzsh_window win);

/**
 * @internal
 * @brief Destroys the given call service handle.
 * @since_tizen 2.4
 * @param[in] service The call service handle to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_call_service_create()
 */
int tzsh_call_service_destroy(tzsh_call_service_h service);

#ifdef  __cplusplus
}
#endif

#endif
