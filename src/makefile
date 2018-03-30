#
# makefile
#
# Created by Rohit Saluja on 3/22/18.
# Copyright © 2018 rohit04saluja. All rights reserved.
#

.DEFAULT_GOAL = all

CC = clang++
MKDIR = mkdir
RM = rm
ECHO = echo
FIND = find
GREP = grep
XARGS = xargs

IPATHS = . layer2 layer3

CFLAGS = $(addprefix -I, $(IPATHS))

OBJDIR = ../obj
SRCDIR = .
SHIPDIR = ../ship

_OBJ = decode.o layer2/ethernet.o layer2/layer2_decode.o layer3/ipv4.o layer3/layer3_decode.o layer3/ipv6.o
_GTEST_OBJ = unit-tests/decode_gtest.o layer2/unit-tests/ethernet_gtest.o layer2/unit-tests/layer2_decode_gtest.o layer3/unit-tests/ipv4_gtest.o layer3/unit-tests/layer3_decode_gtest.o layer3/unit-tests/ipv6_gtest.o

_LIBA = gtest

OBJ = $(addprefix $(OBJDIR)/, $(_OBJ))
GTEST_OBJ = $(addprefix $(OBJDIR)/, $(_GTEST_OBJ))
GCOV_OBJ = $(addprefix $(OBJDIR)/gcov/, $(_OBJ))
GCOV_OBJ += $(addprefix $(OBJDIR)/gcov/, $(_GTEST_OBJ))
LIBA = $(addprefix -l, $(_LIBA))

$(OBJDIR)/gcov/%.o: %.cpp
	$(ECHO) Building $@
	$(MKDIR) -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS) -g -fprofile-arcs -ftest-coverage
	$(ECHO) Finished $@

$(OBJDIR)/%.o: %.cpp
	$(ECHO) Building $@
	$(MKDIR) -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)
	$(ECHO) Finished $@

ALL = pkt-decode pkt-decode-gtest

all: $(ALL)

cbuild: pkt-decode-gtest-coverage

pkt-decode: $(OBJDIR)/main.o $(OBJ)
	$(ECHO) Building $@
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^
	$(ECHO) Finished $@

pkt-decode-gtest: $(OBJDIR)/gtest_main.o $(OBJ) $(GTEST_OBJ)
	$(ECHO) Building $@
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(LIBA)
	$(ECHO) Finished $@

pkt-decode-gtest-coverage: $(OBJDIR)/gcov/gtest_main.o $(GCOV_OBJ)
	$(ECHO) Building $@
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(LIBA) -g -fprofile-arcs -ftest-coverage
	$(ECHO) Finished $@

install:
	$(ECHO) Coping targets
	cp $(SHIPDIR)/* /usr/local/bin

clean:
	$(ECHO) Deleting all targets, .o and gcov files
	$(RM) -rf $(OBJDIR) $(SHIPDIR)
	$(FIND) * | $(GREP) gc | $(XARGS) rm

.PHONY: pkt-decode clean pkt-decode-gtest install all
