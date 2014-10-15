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
#ifndef __ldp_h__
    #include "ldp.h"
#endif

/* CCNx Defs */
#define ALLOW_STALE 0x10

//
// Data Structures
//
static 
enum ccn_content_type content_type = CCN_CONTENT_DATA;
/* This is used in the name arg to ccn_connect() */
char *ldp_private_connection_name = "tcp"; /* Set default */

/* Implementations for public interface exposed in header */
struct LDPSettings {
    char *sys_logfile;              /* logfile name for any logging by LDP lib */
    int sys_log_level;				/* log level */
    int ccnd_routes_count;			/* Number of routes */
    char **ccnd_routes; 			/* Pointer to array of Routes needed to bootstrap CCND for LDP lib */
    char *topo_prefix;				/* We will prepopulate this, but allow this to be overriden */
    char *user_id;					/* Username of the library user - can be anything globally unique */
    char *user_secret;				/* User's secret - TBD how we will eventually do user security */
	char *user_copyright; 			/* User's default copyright to use for now a free form field */
	size_t sys_fs_min_mb_available; /* Configurable value for minimum number of Megabytes available */
	size_t sys_fs_max_mb;			/* Configurable value for max number of Megabytes available to LDP lib */
	char *user_location_default; 	/* User's default location if none is provided in photo metadata */
	char *sys_fs_path;				/* System path to a read/write fs */
	char *user_presence_default; 	/* User's default presence */
	char *ccnd_hostname;			/* CCND Hostname */
	char *ccnd_port;				/* CCND Port */
	char *keystore_uri;				/* URI to keystore, optional, we can initialize to a default if a keystore DNE */
	char *keylocator_uri;			/* CCN name for the key locator, we can use the default signing keys */
	char *user_ccnx_dir;			/* Map this to env to override default CCNX_DIR */
};

TLDPSettings *ldp_settings_create(void) {
	TLDPSettings *obj;

	obj = (TLDPSettings*) malloc( sizeof(TLDPSettings));

	if (obj == NULL) {
		return NULL;
	}

	memset(obj, '\0', sizeof(TLDPSettings));
	return obj;
} /* create a TLDPSettings obj */

void ldp_settings_destroy(TLDPSettings **settings) {
	TLDPSettings *ldpobj = *settings;
	int i = 0;
	int size;

	if (ldpobj != NULL) {
		if (ldpobj->sys_logfile != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->sys_logfile), sys_logfile=%s", ldpobj->sys_logfile);
			free(ldpobj->sys_logfile);
		}

		if (ldpobj->ccnd_routes != NULL) {
			size = ldpobj->ccnd_routes_count;
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), size of ccnd_routes = %d", size);
			for (i = 0; i < size; i++) {
				if (ldpobj->ccnd_routes[i] != NULL) {
					LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->ccnd_routes[%d])", i);
					free(ldpobj->ccnd_routes[i]);
				}
			}
		}

		if (ldpobj->topo_prefix != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->topo_prefix)");
			free(ldpobj->topo_prefix);
		}

		if (ldpobj->user_id != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_id)");
			free(ldpobj->user_id);
		}

		if (ldpobj->user_secret != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_secret)");
			free(ldpobj->user_secret);
		}

		if (ldpobj->user_copyright != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_copyright)");
			free(ldpobj->user_copyright);
		}

		if (ldpobj->user_location_default != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_location_default)");
			free(ldpobj->user_location_default);
		}

		if (ldpobj->sys_fs_path != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->sys_fs_path)");
			free(ldpobj->sys_fs_path);
		}

		if (ldpobj->user_presence_default != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_presence_default)");
			free(ldpobj->user_presence_default);
		}

		if (ldpobj->ccnd_hostname != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->ccnd_routes_count)");
			free(ldpobj->ccnd_hostname);
		}

		if (ldpobj->ccnd_port != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->ccnd_port)");
			free(ldpobj->ccnd_port);
		}

		if (ldpobj->keystore_uri != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->keystore_uri)");
			free(ldpobj->keystore_uri);
		}

		if (ldpobj->keylocator_uri != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->keylocator_uri)");
			free(ldpobj->keylocator_uri);
		}

		if (ldpobj->user_ccnx_dir != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(ldpobj->user_ccnx_dir)");
			free(ldpobj->user_ccnx_dir);
		}

		free(ldpobj);
		*settings = NULL;
	}
}

