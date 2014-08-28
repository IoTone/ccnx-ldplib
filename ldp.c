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
					LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->ccnd_routes[%d])", i);
					free(ldpobj->ccnd_routes[i]);
				}
			}
		}

		if (ldpobj->topo_prefix != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->topo_prefix)");
			free(ldpobj->topo_prefix);
		}

		if (ldpobj->user_id != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->user_id)");
			free(ldpobj->user_id);
		}

		if (ldpobj->user_secret != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->user_secret)");
			free(ldpobj->user_secret);
		}

		if (ldpobj->user_copyright != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->user_copyright)");
			free(ldpobj->user_copyright);
		}

		if (ldpobj->user_location_default != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->user_location_default)");
			free(ldpobj->user_location_default);
		}

		if (ldpobj->sys_fs_path != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->sys_fs_path)");
			free(ldpobj->sys_fs_path);
		}

		if (ldpobj->user_presence_default != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->user_presence_default)");
			free(ldpobj->user_presence_default);
		}

		if (ldpobj->ccnd_hostname != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->ccnd_routes_count)");
			free(ldpobj->ccnd_hostname);
		}

		if (ldpobj->ccnd_port != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->ccnd_port)");
			free(ldpobj->ccnd_port);
		}

		if (ldpobj->keystore_uri != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->keystore_uri)");
			free(ldpobj->keystore_uri);
		}

		if (ldpobj->keylocator_uri != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh->keylocator_uri)");
			free(ldpobj->keylocator_uri);
		}

		if (ldpobj->user_ccnx_dir != NULL) {
			LDPLOG(LOG_DEBUG, "ldp_settings_destroy(), free(psh-user_ccnx_dir)");
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