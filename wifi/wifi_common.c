/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include "hardware_legacy/wifi_old.h"

#define LOG_TAG "WifiHW"
#include "cutils/log.h"

extern int WIFI_CHIP_TYPE;

extern int wifi_command_bcm(const char *ifname, const char *command, char *reply, size_t *reply_len);
extern int is_wifi_driver_loaded_bcm();
extern int wifi_load_driver_bcm();
extern int wifi_unload_driver_bcm();
extern int wifi_start_supplicant_bcm(int p2p_supported);
extern int wifi_stop_supplicant_bcm(int p2p_supported);
extern int wifi_connect_to_supplicant_bcm(const char *ifname);
extern void wifi_close_supplicant_connection_bcm(const char *ifname);
extern int wifi_wait_for_event_bcm(const char *ifname, char *buf, size_t buflen);
extern int wifi_change_fw_path_bcm(const char *fwpath);

extern int wifi_command_mt5931(const char *ifname, const char *command, char *reply, size_t *reply_len);
extern int is_wifi_driver_loaded_mt5931();
extern int wifi_load_driver_mt5931();
extern int wifi_unload_driver_mt5931();
extern int wifi_start_supplicant_mt5931(int p2p_supported);
extern int wifi_stop_supplicant_mt5931(int p2p_supported);
extern int wifi_connect_to_supplicant_mt5931(const char *ifname);
extern void wifi_close_supplicant_connection_mt5931(const char *ifname);
extern int wifi_wait_for_event_mt5931(const char *ifname, char *buf, size_t buflen);
extern int wifi_change_fw_path_mt5931(const char *fwpath);

static int debug = 0;

int wifi_command(const char *ifname, const char *command, char *reply, size_t *reply_len)
{
	//if(debug) ALOGD("wifi_command: %s, %s", ifname, command);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_command_mt5931(ifname, command, reply, reply_len);
    } else {
    	return wifi_command_bcm(ifname, command, reply, reply_len);
    }
}

int is_wifi_driver_loaded() {
	if(debug) ALOGD("is_wifi_driver_loaded: WIFI_CHIP_TYPE = %d", WIFI_CHIP_TYPE);
	WIFI_CHIP_TYPE = check_wifi_chip_type();
    if(WIFI_CHIP_TYPE == MT5931) {
    	return is_wifi_driver_loaded_mt5931();
    } else {
    	return is_wifi_driver_loaded_bcm();
    }
}

extern int check_wifi_chip_type(void);
int wifi_load_driver()
{
	if(debug) ALOGD("wifi_load_driver: WIFI_CHIP_TYPE = %d", WIFI_CHIP_TYPE);
    WIFI_CHIP_TYPE = check_wifi_chip_type();
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_load_driver_mt5931();
    } else {
    	return wifi_load_driver_bcm();
    }
}

int wifi_unload_driver()
{
	WIFI_CHIP_TYPE = check_wifi_chip_type();
	if(debug) ALOGD("wifi_unload_driver: WIFI_CHIP_TYPE = %d", WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_unload_driver_mt5931();
    } else {
    	return wifi_unload_driver_bcm();
    }
}

int wifi_start_supplicant(int p2p_supported)
{
	if(debug) ALOGD("wifi_start_supplicant: %d, WIFI_CHIP_TYPE = %d", p2p_supported, WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_start_supplicant_mt5931(p2p_supported);
    } else {
    	return wifi_start_supplicant_bcm(p2p_supported);
    }
}

int wifi_stop_supplicant(int p2p_supported)
{
	if(debug) ALOGD("wifi_stop_supplicant: %d, WIFI_CHIP_TYPE = %d", p2p_supported, WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_stop_supplicant_mt5931(p2p_supported);
    } else {
    	return wifi_stop_supplicant_bcm(p2p_supported);
    }
}

/* Establishes the control and monitor socket connections on the interface */
int wifi_connect_to_supplicant(const char *ifname)
{
	if(debug) ALOGD("wifi_connect_to_supplicant: %s, WIFI_CHIP_TYPE = %d", ifname, WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_connect_to_supplicant_mt5931(ifname);
    } else {
    	return wifi_connect_to_supplicant_bcm(ifname);
    }
}

void wifi_close_supplicant_connection(const char *ifname)
{
	if(debug) ALOGD("wifi_close_supplicant_connection: %s, WIFI_CHIP_TYPE = %d", ifname, WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_close_supplicant_connection_mt5931(ifname);
    } else {
    	return wifi_close_supplicant_connection_bcm(ifname);
    }
}

int wifi_wait_for_event(const char *ifname, char *buf, size_t buflen)
{
	if(debug) ALOGD("wifi_wait_for_event: %s", ifname);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_wait_for_event_mt5931(ifname, buf, buflen);
    } else {
    	return wifi_wait_for_event_bcm(ifname, buf, buflen);
    }
}

int wifi_change_fw_path(const char *fwpath)
{
	WIFI_CHIP_TYPE = check_wifi_chip_type();
	if(debug) ALOGD("wifi_change_fw_path: %s, WIFI_CHIP_TYPE = %d", fwpath, WIFI_CHIP_TYPE);
    if(WIFI_CHIP_TYPE == MT5931) {
    	return wifi_change_fw_path_mt5931(fwpath);
    } else {
    	return wifi_change_fw_path_bcm(fwpath);
    }
}
