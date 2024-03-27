
COMPILER := gcc-rv32

ifeq ($(COMPILER),gcc-rv32)
	CC := riscv64-unknown-elf-gcc
	OBJDUMP := riscv64-unknown-elf-objdump
	CFLAGS_ARCH := -march=rv32i -mabi=ilp32 -Wno-pointer-to-int-cast
	SIMULATOR := qemu-riscv32
else ifeq ($(COMPILER),gcc-rv64)
	CC := riscv64-unknown-elf-gcc
	OBJDUMP := riscv64-unknown-elf-objdump
	CFLAGS_ARCH := -march=rv64imac -mabi=lp64 -Wno-pointer-to-int-cast
	SIMULATOR := qemu-riscv64
else ifeq ($(COMPILER),ccac-rmx100)
	CC := ccac
	OBJDUMP := riscv64-unknown-elf-objdump
	CFLAGS_ARCH := -tcf=rmx100.tcf -Hhostlib=semihost
	SIMULATOR := nsimdrv
	SIMULATOR_FLAGS := -tcf $(METAWARE_ROOT)/arc/tcf/rmx100.tcf -p nsim_semihosting=1
else
	$(error "Unrecognized COMPILER")
endif

CFLAGS := -O0 -mno-relax $(CFLAGS_ARCH)
LDFLAGS := -Wl,--section-start=.data=0x30000
BINARY := riscv_relocations_$(COMPILER).elf
OBJECTS := riscv_relocations_data_$(COMPILER).o riscv_relocations_$(COMPILER).o

.PHONY: all run clean

all: $(BINARY)

riscv_relocations_data_$(COMPILER).o: riscv_relocations_data.S
	$(CC) $(CFLAGS) -c $^ -o $@

riscv_relocations_$(COMPILER).o: riscv_relocations.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

run: $(BINARY)
	$(SIMULATOR) $(SIMULATOR_FLAGS) $(BINARY)

relocations: riscv_relocations_data_$(COMPILER).o
	$(OBJDUMP) -r $<

clean:
	rm -f $(BINARY) $(OBJECTS)
