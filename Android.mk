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


LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)


# Look into creating libccnx exports
LOCAL_C_INCLUDES    += $(LOCAL_PATH)/../external/ccnx-0.8.0/csrc/sync
LOCAL_C_INCLUDES    += $(LOCAL_PATH)/../external/ccnx-0.8.0/csrc/include

LOCAL_SRC_FILES     := \
			ldp.c \
			ldp_controller.c 
LOCAL_CFLAGS		:= $(M_CFLAGS) $(OS_CFLAGS)
LOCAL_LDLIBS        := -L$(SYSROOT)/usr/lib -ldl -llog $(OS_LDFLAGS)

LOCAL_SHARED_LIBRARIES := \
	libccnsync \
LOCAL_STATIC_LIBRARIES := \
	libccnx \
	libssl \
	libcrypto
LOCAL_MODULE := ldp_controller
include $(BUILD_SHARED_LIBRARY)
