CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -O2 -D_GNU_SOURCE
SRCDIR = src
OBJDIR = build
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = coldjail

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
