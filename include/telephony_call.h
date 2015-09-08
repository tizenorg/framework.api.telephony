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

#ifndef __CAPI_TELEPHONY_CALL_H__
#define __CAPI_TELEPHONY_CALL_H__

/**
 * @file telephony_call.h
 * @brief This file contains call APIs and related enumeration.
 */

#include "telephony_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_TELEPHONY_INFORMATION_CALL
 * @{
 */

/**
 * @brief Enumeration for the call state.
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 */
typedef enum
{
    TELEPHONY_CALL_STATE_IDLE,       /**< There exists no calls. */
    TELEPHONY_CALL_STATE_CONNECTING, /**< There exists at least one call that is dialing, alerting or incoming */
    TELEPHONY_CALL_STATE_CONNECTED,  /**< There exist active or held calls, and no calls are dialing, alerting or incoming*/
} telephony_call_state_e;

/**
 * @brief Gets the voice call state of the telephony service.
 * @details Determines if the voice call is connecting, connected, or idle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks When you are dialing a number or a new voice call is ringing,
 *          the state of the voice call is #TELEPHONY_CALL_STATE_CONNECTING.
 *          When a new voice call is connecting while another voice call is already connected,
 *          the state of the voice call is #TELEPHONY_CALL_STATE_CONNECTING as well.
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] call_state The current state of the voice call
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
int telephony_call_get_voice_call_state(telephony_h handle, telephony_call_state_e *call_state);

/**
 * @brief Gets the video call state of the telephony service.
 * @details Determines if the video call is connecting, connected, or idle.
 *
 * @since_tizen @if MOBILE 2.3 @elseif WEARABLE 2.3.1 @endif
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks When you are dialing a number or a new video call is ringing,
 *          the state of the video call is #TELEPHONY_CALL_STATE_CONNECTING.
 *          If a video call is connected, then the state of any other call cannot be
 *          #TELEPHONY_CALL_STATE_CONNECTING and #TELEPHONY_CALL_STATE_CONNECTED.
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] call_state The current state of the video call
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
int telephony_call_get_video_call_state(telephony_h handle, telephony_call_state_e *call_state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif // __CAPI_TELEPHONY_CALL_H__
