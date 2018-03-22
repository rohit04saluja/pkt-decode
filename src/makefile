#
# makefile
#
# Created by Rohit Saluja on 3/22/18.
# Copyright © 2018 rohit04saluja. All rights reserved.
#

CC = clang++
MKDIR = mkdir
RM = rm

CFLAGS = -I./layer2 -I./layer23 -I./layer3 -I./layer4 -I./layer5
OBJDIR = ../obj
SRCDIR = .
SHIPDIR = ../ship

_OBJ = main.o layer2/ethernet.o
OBJ = $(addprefix $(OBJDIR)/, $(_OBJ))

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

pkt-decode: $(OBJ)
	$(MKDIR) -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(CFLAGS)

clean:
	$(RM) -rf $(OBJDIR) $(SHIPDIR)

.PHONY: pkt-decode clean