int ldp_settings_init(TLDPSettings *settings) {
	int ret;
	double fs_available;

	// Set some reasonable defaults for logging, use our console
	// Not really sure where is the best place to set this ...  probably in the app, so may want to remove this
	// Configure default logging
	#ifndef __ANDROID__
	LDPLOG = &ldp_log_console;
	ldp_private_connection_name = "tcp";
	#else
	// LDPLOG = &__android_log_print;
	LDPLOG = &ldp_log_to_android_logcat;
	ldp_private_connection_name = "tcp";
	#endif

	LDPLOG_setmask = &ldp_log_console_setlogmask;
	LDPLOG(LOG_DEBUG, "ldp_settings_init()  begin");
	// We just need to perform any book keeping at the system level

	// Let's set reasonable defaults if they aren't configured yet
	if (settings->sys_logfile == NULL) {
		// TBD - Decide where to put these private defaults
		LDPLOG(LOG_DEBUG, "ldp_settings_init() about to call ldp_private_create_str");
		settings->sys_logfile = ldp_private_create_str(DEFAULT_LOG_DIR);
	}

	if (settings->sys_log_level == 0) {
		// TBD - Decide where to put these private defaults
		settings->sys_log_level = LOG_INFO;
	}
	LDPLOG_setmask(LOG_MASK(settings->sys_log_level));

	// verify that we have read/write access to our FS
	if (settings->sys_fs_path == NULL) {
		// TBD - Decide where to put these private defaults
		settings->sys_fs_path = ldp_private_create_str(".");  // Note, this won't work well on a phone, so embedded devices should set this variable
	}

	if ((ret = access(settings->sys_fs_path, R_OK|W_OK)) == -1) {
		LDPLOG(LOG_ERR, "PS does not have read/write access to the FS at %s", settings->sys_fs_path);
		return (-1);
	}


	// Normally we might do some kind of authentication, punt for now
	// But let's at least start enforcing use of usernames since this becomes
	// very useful down the road
	if (settings->user_id == NULL) {
		// Generate a nice little unique secret:
		LDPLOG(LOG_DEBUG, "ldp_settings_init() set a random user_id");
	 	settings->user_id = ldp_private_generate_name(time(NULL), 12);
	}

	if (settings->user_secret == NULL) {
		// Generate a nice little unique secret:
		LDPLOG(LOG_DEBUG, "ldp_settings_init() set the default password");
	 	settings->user_secret = strdup(ELSECRETOINSEGURO);
	}

	if (settings->user_copyright == NULL) {
		// TBD - Decide where to put these private defaults
		settings->user_copyright = ldp_private_create_str("CC-BY-SA");
	}

	if (settings->user_presence_default == NULL) {
		// TBD - Decide where to put these private defaults
		settings->user_presence_default = ldp_private_create_str("AVAILABLE"); // At some point this would be cool to link into XMPP
	}

	if (settings->user_location_default == NULL) {
		// TBD - Decide where to put these private defaults
		settings->user_location_default = ldp_private_create_str("37.7750N,122.4183W"); // Default to SF, use LAT/LONG coordinates
	}

	// Check that our FS has at least the minimal amount of space left
	// We need to remember that esp. on embedded and mobile devices, we'll hit space constraints
	// that are brick walls, and it can really blow things up to run out of space on the device
	if (settings->sys_fs_max_mb == 0) {
		// TBD - Decide where to put these private defaults
		settings->sys_fs_max_mb = 250;  // This is silly, need to think about best way to map these values.  
	}

	if (settings->sys_fs_min_mb_available == 0) {
		// TBD - Decide where to put these private defaults
		settings->sys_fs_min_mb_available = 100; // This is silly, need to think about best way to map these values. 
	}

	fs_available = ldp_private_get_fs_mb_available(settings->sys_fs_path);
	if (fs_available < settings->sys_fs_min_mb_available) {
		// We don't have enough space to start up.  Let's NOT and report that we didn't.
		LDPLOG(LOG_ERR, "PS does not have have enough space available to start up.  Need %d but found %d", settings->sys_fs_min_mb_available, fs_available);
		return (-1);
	} else {
		LDPLOG(LOG_DEBUG, "fs_available = %lf", fs_available);
	}

	if (settings->user_ccnx_dir == NULL) {
#ifndef __ANDROID__
		if ((settings->user_ccnx_dir = strdup(getenv("HOME"))) == NULL) {
			settings->user_ccnx_dir = "~"; // Not sure why HOME would be unset, but worst case, we should be able to expand ~ to the right place
			LDPLOG(LOG_DEBUG, "getenv(HOME) = %s", settings->user_ccnx_dir);
		} else {
			LDPLOG(LOG_DEBUG, "getenv(HOME) = %s", settings->user_ccnx_dir);
		}
		if (settings->user_ccnx_dir == NULL) {
			//
			// This is not recommended, but just use /var/tmp
			LDPLOG(LOG_ERR, "getenv(HOME) is NULL ... we must be in an unsusual environment.  Fallback to a default");
			settings->user_ccnx_dir = strdup("/var/tmp");
		}
		
		strcat(settings->user_ccnx_dir, strdup("/.ccnx"));
		LDPLOG(LOG_DEBUG, "settings->user_ccnx_dir = %s", settings->user_ccnx_dir);
#else
		// For Android, we shouldn't harcode the full path
		// settings->user_ccnx_dir = strdup(ANDROID_CCNX_USER_DIR_DEFAULT);
		
		settings->user_ccnx_dir = ldp_private_strcat(settings->sys_fs_path, strdup(ANDROID_CCNX_USER_DIR_DEFAULT_SUFFIX));
		LDPLOG(LOG_DEBUG, "settings->user_ccnx_dir = %s", settings->user_ccnx_dir);
		setenv("CCNX_USER_NAME", strdup(settings->user_id), 1); 
		LDPLOG(LOG_DEBUG, "setenv(HOME) = %s", settings->user_id);
		setenv("HOME", strdup(settings->sys_fs_path), 1); 
		LDPLOG(LOG_DEBUG, "setenv(HOME) = %s", settings->sys_fs_path);
#endif
		// Check for directory existence
		if ((ret = access(settings->user_ccnx_dir, R_OK|W_OK)) == -1) {
			//
			// Try to create it
			// If we can't it's time to bail
			//
			if (mkdir(settings->user_ccnx_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0) {
				LDPLOG(LOG_DEBUG, "unable to mkdir() = %s, bailing out!!!!!  Do not continue, abort, no user dir == no keystore == no worky", settings->user_ccnx_dir);
				return (-1);
			} else {
				LDPLOG(LOG_DEBUG, "Successfully called mkdir() of %s", settings->user_ccnx_dir);
				
			}
		} else {
			LDPLOG(LOG_DEBUG, "CCNX User dir %s exists, don't need to create", settings->user_ccnx_dir);
		}

		setenv("CCNX_DIR", strdup(settings->user_ccnx_dir), 1); // XXX HMMM, shouldn't we just check for this first?
		LDPLOG(LOG_DEBUG, "setenv(CCNX_DIR) = %s", settings->user_ccnx_dir);
	}
	if (settings->keystore_uri == NULL) {
		LDPLOG(LOG_DEBUG, "keystore_uri is NULL, use defaults");
		// XXX This causes a core dump on android?
		// settings->keystore_uri = strcat(strdup(settings->user_ccnx_dir), strdup("/.ccnx_keystore")); 
		settings->keystore_uri = ldp_private_strcat(strdup(settings->user_ccnx_dir), "/.ccnx_keystore"); 
		
		LDPLOG(LOG_DEBUG, "Setting settings->keystore_uri = %s", settings->keystore_uri);
	} else {
		LDPLOG(LOG_DEBUG, "Using keystore_uri = %s", settings->keystore_uri);
	}

	if (settings->keylocator_uri == NULL) {
		LDPLOG(LOG_DEBUG, "settings->keylocator_uri is NULL, attempt to use default key signing");
		// Should we set a default?
	}

	//
	// XXX Not used, we should be setting up routes somewhere, but I don't believe here is the
	// appropraite place
	//
	if (settings->ccnd_routes_count == 0){
		// We are expecting at least 2 routes
		// Not sure what we'd do if there was just one route, but we have to trust configuration provided
		settings->ccnd_routes_count = 2;
	}


	if (settings->ccnd_routes == NULL) {
		// XXX Unused
		settings->ccnd_routes = malloc(sizeof(char*)*2); 
		settings->ccnd_routes[0] =  ldp_private_create_str(DEFAULT_LDP_NAMESPACE_ROUTE);
		settings->ccnd_routes[1] = ldp_private_create_str(DEFAULT_LDP_USER_KEYS_ROUTE);
	}

	if (settings->ccnd_port == NULL) {
		settings->ccnd_port = ldp_private_create_str("9695");
	}

	if (settings->ccnd_hostname == NULL) {
		settings->ccnd_hostname = ldp_private_create_str("localhost");
	}

	return (0);
} /* Initialize Settings using the TLDPSettings */

int ldp_write_peer_metadata_from_bytes(char *peer_id_common_name, char *metadata, char *access_control_obj) {
	int status = 0;
	LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() begin");
	struct ccn_charbuf *content_uri;

	char uri[256]; // XXX Increase this, add def in headers

	char *ccn_prefix = NULL;
	unsigned long metadata_bytes_length = 0;
	if (peer_id_common_name == NULL) {
		LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() ERROR NULL content_name passed to ldp_write_peer_metadata_from_bytes()");
		status = -1;
	}

	if (metadata == NULL) {
		// TODO: Implement defaults
		LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() ERROR NULL metadata passed to ldp_write_peer_metadata_from_bytes()");
		status = -1;
	} else {
		metadata_bytes_length = strlen(metadata);
	}

	if (ccn_prefix == NULL) {
		LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() NULL ccn_prefix passed to ldp_write_peer_metadata_from_bytes()");
		ccn_prefix = strdup(DEFAULT_LDP_PEERGROUP_PEERS_PEERID_METADATA_1_0_0);
	}

	if (access_control_obj == NULL) {
		LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() NULL access_control_obj passed to ldp_write_peer_metadata_from_bytes(), ignore");
	}

	if ((content_uri = ccn_charbuf_create()) == NULL) {
		LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() ERROR cannot ccn_charbuf_create()");
		status = -1;
	}

	LDPLOG(LOG_DEBUG, "Some Useful CCNx ENV\n==================");

	if (getenv("HOME") != NULL) {
		LDPLOG(LOG_DEBUG, "getenv(HOME) = %s", strdup(getenv("HOME")));
	}

	if (getenv("CCNX_DIR") != NULL) {
		LDPLOG(LOG_DEBUG, "getenv(CCNX_DIR) = %s", strdup(getenv("CCNX_DIR")));
	}

	if (getenv("CCNX_USER_NAME") != NULL) {
		LDPLOG(LOG_DEBUG, "getenv(CCNX_USER_NAME) = %s", strdup(getenv("CCNX_USER_NAME")));
	}

	if (getenv("CCNX_USER_NAMESPACE_PREFIX") != NULL) {
		LDPLOG(LOG_DEBUG, "getenv(CCNX_USER_NAMESPACE_PREFIX = %s", strdup(getenv("CCNX_USER_NAMESPACE_PREFIX")));
	}

	// 
	// 1. ccnush the Peer Metadata (i.e. push the image into CCN)

	//
	// We potentially want to have a real pipeline processing such things so work can be split up, or at least, we can queue
	// up requests so that each ccnush call is asynchronous.
	//

	if (status == 0) {
		// ccnush metadata
		// Create peerID in the LDP_DEFAULT_PEERGROUP_PEERS
		// XXX We really want to be writing this under: LDP_DEFAULT_PEERGROUP_PEERS_PEERID_METADATA_1_0_0
		sprintf(uri, ccn_prefix, peer_id_common_name);
		LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() to name uri = %s", uri);

		if (ccn_name_from_uri(content_uri, uri) <= 0) {
			LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() failed to create ccn_name_from_uri for %s%s", DEFAULT_LDP_PEERGROUP_PEERS, peer_id_common_name);
			status = -1;
		} else {
			// LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() created ccn_name_from_uri() content_name = %s, ret=%d", ccn_charbuf_as_string(content_uri), ret);
			/* if (ldp_private_ccnush_data(content_uri, metadata, metadata_bytes_length, 60000L, LDP_DEFAULT_SCOPE) < 0) {
				status = -1;
			} */
			
			if (ldp_private_ccnush_data_with_freshness(content_uri, metadata, metadata_bytes_length, 60000L, DEFAULT_LDP_SCOPE, LDP_CONTENT_FRESHNESS_IN_SEC_DEFAULT, FALSE) < 0) {
				status = -1;
			}

			if (status == 0) {
				 LDPLOG(LOG_DEBUG, "ldp_write_peer_metadata_from_bytes() success");
			} else {
				LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() failed");
			}
		} 

		// Cleanup names
		ccn_charbuf_destroy(&content_uri);
	} else {
		LDPLOG(LOG_ERR, "ldp_write_peer_metadata_from_bytes() bailing because of earlier errors");
	}
 	return status;
} /* Write metadata from buffer */

char * ldp_get_peer_metadata_as_bytes(char *remote_peer_id_common_name, size_t *data_len, char *access_control_obj) {
	int status = 0;
	LDPLOG(LOG_DEBUG, "ldp_get_peer_metadata_as_bytes() begin");
	char* bytes = NULL;
	char uri[128];

	if (remote_peer_id_common_name == NULL) {
		LDPLOG(LOG_ERR, "ldp_get_peer_metadata_as_bytes() ERROR NULL content_name passed");
		status = -1;
	}

	if (access_control_obj == NULL) {
		LDPLOG(LOG_DEBUG, "ldp_get_peer_metadata_as_bytes() NULL access_control_obj passed to , ignore");
	}

	sprintf(uri, DEFAULT_LDP_PEERGROUP_PEERS_PEERID_METADATA_1_0_0, strdup(remote_peer_id_common_name));
  
	bytes = ldp_private_ccnsip_data(uri, LDP_CCN_GET_TIMEOUT_IN_MILLIS_DEFAULT, DEFAULT_LDP_SCOPE, data_len);
  	
	return bytes;
}

char** ldp_get_peers(int *peer_names_length, char *access_control_obj) {
	char **peer_names = {0};

	LDPLOG(LOG_DEBUG, "ldp_get_peers() begin");

	if (access_control_obj == NULL) {
		LDPLOG(LOG_DEBUG, "ldp_get_peers() NULL access_control_obj passed, ignore");
	}

	peer_names = ldp_private_get_ccn_child_name_components_under_name(DEFAULT_LDP_PEERGROUP_PEERS, peer_names_length);
	LDPLOG(LOG_DEBUG, "ldp_get_peers(), we found %d names", *peer_names_length);
	if (peer_names != NULL) {
		LDPLOG(LOG_DEBUG, "ldp_get_peers(), first element: peer_names[0]=%s", peer_names[0]);
	} else {
		LDPLOG(LOG_ERR, "ldp_get_peers() got NULL data back, need to handle error");
	}
	return peer_names;
}

int ldp_settings_set_sys_fs_path(TLDPSettings *settings, char *path) {
	if ((settings == NULL) || (path == NULL)) {
		LDPLOG(LOG_ERR, "ldp_settings_set_sys_fs_path() TLDPSettings are NULL");
		return -1;
	}
	settings->sys_fs_path = strdup(path);
  	return 0;
}

int ldp_settings_set_sys_logfile(TLDPSettings *settings, char *path) {
	if ((settings == NULL) || (path == NULL)) {
		LDPLOG(LOG_ERR, "ldp_settings_set_sys_logfile() TLDPSettings are NULL");
		return -1;
	}
	settings->sys_logfile = strdup(path);
  	return 0;
}

int ldp_settings_set_user_id(TLDPSettings *settings, char *user_id) {
	if ((settings == NULL) || (user_id == NULL)) {
		LDPLOG(LOG_ERR, "ldp_settings_set_sys_fs_path() TLDPSettings are NULL");
		return -1;
	}
	settings->user_id = strdup(user_id); // XXX This doesn't make sense?  Why do this?  Should be user_id
  	return 0;
}

int ldp_settings_set_keystore_uri(TLDPSettings *settings, char *keystore_uri) {
	if ((settings == NULL) || (keystore_uri == NULL)) {
		LDPLOG(LOG_ERR, "ldp_settings_set_keystore_uri() TLDPSettings are NULL");
		return -1;
	}
	settings->keystore_uri = strdup(keystore_uri);
  	return 0;	
}

int ldp_write_peer_metadata_from_json(char *peer_id_common_name, TJson* json, char *access_control_obj) {
	return ldp_write_peer_metadata_from_bytes(peer_id_common_name, cJSON_Print(json), access_control_obj);
}

TJson* ldp_get_peer_metadata_as_json(char *remote_peer_id_common_name, size_t *data_length, char *access_control_obj) {
	const char* data = ldp_get_peer_metadata_as_bytes(remote_peer_id_common_name, data_length, access_control_obj);
	TJson* jsonroot = cJSON_Parse(data);
	if (!jsonroot) {
		LDPLOG(LOG_ERR, "ldp_get_peer_metadata_as_json cannot parse JSON");
		return NULL;
	} else {
		return jsonroot;
	}
}

TJson* ldp_get_peers_as_json(int *peer_names_length, char *access_control_obj) {
	const char* data = ldp_get_peers_as_json(peer_names_length, access_control_obj);
	TJson* jsonroot = cJSON_Parse(data);
	if (!jsonroot) {
		LDPLOG(LOG_ERR, "ldp_get_peers_as_json cannot parse JSON");
		return NULL;
	} else {
		return jsonroot;
	}
}

/*
 * Utility Methods
 */
//
// Simple Syslog wrapper.  Attribution: http://bit.ly/Qibo5r
//
/* Private storage for the current mask */
static int ldp_log_consolemask;

int ldp_log_console_setlogmask(int mask) {
  int oldmask = ldp_log_consolemask;
  if(mask == 0)
    return oldmask; /* POSIX definition for 0 mask */
  ldp_log_consolemask = mask;
  return oldmask;
}

#ifdef __ANDROID__
void ldp_log_to_android_logcat(int priority, const char *format, ...) {
	// This by itself doesn't work properly with the varargs.  
	va_list arglist;
	va_start(arglist, format);
	__android_log_vprint(ANDROID_LOG_DEBUG, TAG, format, arglist);
	va_end(arglist);
}
#endif

// Might make sense to add the __FUNCTION__ and __LINE__ macro
void ldp_log_console(int priority, const char *format, ...) {
  va_list arglist;
  const char *loglevel;
  va_start(arglist, format);

  /* Return on MASKed log priorities */
  if (LOG_MASK(priority) & ldp_log_consolemask)
    return;

  switch(priority)
  {
  case LOG_ALERT:
    loglevel = "ALERT: ";
    break;
  case LOG_CRIT:
    loglevel = "CRIT: ";
    break;
  case LOG_DEBUG:
    loglevel = "DEBUG: ";
    break;
  case LOG_EMERG:
    loglevel = "EMERG: ";
    break;
  case LOG_ERR:
    loglevel = "ERR: ";
    break;
  case LOG_INFO:
    loglevel = "INFO: ";
    break;
  case LOG_NOTICE:
    loglevel = "NOTICE: ";
    break;
  case LOG_WARNING:
    loglevel = "WARNING: ";
    break;
  default:
    loglevel = "UNKNOWN: ";
    break;
  }
  // TODO - should make this support STDERR
  printf("%s", loglevel);
  vprintf(format, arglist);
  printf("\n");
  va_end(arglist);
}

/*
 * private method implementations
 */
// XXX Get rid of this.  Candidate to replace with bstring methods
char *ldp_private_create_str(const char *constr) {
	char * newstr;

	if ((newstr = malloc(strlen(constr) + 1)) == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_create_str() could not allocate str memory");
		return NULL;
	}

	strcpy(newstr, constr);

	return newstr;
}

char *ldp_private_strcat(char *s1, char *s2) {
	size_t s1len;
	size_t s2len;
	char *catbuf;

	if ((s1 == NULL) || (s2 == NULL)) {
		LDPLOG(LOG_ERR, "ldp_private_strcat() passed NULL args");
		return NULL;
	}
	s1len = strlen(s1);
	s2len = strlen(s2);

	LDPLOG(LOG_DEBUG, "s1 is length=%d", s1len);
	LDPLOG(LOG_DEBUG, "s2 is length=%d", s2len);

	if ((catbuf = malloc(s1len + s2len + 1)) == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_strcat() cannot malloc()");
		return NULL;
	}
	memset(catbuf, '\0', (s1len + s2len + 1));
	memcpy(catbuf, s1, s1len);
	memcpy(catbuf+s1len, s2, s2len + 1);
	LDPLOG(LOG_DEBUG, "ldp_private_strcat() returning %s from s1=%s, s2=%s", catbuf, s1, s2);
	return catbuf;
}

char *ldp_private_generate_name(uint seed, int length) {
	// Do naive setup for now.  Change this to generate a set from ASCII printable character set, and store the initial set once created
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int alphabet_size = sizeof(alphabet);
	int i;
	srand(seed);
	char *seq = malloc(length + 1);

	// TODO Would be nice to let length be a negative argument to indicate random length, and then set length to some value between 8-32

	for (i = 0; i < length; i++) {
		seq[i] = alphabet[rand()%alphabet_size];
	}
	seq[length] = '\0'; // Terminate sequence

	return seq;
}


int ldp_private_ccnush_data(struct ccn_charbuf *cname, char *data, unsigned long data_length, long timeout_in_millis, int scope) {
	//
	// Default to no staleness for this method
	//
	return ldp_private_ccnush_data_with_freshness(cname, data, data_length, timeout_in_millis, scope, -1, TRUE);
}

int ldp_private_ccnush_data_with_freshness(struct ccn_charbuf *cname, char *data, unsigned long data_length, long timeout_in_millis, int scope, int freshness_in_sec, int use_repo) {
// ccnush (push) content to repo
	int blocksize = SEQWRITER_BLOCKSIZE_DEFAULT; // TODO: presumably we want the 
												 // blocksize to be configurable,
												 // or even adaptive based on some other factors
						  						 // seqwriter uses 4096 as default, btw
	int breakloop = 0;
	int ret;
	int res;
	int i;
	int status = 0;
	int useslow = 1; // Forces to use our old loop

	struct ccn_seqwriter *seqw;
	ssize_t read_res;
	size_t blockread;
	unsigned char *buf = NULL;
	struct ccn_charbuf *tpl = {0};
	struct ccn_charbuf *name_v;
	struct ccn *h = NULL;
	// XXX May want to remove this, I don't think we'll need it
	// unsigned long expected_write = data_length;
	unsigned long seqw_data_written = 0;

	if (data == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() data is NULL");
		return -1;
	}

	if (data_length <=0) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() data_length is zero or less, return");
		return -1;
	}

	if (cname == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() cname is NULL, return");
		return -1;
	}

	if ((h = ccn_create()) == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() ccn_create() is NULL");
		return -1;
	}

	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_connect()");
	if ((ccn_connect(h, ldp_private_connection_name)) < 0) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() ccn_connect() failed");
		ccn_destroy(&h);
		return -1;
	}

	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_seqw_create()");
	// We should probably be checking to see if we have a handle before we do this
	seqw = ccn_seqw_create(h, cname);

	if (seqw == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() can't create ccn_seqwriter_create() for uri: %s", ccn_charbuf_as_string(cname));
		return -1;
	}
	
	// Get the Start Write Seq
	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_seqw_set_block_limits()");
	ccn_seqw_set_block_limits(seqw, blocksize, blocksize);

	if (freshness_in_sec > -1) {
		LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() setting freshness expiry to %d sec", freshness_in_sec);
        ccn_seqw_set_freshness(seqw, freshness_in_sec);
    }
	
	// use_repo = TRUE;
	// Only write to repo if instructed
	if (use_repo) {
		if ((name_v = ccn_charbuf_create()) == NULL) {
			LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() can't create ccn_charbuf_create()");
			return -1;
		}
		ccn_seqw_get_name(seqw, name_v);
		ccn_name_from_uri(name_v, "%C1.R.sw");
		ccn_name_append_nonce(name_v);
		LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() calling ldp_private_startwrite_tpl()");
		tpl = ldp_private_startwrite_tpl(scope);
		LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_get()");
		ret = ccn_get(h, name_v, tpl, timeout_in_millis, NULL, NULL, NULL, 0);
	 	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_charbuf_destroy(&tpl)");
	 	ccn_charbuf_destroy(&tpl);
	 	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() about to call ccn_charbuf_destroy(&name_v)");
		ccn_charbuf_destroy(&name_v);
		if (ret < 0) {
			LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() unable to ccn_get() the Start Write Sequence");
			return -1;
		}
	}

	// attribution: Borrow this loop from ccnseqwriter, modify to use data we already have buffered
	blockread = 0;
	buf = calloc(1, blocksize);
	if (buf == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() unable to calloc()");
		return -1;
	}

	if (useslow) {
		LDPLOG(LOG_DEBUG, "Using slow loop");
		for (i = 0; breakloop != 1;i++) {
			read_res = 0; // This is a magic replacement for the read() sys call
			while (blockread < blocksize) {
				if (ccn_run(h, 1) < 0) {
					// XXX We have a problem
					LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() can't connect to ccnd");
					return -1; // XXX We should cleanup first
				}
				// This is a magic replacement for the read() sys call
				if (data_length > blocksize) {
					blockread = blocksize;
					read_res = blockread;
				} else {
					blockread = blocksize;
					read_res = data_length;
				}
				
				data_length = data_length - read_res;
				memmove(buf, data, read_res);
				data = data + read_res;
				// End - magic replacement for the read() sys call
				LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() data length = %d", data_length);
				// read_res = read(0, buf + blockread, blocksize - blockread);
			}
			// LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() read_res = %d", read_res);
			if (read_res == 0) {
				LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() has no more to read");
				breakloop = 1;
			} else if (read_res < 0)  {
				LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() error reading sequence");
				status = -1;
				breakloop = 1;
			} else {
				// LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() calling ccn_seqw_write() = %d bytes", blockread);
				ret = ccn_seqw_write(seqw, buf, blockread);
				while (ret == -1) {
					if (ccn_run(h, 100) < 0) { // Delay while we wait for data?
						LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() can't connect to ccnd");
					}  
					ret = ccn_seqw_write(seqw, buf, blockread);
				}
				if (ret != blockread) {
					// Don't do abort()
					LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() catastrophic error reading sequence");
					status = -1;
					breakloop = 1;
				}
				seqw_data_written += ret;
				blockread = 0;
			}
			// We'll drop out here if breakloop == 1
		}
		LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() run loop wrote %d", seqw_data_written);
	} else {
		// XXX This is the original loop, but is set up to read from stdin
		for (i = 0;; i++) {
	        while (blockread < blocksize) {
	            if (ccn_run(h, 1) < 0) {
	                LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() Lost connection to ccnd: %s\n", strerror(ccn_geterror(h)));
	                return -1;
	            }
	            read_res = read(0, buf + blockread, blocksize - blockread);
	            if (read_res == 0)
	                goto cleanup;
	            if (read_res < 0) {
	                // perror("read");
	                status = 1;
	                goto cleanup;
	            }
	            blockread += read_res;
	        }
	        res = ccn_seqw_write(seqw, buf, blockread);
	        while (res == -1) {
	            if (ccn_run(h, 100) < 0) {
	                LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() Lost connection to ccnd: %s\n", strerror(ccn_geterror(h)));
	                return -1;
	            }
	            res = ccn_seqw_write(seqw, buf, blockread);
	        }
	        if (res != blockread) {
	        	LDPLOG(LOG_ERR, "ldp_private_ccnush_data_with_freshness() ccn_seqw_write did a short write or something");
	        	return -1;
	            // abort(); /* hmm, ccn_seqw_write did a short write or something */
	        }
	        blockread = 0;
	    }
	    
	cleanup:
	    // flush out any remaining data and close
	    if (blockread > 0) {
	        res = ccn_seqw_write(seqw, buf, blockread);
	        while (res == -1) {
	            if (ccn_run(h, 100) < 0) {
	                LDPLOG(LOG_ERR, "Lost connection to ccnd: %s\n", strerror(ccn_geterror(h)));
	                return -1;
	            }
	            res = ccn_seqw_write(seqw, buf, blockread);
	        }
	    }
	}

	// Using this as a safeguard to check whether we wrote enough data or too much
	// XXX Should we remove this?
	/* if (expected_write != seqw_data_written) {
		status = -1;
	} */
	// Cleanup
	// Flush remaining data
	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() calling ccn_seqw_close()");
	ccn_seqw_close(seqw);
	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() run for a second");
	ccn_run(h, 1);
	if (tpl != NULL) {
		ccn_charbuf_destroy(&tpl);
	}

	if (buf != NULL) {
		LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() free(buf)");
		free(buf);
	}
	buf = NULL;
	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() ccn_disconnect()");
	ccn_disconnect(h);
	LDPLOG(LOG_DEBUG, "ldp_private_ccnush_data_with_freshness() ccn_destroy()");
	ccn_destroy(&h);
	return status;
}

