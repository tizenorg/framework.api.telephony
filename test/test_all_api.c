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

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <dlog.h>

#include <telephony.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPI_TELEPHONY_TEST"

static GMainLoop *event_loop;

static int network_noti_tbl[] = {
	TELEPHONY_NOTI_NETWORK_SERVICE_STATE,
	TELEPHONY_NOTI_NETWORK_CELLID,
	TELEPHONY_NOTI_NETWORK_ROAMING_STATUS,
	TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL
};

static int call_noti_tbl[] = {
	TELEPHONY_NOTI_VOICE_CALL_STATE,
	TELEPHONY_NOTI_VIDEO_CALL_STATE
};

static const char *_mapping_sim_state(telephony_sim_state_e sim_state)
{
	switch (sim_state) {
	case TELEPHONY_SIM_STATE_AVAILABLE:
		return "Available";
	case TELEPHONY_SIM_STATE_LOCKED:
		return "Locked";
	case TELEPHONY_SIM_STATE_UNKNOWN:
		return "Unknown";
	default:
		return "Unavailable";
	}
}

static void sim_noti_cb(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
{
	LOGI("Noti!! SIM status: [%d]", *(int *)data);

//	g_main_loop_quit(event_loop);
}


static const char *_mapping_service_state(telephony_network_service_state_e service_state)
{
	switch (service_state) {
	case TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE:
		return "In service";
	case TELEPHONY_NETWORK_SERVICE_STATE_OUT_OF_SERVICE:
		return "Out of service";
	case TELEPHONY_NETWORK_SERVICE_STATE_EMERGENCY_ONLY:
		return "Emergency only";
	default:
		return "Unknown state";
	}
}

static const char *_mapping_network_type(telephony_network_type_e network_type)
{
	switch (network_type) {
	case TELEPHONY_NETWORK_TYPE_GSM:
		return "GSM";
	case TELEPHONY_NETWORK_TYPE_GPRS:
		return "GPRS";
	case TELEPHONY_NETWORK_TYPE_EDGE:
		return "EDGE";
	case TELEPHONY_NETWORK_TYPE_UMTS:
		return "UMTS";
	case TELEPHONY_NETWORK_TYPE_HSDPA:
		return "HSDPA";
	case TELEPHONY_NETWORK_TYPE_LTE:
		return "LTE";
	default:
		return "Unknown";
	}
}

static void network_noti_cb(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
{
	switch (noti_id) {
	case TELEPHONY_NOTI_NETWORK_SERVICE_STATE:
		LOGI("Noti!!! Service state: [%s]", _mapping_service_state(*(int *)data));
		break;
	case TELEPHONY_NOTI_NETWORK_CELLID:
		LOGI("Noti!!! Cell ID: [%d]", *(int *)data);
		break;
	case TELEPHONY_NOTI_NETWORK_ROAMING_STATUS:
		LOGI("Noti!!! Roaming status: [%s]", *(int *)data ? "ON" : "OFF");
		break;
	case TELEPHONY_NOTI_NETWORK_SIGNALSTRENGTH_LEVEL:
		LOGI("Noti!!! Signal strength: [%d]", *(int *)data);
		break;
	default:
		LOGE("Unknown noti");
		break;
	}

//	g_main_loop_quit(event_loop);
}

static const char *_mapping_call_state(telephony_call_state_e call_state)
{
	switch (call_state) {
	case TELEPHONY_CALL_STATE_IDLE:
		return "Idle";
	case TELEPHONY_CALL_STATE_CONNECTING:
		return "Connecting";
	case TELEPHONY_CALL_STATE_CONNECTED:
		return "Active";
	default:
		return "Unknown";
	}
}

static void call_noti_cb(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
{
	switch (noti_id) {
	case TELEPHONY_NOTI_VOICE_CALL_STATE:
		LOGI("Noti!!! Voice Call state: [%s]", _mapping_call_state(*(int *)data));
		break;
	case TELEPHONY_NOTI_VIDEO_CALL_STATE:
		LOGI("Noti!!! Video Call state: [%s]", _mapping_call_state(*(int *)data));
		break;
	default:
		LOGE("Unknown noti");
		break;
	}

//	g_main_loop_quit(event_loop);
}

int main()
{
	telephony_handle_list_s handle_list;
	int ret_value, i;

	/* SIM value */
	char *operator = NULL;
	char *icc_id = NULL;
	char *msin = NULL;
	char *spn = NULL;
	telephony_sim_state_e sim_state = 0;
	char *subscriber_number = NULL;

	/* Network value */
	int cell_id = 0;
	int lac = 0;
	char *mcc = NULL;
	char *mnc = NULL;
	char *network_name = NULL;
	bool roaming_status;
	telephony_network_rssi_e rssi = 0;
	telephony_network_service_state_e service_state = 0;
	telephony_network_type_e network_type = 0;

	/* Call value */
	telephony_call_state_e call_state = 0;

	/* Modem value */
	char *imei = NULL;

	/* Initialize handle */
	ret_value = telephony_init(&handle_list);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("Initialize failed!!!");
		return 0;
	}

	LOGI("handle count: [%d]", handle_list.count);

	/* SIM API */
	ret_value = telephony_sim_get_operator(handle_list.handle[0], &operator);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_operator() failed!!! [%d]", ret_value);
	} else {
		LOGI("Operator is [%s]", operator);
		free(operator);
	}

	ret_value = telephony_sim_get_icc_id(handle_list.handle[0], &icc_id);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_icc_id() failed!!! [%d]", ret_value);
	} else {
		LOGI("ICC-ID is [%s]", icc_id);
		free(icc_id);
	}

	ret_value = telephony_sim_get_msin(handle_list.handle[0], &msin);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_msin() failed!!! [%d]", ret_value);
	} else {
		LOGI("MSIN is [%s]", msin);
		free(msin);
	}

	ret_value = telephony_sim_get_spn(handle_list.handle[0], &spn);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_spn() failed!!! [%d]", ret_value);
	} else {
		LOGI("SPN is [%s]", spn);
		free(spn);
	}

	ret_value = telephony_sim_get_state(handle_list.handle[0], &sim_state);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_state() failed!!! [%d]", ret_value);
	} else {
		LOGI("SIM state is [%s]", _mapping_sim_state(sim_state));
	}

	ret_value = telephony_sim_get_subscriber_number(handle_list.handle[0], &subscriber_number);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_sim_get_subscriber_number() failed!!! [%d]", ret_value);
	} else {
		LOGI("Subscriber number is [%s]", subscriber_number);
		free(subscriber_number);
	}

	/* Network API */
	ret_value = telephony_network_get_cell_id(handle_list.handle[0], &cell_id);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_cell_id() failed!!! [%d]", ret_value);
	} else {
		LOGI("Cell ID is [%d]", cell_id);
	}

	ret_value = telephony_network_get_lac(handle_list.handle[0], &lac);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_lac() failed!!! [%d]", ret_value);
	} else {
		LOGI("Location Area Code is [%d]", lac);
	}

	ret_value = telephony_network_get_mcc(handle_list.handle[0], &mcc);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_mcc() failed!!! [%d]", ret_value);
	} else {
		LOGI("Mobile Country Code is [%s]", mcc);
		free(mcc);
	}

	ret_value = telephony_network_get_mnc(handle_list.handle[0], &mnc);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_mnc() failed!!! [%d]", ret_value);
	} else {
		LOGI("Mobile Network Code is [%s]", mnc);
		free(mnc);
	}

	ret_value = telephony_network_get_network_name(handle_list.handle[0], &network_name);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_network_name() failed!!! [%d]", ret_value);
	} else {
		LOGI("Network name is [%s]", network_name);
		free(network_name);
	}

	ret_value = telephony_network_get_roaming_status(handle_list.handle[0], &roaming_status);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_roaming_status() failed!!! [%d]", ret_value);
	} else {
		LOGI("Network Roaming: [%s]", roaming_status ? "ON" : "OFF");
	}

	ret_value = telephony_network_get_rssi(handle_list.handle[0], &rssi);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_rssi() failed!!! [%d]", ret_value);
	} else {
		LOGI("Received Signal Strength Indicator is [%d]", rssi);
	}

	ret_value = telephony_network_get_service_state(handle_list.handle[0], &service_state);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_service_state() failed!!! [%d]", ret_value);
	} else {
		LOGI("Network service state is [%s]", _mapping_service_state(service_state));
	}

	ret_value = telephony_network_get_type(handle_list.handle[0], &network_type);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_network_get_type() failed!!! [%d]", ret_value);
	} else {
		LOGI("Network type is [%s]", _mapping_network_type(network_type));
	}

	/* Call API */
	ret_value = telephony_call_get_voice_call_state(handle_list.handle[0], &call_state);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_call_get_voice_call_state() failed!!! [%d]", ret_value);
	} else {
		LOGI("Voice Call state is [%s]", _mapping_call_state(call_state));
	}

	ret_value = telephony_call_get_video_call_state(handle_list.handle[0], &call_state);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_call_get_video_call_state() failed!!! [%d]", ret_value);
	} else {
		LOGI("Video Call state is [%s]", _mapping_call_state(call_state));
	}

	/* Modem API */
	ret_value = telephony_modem_get_imei(handle_list.handle[0], &imei);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("telephony_modem_get_imei() failed!!! [%d]", ret_value);
	} else {
		LOGI("IMEI is [%s]", imei);
		free(imei);
	}

	/* set_noti_cb */
	ret_value = telephony_set_noti_cb(handle_list.handle[0], TELEPHONY_NOTI_SIM_STATUS, sim_noti_cb, NULL);
	if (ret_value != TELEPHONY_ERROR_NONE)
		LOGE("Set noti failed!!!");

	for (i = 0; i < 4; i++) {
		ret_value = telephony_set_noti_cb(handle_list.handle[0], network_noti_tbl[i], network_noti_cb, NULL);
		if (ret_value != TELEPHONY_ERROR_NONE)
			LOGE("Set noti failed!!!");
	}

	for (i = 0; i < 2; i++) {
		ret_value = telephony_set_noti_cb(handle_list.handle[0], call_noti_tbl[i], call_noti_cb, NULL);
		if (ret_value != TELEPHONY_ERROR_NONE)
			LOGE("Set noti failed!!!");
	}

	LOGI("If telephony status is changed, then callback function will be called");
	event_loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(event_loop);

	ret_value = telephony_unset_noti_cb(handle_list.handle[0], TELEPHONY_NOTI_SIM_STATUS);
	if (ret_value != TELEPHONY_ERROR_NONE)
		LOGE("Unset noti failed!!!");

	for (i = 0; i < 4; i++) {
		ret_value = telephony_unset_noti_cb(handle_list.handle[0], network_noti_tbl[i]);
		if (ret_value != TELEPHONY_ERROR_NONE)
			LOGE("Unset noti failed!!!");
	}

	for (i = 0; i < 2; i++) {
		ret_value = telephony_unset_noti_cb(handle_list.handle[0], call_noti_tbl[i]);
		if (ret_value != TELEPHONY_ERROR_NONE)
			LOGE("Unset noti failed!!!");
	}

	ret_value = telephony_deinit(&handle_list);
	if (ret_value != TELEPHONY_ERROR_NONE) {
		LOGE("Deinitialize failed!!!");
	}

	return 0;
}
