#ifndef _TZSH_TVSRV_H_
#define _TZSH_TVSRV_H_

/**
 * @addtogroup TIZEN_WS_SHELL_TVSRV_MODULE
 * @{
 */

#include <tzsh.h>

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen tvsrv client.
 * @since_tizen 3.0
 */
typedef struct _tzsh_tvsrv_s * tzsh_tvsrv_h;

/**
 * @brief Creates the #tzsh_tvsrv_h object which handles the tvsrv service.
 * @since_tizen 3.0
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] tzsh The #tzsh_h instance
 * @param[in] win The native window
 * @return #tzsh_tvsrv_h object on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_SERVICE_NOT_EXSITED Service not exist
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_tvsrv_destroy()
 */
tzsh_tvsrv_h tzsh_tvsrv_create(tzsh_h tzsh, tzsh_window win);

/**
 * @brief Destroys the given #tzsh_tvsrv_h object.
 * @since_tizen 3.0
 * @param[in] tvsrv The #tzsh_tvsrv_h object to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_tvsrv_create()
 */
int tzsh_tvsrv_destroy(tzsh_tvsrv_h tvsrv);

/**
 * @brief Requests to bind with the tvsrv service window.
 * @since_tizen 3.0
 * @param[in] tvsrv The #tzsh_tvsrv_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_tvsrv_bind(tzsh_tvsrv_h tvsrv);

/**
 * @brief Requests to unbind with the tvsrv service window.
 * @since_tizen 3.0
 * @param[in] tvsrv The #tzsh_tvsrv_h object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TZSH_ERROR_SERVICE_NOT_EXSITED No such service
 */
int tzsh_tvsrv_unbind(tzsh_tvsrv_h tvsrv);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