double ldp_private_get_fs_mb_available(char * path) {
	const unsigned int MB = 1024*1024;
	unsigned long blocks_free = 0;
	unsigned long free_size = 0;

	#ifndef __ANDROID__
	struct statvfs s_fs; // Described here: http://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstatvfs.h.html
	if (statvfs(path, &s_fs) == 0) {
		free_size = s_fs.f_frsize;
		blocks_free = s_fs.f_bfree;
	#else
	struct statfs s_fs; // http://linux.about.com/library/cmd/blcmdl2_statfs.htm
	if (statfs(path, &s_fs) == 0) {
		free_size = s_fs.f_bfree;
		blocks_free = s_fs.f_bsize;
	#endif
	} else {
		LDPLOG(LOG_ERR, "Unable to statvfs() path: %s", path);
		return -1;
	}
	// TODO: Double check the math here and make sure this is accurate
 
	LDPLOG(LOG_DEBUG, "f_frsize = %ld, f_bfree = %ld, MB=%d, total bytes: %ld", free_size, blocks_free, MB, (free_size * blocks_free));
	LDPLOG(LOG_DEBUG, "MBytes available on path %s: %ld", path, (free_size * blocks_free)/MB);
	return (free_size * blocks_free)/MB; // Should we apply ceil?
}

/* ccnsip the data (get it), won't block on data, loosely based on ccnpeek */
char *ldp_private_ccnsip_data(char *content_name_uri, long timeout_in_millis, int scope, size_t *data_length) {
	struct ccn_charbuf *content_name = NULL;;
	struct ccn_charbuf *tpl = NULL;;
	struct ccn *h = NULL;
	int res;
	size_t length;
    struct ccn_charbuf *resultbuf = NULL;
    struct ccn_parsed_ContentObject pcobuf = { 0 };

    int allow_stale = 0; // We won't allow stale data
    int content_only = 1; // Only get the content, not the ccnb
    // We may want to default scope to -1
    // scope = -1;
    scope = -1;
    const unsigned char *ptr = NULL;
    int resolve_version = 1; // Activate version resolution
	 
    const unsigned lifetime_default = CCN_INTEREST_LIFETIME_SEC << 12;
    unsigned lifetime_l12 = lifetime_default;
    int get_flags = 0;
	content_name = ccn_charbuf_create();

	if (resolve_version == 0)
		resolve_version = CCN_V_HIGHEST;
	else
		resolve_version = CCN_V_HIGH;
	if (content_name == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() can't create ccn_charbuf_create()");
		return NULL;
	}

	if (content_name_uri == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() content_name_uri is NULL");
		return NULL;
	}

    res = ccn_name_from_uri(content_name, content_name_uri);

    if (res < 0) {
        LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() bad ccn URI: %s\n", content_name_uri);
        return NULL;
    }

    h = ccn_create();
    res = ccn_connect(h, ldp_private_connection_name);
    if (res < 0) {
        LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() error connecting to CCND, is it running?");
        return NULL;
    }

    LDPLOG(LOG_DEBUG, "ldp_private_ccnsip_data() timeout_in_millis = %d", timeout_in_millis);

    //
    // We won't need this, leave it in case we tweak scope
    //
	if (allow_stale || lifetime_l12 != lifetime_default || scope != -1) {
        tpl = ccn_charbuf_create();
        ccn_charbuf_append_tt(tpl, CCN_DTAG_Interest, CCN_DTAG);
        ccn_charbuf_append_tt(tpl, CCN_DTAG_Name, CCN_DTAG);
        ccn_charbuf_append_closer(tpl); /* </Name> */
		if (allow_stale) {
			ccn_charbuf_append_tt(tpl, CCN_DTAG_AnswerOriginKind, CCN_DTAG);
			ccnb_append_number(tpl, CCN_AOK_DEFAULT | CCN_AOK_STALE);
			ccn_charbuf_append_closer(tpl); /* </AnswerOriginKind> */
		}
        if (scope != -1) {
            ccnb_tagged_putf(tpl, CCN_DTAG_Scope, "%d", scope);
        }
		if (lifetime_l12 != lifetime_default) {
			/*
			 * Choose the interest lifetime so there are at least 3
			 * expressions (in the unsatisfied case).
			 */
			unsigned char buf[3] = { 0 };
			int i;
			for (i = sizeof(buf) - 1; i >= 0; i--, lifetime_l12 >>= 8)
				buf[i] = lifetime_l12 & 0xff;
			ccnb_append_tagged_blob(tpl, CCN_DTAG_InterestLifetime, buf, sizeof(buf));
		}
        ccn_charbuf_append_closer(tpl); /* </Interest> */
    }
    resultbuf = ccn_charbuf_create();
    if (resolve_version != 0) {
        res = ccn_resolve_version(h, content_name, resolve_version, 500);
        if (res >= 0) {
            ccn_uri_append(resultbuf, content_name->buf, content_name->length, 1);
            LDPLOG(LOG_DEBUG, "version== %s\n", ccn_charbuf_as_string(resultbuf));
            resultbuf->length = 0;
        }
    }
    res = ccn_get(h, content_name, tpl, timeout_in_millis, resultbuf, &pcobuf, NULL, get_flags);
    if (res >= 0) {
        ptr = resultbuf->buf;
        length = resultbuf->length;
        if (content_only)
            ccn_content_get_value(ptr, length, &pcobuf, &ptr, &length);
        /* if (data_length > 0) {
            res = fwrite(ptr, length, 1, stdout) - 1;
        } */
        if (length <= 0) {
        	LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() read ZERO data");
        	length = 0;
        	ptr = NULL;
        } else {
        	LDPLOG(LOG_DEBUG, "ldp_private_ccnsip_data() read %d", length);
        }
    } else {
    	LDPLOG(LOG_ERR, "ldp_private_ccnsip_data() no results");
    }
    *data_length = length;
    ccn_charbuf_destroy(&resultbuf);
    ccn_charbuf_destroy(&tpl);
    ccn_charbuf_destroy(&content_name);
    ccn_destroy(&h);

    return ptr;
}


// Technique applied from ccncat
struct ccn_charbuf *ldp_private_interest_tpl(int allow_stale, int scope) {
	struct ccn_charbuf *tpl = NULL;
	tpl = ccn_charbuf_create();
	ccn_charbuf_append_tt(tpl, CCN_DTAG_Interest, CCN_DTAG);
	ccn_charbuf_append_tt(tpl, CCN_DTAG_Name, CCN_DTAG);
	ccn_charbuf_append_closer(tpl);
	ccn_charbuf_append_tt(tpl, CCN_DTAG_MaxSuffixComponents, CCN_DTAG);
	ccnb_append_number(tpl, 1);
	ccn_charbuf_append_closer(tpl);
	if (allow_stale) {
		ccn_charbuf_append_tt(tpl, CCN_DTAG_AnswerOriginKind, CCN_DTAG);
		ccnb_append_number(tpl, CCN_AOK_DEFAULT | CCN_AOK_STALE);
		ccn_charbuf_append_closer(tpl);
	}
	if (fabs(scope) < 3) {
		ccnb_tagged_putf(tpl, CCN_DTAG_Scope, "%d", scope);
	}
	ccn_charbuf_append_closer(tpl);
	return tpl;
}

//
// Utility Items below are inspired by ccnls
//
struct ldp_private_upcalldata {
    int magic; /* 856372 */
    long *counter;
    unsigned warn;
    unsigned option;
    int n_excl;
    int scope;
    int flags;
    int allow_stale;
    struct ccn_charbuf **excl; /* Array of n_excl items */
};


static int ldp_private_namecompare(const void *a, const void *b)
{
    const struct ccn_charbuf *aa = *(const struct ccn_charbuf **)a;
    const struct ccn_charbuf *bb = *(const struct ccn_charbuf **)b;
    int ans = ccn_compare_names(aa->buf, aa->length, bb->buf, bb->length);
    if (ans == 0)
        LDPLOG(LOG_ERR, "ldp_private_namecompare() issue %d\n", __LINE__);
    return (ans);
}

enum ccn_upcall_res ldp_private_namelookup_incoming_content(
    struct ccn_closure *selfp,
    enum ccn_upcall_kind kind,
    struct ccn_upcall_info *info) {

    struct ccn_charbuf *c = NULL;
    struct ccn_charbuf *comp = NULL;
    struct ccn_charbuf *uri = NULL;
    struct ccn_charbuf *templ = NULL;
    const unsigned char *ccnb = NULL;
    size_t ccnb_size = 0;
    struct ccn_indexbuf *comps = NULL;
    int matched_comps = 0;
    int res;
    int i;
    struct ldp_private_upcalldata *data = selfp->data;
    
    if (data->magic != 856372) 
    	return(CCN_UPCALL_RESULT_ERR); /* XXX Don't abort(); */
    if (kind == CCN_UPCALL_FINAL)
        return(CCN_UPCALL_RESULT_OK);
    if (kind == CCN_UPCALL_INTEREST_TIMED_OUT)
        return(CCN_UPCALL_RESULT_REEXPRESS);
    if (kind == CCN_UPCALL_CONTENT_UNVERIFIED) {
        if ((data->option & 0x00) != 0)
        return(CCN_UPCALL_RESULT_VERIFY);
        }
    else if (kind != CCN_UPCALL_CONTENT) return(CCN_UPCALL_RESULT_ERR); /* XXX Don't abort(); */
    
    ccnb = info->content_ccnb;
    ccnb_size = info->pco->offset[CCN_PCO_E];
    comps = info->content_comps;
    matched_comps = info->pi->prefix_comps;
    c = ccn_charbuf_create();
    uri = ccn_charbuf_create();
    templ = ccn_charbuf_create();
    /* note that comps->n is 1 greater than the number of explicit components */
    if (matched_comps > comps->n) {
        ccn_uri_append(c, ccnb, ccnb_size, 1);
        LDPLOG(LOG_ERR, "ldp_private_namelookup_incoming_content(), fatal error  %s\n", ccn_charbuf_as_string(uri));
        return(CCN_UPCALL_RESULT_ERR);
    }
    data->counter[0]++;
    /* Recover the same prefix as before */
    ccn_name_init(c);
    res = ccn_name_append_components(c, info->interest_ccnb,
                                     info->interest_comps->buf[0],
                                     info->interest_comps->buf[matched_comps]);
    if (res < 0) return(CCN_UPCALL_RESULT_ERR); /* XXX Don't abort(); */
    
    comp = ccn_charbuf_create();
    ccn_name_init(comp);
    if (matched_comps + 1 == comps->n) {
        /* Reconstruct the implicit ContentObject digest component */
        ccn_digest_ContentObject(ccnb, info->pco);
        ccn_name_append(comp, info->pco->digest, info->pco->digest_bytes);
    }
    else if (matched_comps < comps->n) {
        ccn_name_append_components(comp, ccnb,
                                   comps->buf[matched_comps],
                                   comps->buf[matched_comps + 1]);
    }
    res = ccn_uri_append(uri, comp->buf, comp->length, 0);
    if (res < 0 || uri->length < 1)
        LDPLOG(LOG_ERR, "ldp_private_namelookup_incoming_content() Fatal Error:  line %d res=%d\n", __LINE__, res);
    else {
        if (uri->length == 1)
            ccn_charbuf_append(uri, ".", 1);
        global_peer_names[global_peer_names_length] = strdup(ccn_charbuf_as_string(uri) + 1);
       	global_peer_names_length++;
        LDPLOG(LOG_DEBUG, (ccn_charbuf_as_string(uri) + 1));
    }
    ccn_charbuf_append_tt(templ, CCN_DTAG_Interest, CCN_DTAG);
    ccn_charbuf_append(templ, c->buf, c->length); /* Name */
    if (matched_comps == comps->n) {
        /* The interest supplied the digest component */
        ccn_charbuf_destroy(&comp);
        /*
         * We can't rely on the Exclude filter to keep from seeing this, so 
         * say that we need at least one more name component.
         */
        ccn_charbuf_append_tt(templ, CCN_DTAG_MinSuffixComponents, CCN_DTAG);
        ccn_charbuf_append_tt(templ, 1, CCN_UDATA);
        ccn_charbuf_append(templ, "1", 1);
        ccn_charbuf_append_closer(templ); /* </MinSuffixComponents> */
    }
    else {
        data->excl = realloc(data->excl, (data->n_excl + 1) * sizeof(data->excl[0]));
        data->excl[data->n_excl++] = comp;
        comp = NULL;
    }
    qsort(data->excl, data->n_excl, sizeof(data->excl[0]), &ldp_private_namecompare);
    ccn_charbuf_append_tt(templ, CCN_DTAG_Exclude, CCN_DTAG);
    for (i = 0; i < data->n_excl; i++) {
        comp = data->excl[i];
        if (comp->length < 4) return(CCN_UPCALL_RESULT_ERR); /* XXX Don't abort(); */
        ccn_charbuf_append(templ, comp->buf + 1, comp->length - 2);
    }
    comp = NULL;
    ccn_charbuf_append_closer(templ); /* </Exclude> */

    // XXX I think we can exclude this
    ccnb_tagged_putf(templ, CCN_DTAG_AnswerOriginKind, "%d", CCN_AOK_CS);
    if (data->scope > -1)
       ccnb_tagged_putf(templ, CCN_DTAG_Scope, "%d", data->scope);
    ccn_charbuf_append_closer(templ); /* </Interest> */
    if (templ->length > data->warn) {
        LDPLOG(LOG_WARNING, "ldp_private_namelookup_incoming_content() Interest packet is %d bytes\n", (int)templ->length);
        data->warn = data->warn * 8 / 5;
    }
    ccn_express_interest(info->h, c, selfp, templ);
    ccn_charbuf_destroy(&templ);
    ccn_charbuf_destroy(&c);
    ccn_charbuf_destroy(&uri);
    return(CCN_UPCALL_RESULT_OK);
}

char ** ldp_private_get_ccn_child_name_components_under_name(char *uri_prefix, int *number_of_names) {
	struct ccn *handle = NULL;
	struct ccn_charbuf *prefix = NULL;
	struct ccn_charbuf *templ = NULL;
	struct ldp_private_upcalldata *data = NULL;

	global_peer_names_length = 0;
	memset(global_peer_names, 0, MAX_GLOBAL_PEERS_LENGTH);

	int i;
	int n;
	int res;
	int allow_stale = 0;
	long counter = 0;

	struct ccn_closure *cl = 0;
	int timeout_millis = 500;

	if (uri_prefix == NULL) {
		LDPLOG(LOG_ERR, "ldp_private_get_ccn_child_name_components_under_name() missing uri prefix");
		return NULL;
	}

    prefix = ccn_charbuf_create();
    res = ccn_name_from_uri(prefix, uri_prefix);
    if (res < 0) {
    	LDPLOG(LOG_ERR, "ldp_private_get_ccn_child_name_components_under_name() malformed name, please provide a well-formed uri prefix");
		return NULL;
    }
    
    handle = ccn_create();
    //
    // If you leave the second argument NULL, this fails on Android
    //
    if (ccn_connect(handle, ldp_private_connection_name) == -1) {
        LDPLOG(LOG_ERR, "Could not connect to ccnd");
        return NULL;
    }
    
    data = calloc(1, sizeof(*data));
    data->magic = 856372;
    data->warn = 1492;
    data->counter = &counter;
    data->option = 0;
    data->scope = -1;
    data->allow_stale = allow_stale;
    // data->flags |= ALLOW_STALE;

    cl = calloc(1, sizeof(*cl));
    cl->p = &ldp_private_namelookup_incoming_content;
    cl->data = data;
    if (data->scope > -1) {
        templ = ccn_charbuf_create();
        ccn_charbuf_append_tt(templ, CCN_DTAG_Interest, CCN_DTAG);
        ccn_charbuf_append_tt(templ, CCN_DTAG_Name, CCN_DTAG);
        ccn_charbuf_append_closer(templ); /* </Name> */
        ccnb_tagged_putf(templ, CCN_DTAG_Scope, "%d", data->scope);
        ccn_charbuf_append_closer(templ); /* </Interest> */
    }
    ccn_express_interest(handle, prefix, cl, templ);
    ccn_charbuf_destroy(&templ);
    cl = NULL;
    data = NULL;
    for (i = 0;; i++) {
        n = counter;
        ccn_run(handle, timeout_millis); /* stop if we run dry for 1/2 sec */
        /* XXX Don't need to flush */
        /* fflush(stdout); */
        if (counter == n)
            break;
    }
    ccn_destroy(&handle);
    ccn_charbuf_destroy(&prefix);
    *number_of_names = global_peer_names_length;
    LDPLOG(LOG_DEBUG, "global_peer_names_length=%d,NULL global_peer_names[0]=%s", global_peer_names_length, global_peer_names[0]);

	return global_peer_names;
}

// Technique applied from ccnseqwriter
struct ccn_charbuf *ldp_private_startwrite_tpl(int scope) {
	struct ccn_charbuf *tpl = NULL;
	tpl = ccn_charbuf_create();
	ccn_charbuf_append_tt(tpl, CCN_DTAG_Interest, CCN_DTAG);
	ccn_charbuf_append_tt(tpl, CCN_DTAG_Name, CCN_DTAG);
	ccn_charbuf_append_closer(tpl);
	if (fabs(scope) < 3) {
		ccnb_tagged_putf(tpl, CCN_DTAG_Scope, "%d", scope);
	}
	ccn_charbuf_append_closer(tpl);
	return tpl;	
}
