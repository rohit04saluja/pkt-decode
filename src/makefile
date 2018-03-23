#
# makefile
#
# Created by Rohit Saluja on 3/22/18.
# Copyright © 2018 rohit04saluja. All rights reserved.
#

CC = clang++
MKDIR = mkdir
RM = rm
ECHO = echo

IPATHS = . layer2
IPATHS_GTEST = layer2/unit-tests
LPATHS_GTEST = /usr/local/lib

CFLAGS = $(addprefix -I, $(IPATHS))
CFLAGS_GTEST += $(addprefix -I, $(IPATHS_GTEST))
CFLAGS_GTEST += $(addprefix -L, $(LPATHS_GTEST))

OBJDIR = ../obj
SRCDIR = .
SHIPDIR = ../ship

_OBJ = layer2/ethernet.o layer2/decode.o
_GTEST_OBJ = layer2/unit-tests/ethernet_gtest.o layer2/unit-tests/layer2_decode_gtest.o
_LIBA = /usr/local/lib/libgtest.a

OBJ = $(addprefix $(OBJDIR)/, $(_OBJ))
GTEST_OBJ = $(addprefix $(OBJDIR)/, $(_GTEST_OBJ))
LIBA = $(addprefix -l, $(_LIBA))

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

ALL = pkt-decode pkt-decode-gtest

all: $(ALL)

pkt-decode: $(OBJDIR)/main.o $(OBJ)
	$(ECHO) Building $@
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(CFLAGS)
	$(ECHO) Finished $@

pkt-decode-gtest: $(OBJDIR)/gtest_main.o $(OBJ) $(GTEST_OBJ)
	$(ECHO) Building $@
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(CFLAGS) $(CFLAGS_GTEST) $(_LIBA)
	$(ECHO) Finished $@

install:
	$(ECHO) Coping targets
	cp $(SHIPDIR)/* /usr/local/bin

clean:
	$(ECHO) Deleting all targets and .o
	$(RM) -rf $(OBJDIR) $(SHIPDIR)

.PHONY: pkt-decode clean pkt-decode-gtest install all
