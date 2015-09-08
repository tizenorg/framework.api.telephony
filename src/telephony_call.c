/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <dlog.h>

#include <tapi_common.h>
#include <TapiUtility.h>
#include <ITapiCall.h>
#include "telephony_common.h"
#include "telephony_call.h"
#include "telephony_private.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPI_TELEPHONY"

#define CHECK_INPUT_PARAMETER(arg) \
	if (arg == NULL) { \
		LOGE("INVALID_PARAMETER"); \
		return TELEPHONY_ERROR_INVALID_PARAMETER; \
	}

static void _mapping_call_state(TelCallStates_t tapi_call_state, telephony_call_state_e *call_state)
{
	switch (tapi_call_state) {
	case TAPI_CALL_STATE_ACTIVE:
	case TAPI_CALL_STATE_HELD:
		if (*call_state != TELEPHONY_CALL_STATE_CONNECTING)
			*call_state = TELEPHONY_CALL_STATE_CONNECTED;
		break;
	case TAPI_CALL_STATE_DIALING:
	case TAPI_CALL_STATE_ALERT:
	case TAPI_CALL_STATE_INCOMING:
	case TAPI_CALL_STATE_WAITING:
		*call_state = TELEPHONY_CALL_STATE_CONNECTING;
		break;
	/* Do not check IDLE state to prevent overriding in case of multi-party call */
	default:
		LOGE("Not handled call state: [%d]", tapi_call_state);
		break;
	}
}

static void _voice_call_get_state_cb(TelCallStatus_t *tapi_status, void *user_data)
{
	telephony_call_state_e *call_state = user_data;

	if (tapi_status->CallType != TAPI_CALL_TYPE_VOICE
			&& tapi_status->CallType != TAPI_CALL_TYPE_E911)
		return;

	_mapping_call_state(tapi_status->CallState, call_state);
}

static void _video_call_get_state_cb(TelCallStatus_t *tapi_status, void *user_data)
{
	telephony_call_state_e *call_state = user_data;

	if (tapi_status->CallType != TAPI_CALL_TYPE_DATA)
		return;

	_mapping_call_state(tapi_status->CallState, call_state);
}

int telephony_call_get_voice_call_state(telephony_h handle, telephony_call_state_e *call_state)
{
	int ret;
	TapiHandle *tapi_h;

	CHECK_TELEPHONY_SUPPORTED(TELEPHONY_FEATURE);
	CHECK_INPUT_PARAMETER(handle);
	tapi_h = ((telephony_data *)handle)->tapi_h;
	CHECK_INPUT_PARAMETER(tapi_h);
	CHECK_INPUT_PARAMETER(call_state);

	*call_state = TELEPHONY_CALL_STATE_IDLE;

	ret = tel_get_call_status_all(tapi_h, _voice_call_get_state_cb, call_state);
	if (ret == TAPI_API_ACCESS_DENIED) {
		LOGE("PERMISSION_DENIED");
		return TELEPHONY_ERROR_PERMISSION_DENIED;
	} else if (ret != TAPI_API_SUCCESS) {
		LOGE("OPERATION_FAILED");
		return TELEPHONY_ERROR_OPERATION_FAILED;
	}

	LOGI("call_state: [%d]", *call_state);

	return TELEPHONY_ERROR_NONE;
}

int telephony_call_get_video_call_state(telephony_h handle, telephony_call_state_e *call_state)
{
	int ret;
	TapiHandle *tapi_h;

	CHECK_TELEPHONY_SUPPORTED(TELEPHONY_FEATURE);
	CHECK_INPUT_PARAMETER(handle);
	tapi_h = ((telephony_data *)handle)->tapi_h;
	CHECK_INPUT_PARAMETER(tapi_h);
	CHECK_INPUT_PARAMETER(call_state);

	*call_state = TELEPHONY_CALL_STATE_IDLE;

	ret = tel_get_call_status_all(tapi_h, _video_call_get_state_cb, call_state);
	if (ret == TAPI_API_ACCESS_DENIED) {
		LOGE("PERMISSION_DENIED");
		return TELEPHONY_ERROR_PERMISSION_DENIED;
	} else if (ret != TAPI_API_SUCCESS) {
		LOGE("OPERATION_FAILED");
		return TELEPHONY_ERROR_OPERATION_FAILED;
	}

	LOGI("call_state: [%d]", *call_state);

	return TELEPHONY_ERROR_NONE;
}
