CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -O2 -D_GNU_SOURCE
SRCDIR = src
OBJDIR = build
TARGET = coldjail

# Lista os arquivos .c manualmente ou com wildcard (funciona se src/ existir)
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Força o diretório de objetos a ser criado ANTES de qualquer compilação
$(shell mkdir -p $(OBJDIR))

# Regra para compilar .c → .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra principal
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
