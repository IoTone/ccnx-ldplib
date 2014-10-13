#
#
# Copyright (c) 2014, IoTone, Inc.
#
#
# CCNx LDP Library
# 
# Runtime Depends on:
# - libccnx.a and libccnx headers
# - cJSON
# 
# Test Suite depends on:
# - google test
#

EXTERNAL_DIR = ./external
# Set INSTALL_BASE to the location of your CCNx installation or dev source base
#
# for example INSTALL_BASE = $(EXTERNAL_DIR)/ccnx-0.8.0
#
ADD_INCLUDE = $(EXTERNAL_DIR)/cJSON

#
# Add libs here, for example: -lpthread 
#
ADD_LIBS =
IFLAGS = -I$(INSTALL_BASE)/include -I$(ADD_INCLUDE)
LFLAGS = -L$(INSTALL_BASE)/lib -lccn -lccnsync -lcrypto $(ADD_LIBS)

PROGRAMS = ldputil
OBJS = ldp.o
LIBS = ldplib.a



CC = gcc
CFLAGS = -g -Wall -Wextra -O2
AR = ar
default: $(PROGRAMS) $(LIBS)

testframework:
	(cd $(EXTERNAL_DIR) && wget https://googletest.googlecode.com/files/gtest-1.6.0.zip && unzip -o ./gtest-1.6.0.zip && cd gtest-1.6.0 && ./configure && make)

test:
	(cd tests && make runall)

ccnx:
	(cd $(INSTALL_BASE) && make)

jsmn.o: $(EXTERNAL_DIR)/bstrlib/bstrlib.c $(EXTERNAL_DIR)/bstrlib/bstraux.c
	(cd $(EXTERNAL_DIR)/bstrlib && $(CC) $(CFLAGS) $(IFLAGS) -c bstrlib.c bstraux.c)

bstrlib.o: $(EXTERNAL_DIR)/bstrlib/bstrlib.c $(EXTERNAL_DIR)/bstrlib/bstraux.c
	(cd $(EXTERNAL_DIR)/bstrlib && $(CC) $(CFLAGS) $(IFLAGS) -c bstrlib.c bstraux.c)

ldp.o: ldp.c
	$(CC) $(CFLAGS) $(IFLAGS) -c ldp.c

ldputil.o: ldputil.c
	$(CC) $(CFLAGS) $(IFLAGS) -c ldputil.c

ldplib.a: $(OBJS)
	$(AR) crus $@ $(OBJS)

ldputil: $(OBJS) ldputil.o
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJS) ldputil.o $(LFLAGS)

clean:
	rm -f $(PROGRAMS) $(OBJS) *.o *.a *.dSYM core core.*
