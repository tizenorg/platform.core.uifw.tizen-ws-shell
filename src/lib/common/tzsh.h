#ifndef _TZSH_COMMON_H_
#define _TZSH_COMMON_H_


/**
 * @addtogroup TIZEN_WS_SHELL_MODULE
 * @{
 */

#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen shell.
 * @since_tizen 2.4
 */
typedef struct _tzsh_s * tzsh_h;

/**
 * @brief The window handle for native window.
 * @details This is abstract window type for native window handle.
 * @since_tizen 2.4
 */
typedef unsigned int tzsh_window;

/**
 * @brief Enumeration for toolkit type.
 * @since_tizen 2.4
 */
typedef enum
{
   TZSH_TOOLKIT_TYPE_UNKNOWN, /**< Unknown type */
   TZSH_TOOLKIT_TYPE_EFL, /**< Use EFL toolkit */
} tzsh_toolkit_type_e;

#ifndef TIZEN_ERROR_TZSH
#define TIZEN_ERROR_TZSH -0x05000000
#endif

/**
 * @brief Enumeration for tizen shell error.
 * @since_tizen 2.4
 */
typedef enum
{
   TZSH_ERROR_NONE = TIZEN_ERROR_NONE, /*< Successful */
   TZSH_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
   TZSH_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
   TZSH_ERROR_PERMISSION_DENIED = TIZEN_ERROR_PERMISSION_DENIED, /**< Permission denied */
   TZSH_ERROR_SERVICE_NOT_EXSITED = TIZEN_ERROR_TZSH | 0x01,/**< Service not exist */
} tzsh_error_e;


/**
 * @brief Creates the #tzsh_h instance.
 * @since_tizen 2.4
 * @remarks The specific error code can be obtained using the get_last_result() method. Error codes are described in exception section.
 * @param[in] type The type of toolkit
 * @return #tzsh_h instance on success, @c NULL otherwise
 * @exception #TZSH_ERROR_NONE Successful
 * @exception #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @exception #TZSH_ERROR_OUT_OF_MEMORY Out of memory
 * @see tzsh_destroy()
 */
tzsh_h tzsh_create(tzsh_toolkit_type_e type);

/**
 * @brief Destroys the given #tzsh_h instance.
 * @since_tizen 2.4
 * @param[in] tzsh The #tzsh_h instance to be destroyed
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_create()
 */
int tzsh_destroy(tzsh_h tzsh);

#ifdef  __cplusplus
}
#endif

/**
 * @}
 */

#endif
