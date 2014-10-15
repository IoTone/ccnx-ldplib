#ifndef __ldp_h__
#define __ldp_h__
/**
#
#Copyright (c) 2014 IoTone, Inc. All rights reserved.
#
#Redistribution and use in source and binary forms, with or without modification,
#are permitted provided that the following conditions are met:
#
#    * Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#
#    * Redistributions in binary form must reproduce the above copyright notice,
#      this list of conditions and the following disclaimer in the documentation
#      and/or other materials provided with the distribution.
#
#    * Neither the name of IoTone, Inc., nor the names of its
#      contributors may be used to endorse or promote products derived from this
#      software without specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef __ldp_private_h__
    #include "ldp_private.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <cJSON.h>

/*
 * Defs
 */
#define DEFAULT_LDP_NAMESPACE "ccnx:/ldp.iotone.io"
#define DEFAULT_LDP_PEERGROUP "ccnx:/ldp.iotone.io/pg/default"
#define DEFAULT_LDP_PEERGROUP_PEERS "ccnx:/ldp.iotone.io/pg/default/peers"
#define DEFAULT_LDP_PEERGROUP_PEERS_PEERID_PREFIX  "ccnx:/ldp.iotone.io/pg/default/peers/%s"
#define DEFAULT_LDP_PEERGROUP_PEERS_PEERID_SYNC_TOPO_PREFIX  "ccnx:/ldp.iotone.io/pg/default/peers/%s/sync-info"
#define DEFAULT_LDP_PEERGROUP_PEERS_PEERID_METADATA_1_0_0  "ccnx:/ldp.iotone.io/pg/default/peers/%s/metadata_1.0.0"
#define DEFAULT_LDP_NAMESPACE_ROUTE "add ccnx:/ldp.iotone.io udp 224.0.23.170 59695 3 16"
#define DEFAULT_LDP_USER_KEYS_ROUTE "add ccnx:/ccnx.org/Users udp 224.0.23.170 59695 3 16"
#define LDP_API_VERSION "0.9.0.1"

/*
 * API signatures
 */

TLDPSettings *ldp_settings_create(void);
void ldp_settings_destroy(TLDPSettings **settings);
int ldp_settings_init(TLDPSettings *settings);
int ldp_settings_set_sys_fs_path(TLDPSettings *settings, char *path);
int ldp_settings_set_sys_logfile(TLDPSettings *settings, char *path);
int ldp_settings_set_user_id(TLDPSettings *settings, char *user_id);
int ldp_settings_set_keystore_uri(TLDPSettings *settings, char *keystore_uri);
int ldp_write_peer_metadata_from_bytes(char *peer_id_common_name, char *metadata, char *access_control_obj);
char * ldp_get_peer_metadata_as_bytes(char *remote_peer_id_common_name, size_t *data_length, char *access_control_obj);
char ** ldp_get_peers(int *peer_names_length, char *access_control_obj);
int ldp_write_peer_metadata_from_json(char *peer_id_common_name, TJson* json, char *access_control_obj);
TJson* ldp_get_peer_metadata_as_json(char *remote_peer_id_common_name, size_t *data_length, char *access_control_obj);
TJson* ldp_get_peers_as_json(int *peer_names_length, char *access_control_obj);

/*
 * UTILITY Methods
 */
void (*LDPLOG)(int, const char *, ...);
int (*LDPLOG_setmask)(int);
int ldp_log_console_setlogmask(int mask);
void ldp_log_console(int priority, const char *format, ...);
#ifdef __ANDROID__
void ldp_log_to_android_logcat(int priority, const char *format, ...);
#endif

/*
 	Globals - should really be in private
 */

#define TAG "ldplib"

#ifdef __cplusplus
}
#endif
#endif