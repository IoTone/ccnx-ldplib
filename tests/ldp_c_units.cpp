#include <limits.h>
extern "C" {
  #include "ldp.h"
  #include "ldp_private.h"
}

#include "gtest/gtest.h"


// These are Units are based on xUNIT and utilize the GTest framework
// An important point on checking for NULL 
// http://code.google.com/p/googletest/wiki/FAQ#Why_does_Google_Test_support_EXPECT_EQ(NULL,_ptr)_and_ASSERT_EQ(

TEST(LDPCUnitTest, LDPLOGCalls) {
  LDPLOG = &ldp_log_console;
  LDPLOG_setmask = &ldp_log_console_setlogmask;
  LDPLOG_setmask(LOG_MASK(LOG_DEBUG));
  openlog ("LDPCUnitTest", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1); // This should use stdout, not syslog messages file
  ASSERT_TRUE(LDPLOG);
  ASSERT_TRUE(LDPLOG_setmask);
  // I'd need to use some pipes to verify that this works as it should.  We'll do visual inspection and trust that syslog works
  LDPLOG(LOG_INFO, "Testing our logging for LDPCUnitTest at LOG_INFO"); 
  LDPLOG(LOG_ERR, "Testing our logging for LDPCUnitTest at LOG_ERR");
  LDPLOG(LOG_DEBUG, "Testing our logging for LDPCUnitTest at LOG_DEBUG"); // Ignored

  char * s1 = "1234567890abcdefghij";
  char * b1 = (char*) calloc(1, 2 + 1);
  memcpy(b1,s1, 2);
  LDPLOG(LOG_INFO, "b1 = %s", b1);
  s1 = s1 + 2;
  memcpy(b1,s1, 2);
  LDPLOG(LOG_INFO, "b1 = %s", b1);

  closelog();
}

TEST(LDPCUnitTest, InitializeTLDPSettingsAndDestroy) {
  TLDPSettings *ldpobj = NULL;
  int ret;

  EXPECT_EQ(NULL, ldpobj);
  // TLDPSettings *ldp_settings_create(void);
  ldpobj = ldp_settings_create();
  EXPECT_TRUE(ldpobj);
  // int ldp_settings_init(TLDPSettings *settings);
  // We may need to set some timeout value in case the CCND isn't up
  ret = ldp_settings_init(ldpobj);
  EXPECT_TRUE(ret == 0);
  ldp_settings_destroy(&ldpobj);
  EXPECT_EQ(NULL, ldpobj);
}

TEST(LDPCUnitTest, WritePeerMetadata) {
  TLDPSettings *ldp_settings_obj = NULL;
  int ret;
  char *metastr = "{ \"peerID\" : \"8675309\"}";
  LDPLOG = &ldp_log_console;
  LDPLOG_setmask = &ldp_log_console_setlogmask;
  LDPLOG_setmask(LOG_MASK(LOG_ERR));
  openlog ("LDPNXCUnitTest", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1); // This should use stdout, not syslog messages file

  ldp_settings_obj = ldp_settings_create();
  EXPECT_TRUE(ldp_settings_obj);
  EXPECT_TRUE(ldp_settings_init(ldp_settings_obj) == 0);
  LDPLOG(LOG_DEBUG, "about to write peer metadata");
  // ret = ldp_write_peer_metadata_from_bytes(ldp_private_create_str("8675309"), ldp_DEFAULT_PEERGROUP_PEERS, ldp_private_create_str(metastr) , strlen(metastr), NULL, psobj); /* Write metadata from buffer */
  ret = ldp_write_peer_metadata_from_bytes(ldp_private_create_str("86753099"), ldp_private_create_str(metastr) , NULL); /* Write metadata from buffer */
  
  LDPLOG(LOG_DEBUG, "done with ldp_write_peer_metadata_from_bytes()");
  EXPECT_EQ(ret, 0);
  
  ldp_settings_destroy(&ldp_settings_obj);
  EXPECT_EQ(NULL, ldp_settings_obj);
  closelog();
}

TEST(LDPCUnitTest, GetPeerMetadata) {
  TLDPSettings *ldp_settings_obj = NULL;
  char *metadata = NULL;
  size_t bytes_read = 0;

  LDPLOG = &ldp_log_console;
  LDPLOG_setmask = &ldp_log_console_setlogmask;
  LDPLOG_setmask(LOG_MASK(LOG_ERR));
  openlog ("LDPCUnitTest", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1); // This should use stdout, not syslog messages file

  ldp_settings_obj = ldp_settings_create();
  EXPECT_TRUE(ldp_settings_obj);
  EXPECT_TRUE(ldp_settings_init(ldp_settings_obj) == 0);

  
  LDPLOG(LOG_DEBUG, "about to call ldp_get_peer_metadata_as_bytes(%s)", "86753099");
  metadata = ldp_get_peer_metadata_as_bytes("86753099", &bytes_read, NULL);
  LDPLOG(LOG_DEBUG, "done with call to ldp_get_peer_metadata_as_bytes()");
  EXPECT_TRUE(metadata != NULL);
  if (metadata != NULL) {
    LDPLOG(LOG_DEBUG, "read metadata = %s", metadata);
  }
  EXPECT_TRUE(bytes_read > 0);
  LDPLOG(LOG_DEBUG, "Read = %d", bytes_read);

  ldp_settings_destroy(&ldp_settings_obj);
  EXPECT_EQ(NULL, ldp_settings_obj);
  closelog();
}

TEST(LDPCUnitTest, GetPeers) {
  TLDPSettings *ldp_settings_obj = NULL;
  char **names = {0};
  int name_count = 0;

  LDPLOG = &ldp_log_console;
  LDPLOG_setmask = &ldp_log_console_setlogmask;
  LDPLOG_setmask(LOG_MASK(LOG_ERR));
  openlog ("LDPCUnitTest", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1); // This should use stdout, not syslog messages file

  ldp_settings_obj = ldp_settings_create();
  EXPECT_TRUE(ldp_settings_obj);
  EXPECT_TRUE(ldp_settings_init(ldp_settings_obj) == 0);

  
  LDPLOG(LOG_DEBUG, "about to call ldp_get_peers()");
  names = ldp_get_peers(&name_count, NULL);
  LDPLOG(LOG_DEBUG, "done with call to ldp_get_peers()");
  EXPECT_TRUE(names != NULL);
  EXPECT_TRUE(name_count >= 1);
  LDPLOG(LOG_DEBUG, "Got name_count = %d", name_count);
  for (int i = 0; i < name_count; i++) {
    LDPLOG(LOG_DEBUG, "First name: %s", names[i]);
  }

  ldp_settings_destroy(&ldp_settings_obj);
  EXPECT_EQ(NULL, ldp_settings_obj);
  closelog();
}