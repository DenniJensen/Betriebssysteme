#
# Kurzanleitung
# =============
#
# make		-- Baut den Kernel.
# make all
#
# make install	-- Baut den Kernel und transferiert ihn auf den Server.
# 		   Das Board holt sich diesen Kernel beim nächsten Reset.
#
# make clean	-- Löscht alle erzeugten Dateien.
#
# make run    -- Baut den Kernel und startet den Emulator


#
# Quellen
#
LSCRIPT = kernel.lds

OBJ = system/start.o system/main.o
OBJ += system/exception_asm.o system/exception.o

OBJ += lib/helpers.o
OBJ += driver/dbgu.o driver/aic.o driver/timer.o


#
# Konfiguration
#
CC = $(shell ./path_resolve arm-none-eabi-gcc)
LD = $(shell ./path_resolve arm-none-eabi-ld)
OBJCOPY = $(shell ./path_resolve arm-none-eabi-objcopy)

QEMU_BSPRAK = $(shell ./path_resolve qemu-bsprak)


CFLAGS = -Wall -Wextra -ffreestanding -mcpu=arm920t -Iinclude -I. -Ilib -O2
LIBGCC := $(shell $(CC) -print-libgcc-file-name)

DEP = $(OBJ:.o=.d)

debug: CFLAGS += -g

export CC
export LD
export OBJCOPY
export CFLAGS

#
# Regeln
#
.PHONY: all
all: kernel

-include $(DEP)

%.o: %.c %.S
	$(CC) $(CFLAGS) $(IFLAG) -MMD -MP -o $@ -c $<

kernel: $(LSCRIPT) $(OBJ)
	$(LD) -T$(LSCRIPT) -o $@ $(OBJ) $(LIBGCC)

kernel.bin: kernel
	$(OBJCOPY) -Obinary --set-section-flags .bss=contents,alloc,load,data $< $@

kernel.img: kernel.bin
	mkimage -A arm -T standalone -C none -a 0x20000000 -d $< $@

.PHONY: install
install: kernel.img
	arm-install-image $<

.PHONY: clean
clean:
	rm -f kernel kernel.bin kernel.img
	rm -f $(OBJ)
	rm -f $(DEP)
	rm -f $(shell find -name '*.gch')

.PHONY: run
run: clean kernel
	$(QEMU_BSPRAK) -kernel kernel

.PHONY: debug
debug: clean kernel
