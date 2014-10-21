#ifndef __ldp_private_h__
#define __ldp_private_h__
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
/* XXX TODO: Try to refactor the CCNx dependencies into ldp_private.h */
#include <ccn/ccn.h>
#include <ccn/charbuf.h>
#include <ccn/fetch.h>
#include <ccn/keystore.h>
#include <ccn/signing.h>
#include <ccn/sync.h>
#include <ccn/seqwriter.h>
#include <ccn/face_mgmt.h>
#include <ccn/reg_mgmt.h>
#include <ccn/ccnd.h>
#include <ccn/uri.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <stdarg.h>
#include <math.h>
#ifndef __ANDROID__
#include <sys/statvfs.h> 
#else
#include <sys/statfs.h>
#include <android/log.h>
#endif
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/nameser.h>
#include <resolv.h>
#define BIND_8_COMPAT

/* XXX potentially need to add some pound defs around this as well */
#include <sys/un.h>

/* Private forward declarations */

char *ldp_private_generate_name(uint seed, int length);
double ldp_private_get_fs_mb_available(char * path);
char *ldp_private_create_str(const char *constr);
char *ldp_private_strcat(char *s1, char *s2);
int ldp_private_ccnush_data(struct ccn_charbuf *content_name, char *data, unsigned long data_length, long timeout_in_millis, int scope);
int ldp_private_ccnush_data_with_freshness(struct ccn_charbuf *content_name, char *data, unsigned long data_length, long timeout_in_millis, int scope, int freshness_in_sec, int use_repo);
char *ldp_private_ccnsip_data(char *content_name_uri, long timeout_in_millis, int scope, size_t *data_length);
struct ccn_charbuf *ldp_private_startwrite_tpl(int scope);
struct ccn_charbuf *ldp_private_interest_tpl(int allow_stale, int scope);
char ** ldp_private_get_ccn_child_name_components_under_name(char *uri_prefix, int *number_of_names);

//
//
//
#define ELSECRETOINSEGURO "Th1s1sn0t8g00dp8ssw0rd."
#define SEQWRITER_BLOCKSIZE_DEFAULT 4096

// This not will work on Android platforms that use a different path.  
// In that case, we must specifify the setting for user_ccnx_dir
// XXX Should only define this for android
// This is relative path
#define ANDROID_CCNX_USER_DIR_DEFAULT_SUFFIX "/ccnx/user"
#define DEFAULT_LOG_DIR "/tmp/ldp.log"

#define DEFAULT_LDP_SCOPE 3
// Once things are stable, make this freshness as low as possible, say 5 minutes
#define LDP_CONTENT_FRESHNESS_IN_SEC_DEFAULT 600
// XXX Change this back to 4 seconds when the event loop firing is fixed
#define LDP_CMD_FRESHNESS_IN_SEC_DEFAULT 3
#define LDP_CCN_GET_TIMEOUT_IN_MILLIS_DEFAULT 1000
#define LDP_MAX_NAME_LENGTH 256
/* Forward Declarations */
struct LDPSettings;
struct LDPServiceHandle;

/* 
	NOTE: We attempt to hide these structures from the API user ... 
	gets too complicated too quickly.

	Focus on setting up some useful defaults and on using config files as a way to load and 
	persist settings more easily.  Encapsulate internal structures as much as possible to
	keep this library as high level as possible. 

	TODO: Add some json configuration mechanism
*/
typedef struct LDPSettings TLDPSettings;
typedef struct cJSON TJson;
typedef struct ccn_charbuf TCBuf;

/*
 * Globals
 */
// XXX This should be larger, how do we scale at Internet scale?
#define MAX_GLOBAL_PEERS_LENGTH 512
static char* global_peer_names[MAX_GLOBAL_PEERS_LENGTH] = {0};
static int global_peer_names_length = 0;
static struct ccn_keystore* global_keystore_cached = NULL;

#define TRUE 1
#define FALSE 0

#endif