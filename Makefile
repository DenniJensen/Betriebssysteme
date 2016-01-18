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


#
# Quellen
#
LSCRIPT = kernel.lds

OBJ =  system/entry.o system/start.o
OBJ += system/exceptions.o system/exceptions_asm.o
OBJ += system/cpu.o system/cpu_asm.o
OBJ += system/info.o
OBJ += system/scheduler.o

OBJ += driver/dbgu.o driver/mc.o driver/st.o driver/aic.o
OBJ += lib/print.o lib/mem.o lib/list.o lib/syscalls.o
OBJ += lib/scan.o
OBJ += user/userthread.o user/lib.o

#
# Konfiguration
#
CC = $(shell ./path_resolve arm-none-eabi-gcc)
LD = $(shell ./path_resolve arm-none-eabi-ld)
OBJCOPY = $(shell ./path_resolve arm-none-eabi-objcopy)

QEMU_BSPRAK = $(shell ./path_resolve qemu-bsprak)

CFLAGS = -Wall -Wextra -ffreestanding -mcpu=arm920t -O2
CPPFLAGS = -Iinclude
#LIBGCC := $(shell $(CC) -print-libgcc-file-name)

DEP = $(OBJ:.o=.d)

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

%.o: %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -o $@ -c $<

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -o $@ -c $<

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
