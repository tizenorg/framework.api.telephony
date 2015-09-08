/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CAPI_TELEPHONY_MODEM_H__
#define __CAPI_TELEPHONY_MODEM_H__

/**
 * @file telephony_modem.h
 * @brief This file contains modem APIs.
 */

#include "telephony_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_TELEPHONY_INFORMATION_MODEM
 * @{
 */

/**
 * @brief Gets the IMEI (International Mobile Station Equipment Identity) of a mobile phone.
 * @details The IMEI number is used by a GSM network to identify valid devices
 *          and therefore can be used for stopping a stolen phone from accessing that network.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks You must release @c imei using free().
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] imei The International Mobile Station Equipment Identity
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 */
int telephony_modem_get_imei(telephony_h handle, char **imei);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // __CAPI_TELEPHONY_MODEM_H__
