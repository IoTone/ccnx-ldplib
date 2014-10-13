#
# cJSON Makefile - Added because there was no Makefile
# 
# Copyright 2014 IoTone, Inc
#

all: libcjson.a 

libcjson.a: cJSON.o
	$(AR) rc $@ $^

%.o: %.c cJSON.h
	$(CC) -c $(CFLAGS) $< -o $@ -lm

test: cjson_test
	./cjson_test

cjson_test: cjson_test.o
	$(CC) -L. $< -o $@ -lcjson -lm

cjson_test.o: cjson_test.c libcjson.a

clean:
	rm -f cJSON.o cjson_test.o
	rm -f cjson_test
	rm -f cjson_test.exe
	rm -f libcjson.a

.PHONY: all clean test

