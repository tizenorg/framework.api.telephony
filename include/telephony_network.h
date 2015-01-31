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

#ifndef __CAPI_TELEPHONY_NETWORK_INFO_H__
#define __CAPI_TELEPHONY_NETWORK_INFO_H__

#include "telephony_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file telephony_network.h
 * @brief This file contains the network APIs and related enumerations.
 */

/**
 * @addtogroup CAPI_TELEPHONY_INFORMATION_NETWORK
 * @{
 */

/**
 * @brief Enumeration for RSSI (Receive Signal Strength Indicator).
 * @details #TELEPHONY_NETWORK_RSSI_6 indicates the highest strength.
 * @since_tizen 2.3
 */
typedef enum
{
    TELEPHONY_NETWORK_RSSI_0, /**< Strength 0 */
    TELEPHONY_NETWORK_RSSI_1, /**< Strength 1 */
    TELEPHONY_NETWORK_RSSI_2, /**< Strength 2 */
    TELEPHONY_NETWORK_RSSI_3, /**< Strength 3 */
    TELEPHONY_NETWORK_RSSI_4, /**< Strength 4 */
    TELEPHONY_NETWORK_RSSI_5, /**< Strength 5 */
    TELEPHONY_NETWORK_RSSI_6, /**< Strength 6 */
} telephony_network_rssi_e;


/**
 * @brief Enumeration for Network Type.
 * @since_tizen 2.3
 */
typedef enum
{
    TELEPHONY_NETWORK_TYPE_UNKNOWN, /**< Unknown */
    TELEPHONY_NETWORK_TYPE_GSM,     /**< 2G GSM network type */
    TELEPHONY_NETWORK_TYPE_GPRS,    /**< 2.5G GPRS network type */
    TELEPHONY_NETWORK_TYPE_EDGE,    /**< 2.5G EDGE network type */
    TELEPHONY_NETWORK_TYPE_UMTS,    /**< 3G UMTS network type */
    TELEPHONY_NETWORK_TYPE_HSDPA,   /**< HSDPA network type */
    TELEPHONY_NETWORK_TYPE_LTE,     /**< LTE network type */
} telephony_network_type_e;


/**
 * @brief Enumeration for Network Service State.
 * @since_tizen 2.3
 */
typedef enum
{
    TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE,     /**< In service */
    TELEPHONY_NETWORK_SERVICE_STATE_OUT_OF_SERVICE, /**< Out of service */
    TELEPHONY_NETWORK_SERVICE_STATE_EMERGENCY_ONLY, /**< Only emergency call is allowed */
} telephony_network_service_state_e;

/**
 * @brief Gets the LAC (Location Area Code) of the current network.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] lac The Location Area Code
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_lac(telephony_h handle, int *lac);

/**
 * @brief Gets the cell ID.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] cell_id The cell identification number
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_cell_id(telephony_h handle, int *cell_id);

/**
 * @brief Gets the RSSI (Received Signal Strength Indicator).
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %%%%%http://tizen.org/privilege/telephony
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] rssi The Received Signal Strength Indicator \n
 *                  Higher the received number, the stronger the signal strength.
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_rssi(telephony_h handle, telephony_network_rssi_e *rssi);

/**
 * @brief Gets the roaming state.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] status @c true if roaming,
 *                    otherwise @c false if not roaming
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_roaming_status(telephony_h handle, bool *status);

/**
 * @brief Gets the MCC (Mobile Country Code) of the current registered network.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks You must release @c mcc using free().
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] mcc The Mobile Country Code (three digits)
 *                 Mobile Country Code (MCC) identifies the country where the cell is being used.
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_mcc(telephony_h handle, char **mcc);

/**
 * @brief Gets the MNC (Mobile Network Code) of the current registered network.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks You must release @c mnc using free().
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] mnc The Mobile Network Code (three digits)
 *                 The Mobile Network Code (MNC) identifies the mobile phone operator and network provider.
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_mnc(telephony_h handle, char **mnc);

/**
 * @brief Gets the name of the current registered network.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks You must release @c network_name using free().
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] network_name The name of the current registered network
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_network_name(telephony_h handle, char **network_name);

/**
 * @brief Gets the network service type of the current registered network.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] network_type The network service type
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #TELEPHONY_ERROR_NONE              Successful
 * @retval #TELEPHONY_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #TELEPHONY_ERROR_PERMISSION_DENIED Permission denied
 * @retval #TELEPHONY_ERROR_NOT_SUPPORTED     Not supported
 * @retval #TELEPHONY_ERROR_OPERATION_FAILED  Operation failed
 *
 * @pre The Network service state must be #TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE.
 *
 * @see telephony_network_get_service_state()
 */
int telephony_network_get_type(telephony_h handle,
    telephony_network_type_e *network_type);

/**
 * @brief Gets the current network state of the telephony service.
 *
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/telephony
 *
 * @remarks To know the state of data network, refer connection API.
 *
 * @param[in] handle The handle from telephony_init()
 * @param[out] network_service_state The current network state
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
int telephony_network_get_service_state(telephony_h handle,
    telephony_network_service_state_e *network_service_state);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif	// __CAPI_TELEPHONY_NETWORK_INFO_H__
