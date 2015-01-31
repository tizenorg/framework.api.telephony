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
#include <gio/gio.h>
#include <dlog.h>

#include <tapi_common.h>
#include <ITapiModem.h>
#include "telephony_common.h"
#include "telephony_modem.h"
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

int telephony_modem_get_imei(telephony_h handle, char **imei)
{
	GVariant *gv = NULL;
	GError *gerr = NULL;
	int tapi_result;
	char *tapi_imei;
	int error = TELEPHONY_ERROR_OPERATION_FAILED;
	TapiHandle *tapi_h;

	CHECK_TELEPHONY_SUPPORTED(TELEPHONY_FEATURE);
	CHECK_INPUT_PARAMETER(handle);
	tapi_h = ((telephony_data *)handle)->tapi_h;
	CHECK_INPUT_PARAMETER(tapi_h);
	CHECK_INPUT_PARAMETER(imei);

	gv = g_dbus_connection_call_sync(tapi_h->dbus_connection,
		DBUS_TELEPHONY_SERVICE, tapi_h->path, DBUS_TELEPHONY_MODEM_INTERFACE,
		"GetIMEI", NULL, NULL, G_DBUS_CALL_FLAGS_NONE, -1, NULL, &gerr);

	if (gv) {
		g_variant_get(gv, "(is)", &tapi_result, &tapi_imei);
		if (tapi_result == 0) {
			if (tapi_imei != NULL && strlen(tapi_imei) != 0) {
				*imei = g_strdup_printf("%s", tapi_imei);
				error = TELEPHONY_ERROR_NONE;
			}
		}
	} else {
		LOGE("g_dbus_conn failed. error (%s)", gerr->message);
		if (strstr(gerr->message, "No access rights")) {
			LOGE("PERMISSION_DENIED");
			error = TELEPHONY_ERROR_PERMISSION_DENIED;
		}
	}

	return error;
}
