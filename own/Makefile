#
# Kurzanleitung
# =============
#
# make		-- Baut den Kernel.
# make all
# make run -- Fuehrt qemu aus
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
OBJ = start.o io_task.o my_io.o handler.o

#
# Konfiguration
#
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump

CFLAGS = -Wall -Wextra -ffreestanding -mcpu=arm920t -O2
LIBGCC := $(shell $(CC) -print-libgcc-file-name)

DEP = $(OBJ:.o=.d)

.PHONY: all
all: kernel

-include $(DEP)

%.o: %.S
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -o $@ -c $<

kernel: $(LSCRIPT) $(OBJ)
	$(LD) -T$(LSCRIPT) -o $@ $(OBJ) $(LIBGCC)

kernel.bin: kernel
	$(OBJCOPY) -Obinary --set-section-flags .bss=contents,alloc,load,data $< $@

kernel.img: kernel.bin
	mkimage -A arm -T standalone -C none -a 0x20000000 -d $< $@

.PHONY: install
install: kernel.img
	arm-install-image $<

check.kernel:
	$(OBJDUMP) -fhd kernel

check.o:
	$(OBJDUMP) -d $(OBJ)

run:
	qemu-bsprak -kernel kernel

run.telnet:
	qemu-bsprak -kernel kernel -piotelnet

telnet:
	telnet localhost 44444

.PHONY: clean
clean:
	rm -f kernel kernel.bin kernel.img
	rm -f $(OBJ)
	rm -f $(DEP)
