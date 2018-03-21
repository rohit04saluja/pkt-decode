#
# makefile
#
# Created by Rohit Saluja on 3/22/18.
# Copyright © 2018 rohit04saluja. All rights reserved.
#

CC = clang++
CFLAGS = -I.
OBJDIR = ../obj
SRCDIR = .
SHIPDIR = ../ship

_OBJ = main.o
OBJ = $(addprefix $(OBJDIR)/, $(_OBJ))

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

pkt-decode: $(OBJ)
	mkdir -p $(SHIPDIR)
	$(CC) -o $(SHIPDIR)/$@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJDIR) $(SHIPDIR)

.PHONY: pkt-decode clean

