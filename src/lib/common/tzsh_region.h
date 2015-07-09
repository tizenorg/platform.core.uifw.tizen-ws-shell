#ifndef _TZSH_REGION_H_
#define _TZSH_REGION_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for the tizen region.
 * @since_tizen 2.4
 */
typedef struct _tzsh_region_s * tzsh_region_h;

/**
 * @brief Creates the tizen region object.
 * @since_tizen 2.4
 * @param[in] tzsh The #tzsh_h instance
 * @return #tzsh_region_h object on success, @c NULL otherwise
 * @pre You have to create #tzsh_h instance using tzsh_create() before calling this API.
 * @see tzsh_create()
 * @see tzsh_region_destroy()
 */
tzsh_region_h tzsh_region_create(tzsh_h tzsh);

/**
 * @brief Destroys the given tizen region.
 * @since_tizen 2.4
 * @param[in] region The tizen region object
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 * @see tzsh_region_create()
 */
int tzsh_region_destroy(tzsh_region_h region);

/**
 * @brief Adds the rectangle to the region.
 * @since_tizen 2.4
 * @param[in] region The tizen region object
 * @param[in] x The x coordinate
 * @param[in] y The y coordinate
 * @param[in] w The width
 * @param[in] h The height
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_region_add(tzsh_region_h region, int x, int y, int w, int h);

/**
 * @brief Substracts the rectangle to the tizen region.
 * @since_tizen 2.4
 * @param[in] region The tizen region object
 * @param[in] x The x coordinate
 * @param[in] y The y coordinate
 * @param[in] w The width
 * @param[in] h The height
 * @return @c 0 on success, otherwise a negative error value
 * @retval #TZSH_ERROR_NONE Successful
 * @retval #TZSH_ERROR_INVALID_PARAMETER Invalid parameter
 */
int tzsh_region_subtract(tzsh_region_h region, int x, int y, int w, int h);

#ifdef  __cplusplus
}
#endif

#endif
