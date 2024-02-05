REMOTE_HOST ?= arc-qemu-root
REMOTE_PORT ?= 2022
BUGS_DIR := /home/ykolerov/workspace/gdb/bugs
NPROC ?= 4

QEMU_FTP := hostfwd=tcp::2021-:21
QEMU_SSH := hostfwd=tcp::2022-:22
QEMU_TLN := hostfwd=tcp::2023-:23
QEMU_GDB := hostfwd=tcp::12345-:12345
QEMU_COMMON_ARGS := \
    -display none -nographic -monitor none \
    -device virtio-rng-pci \
    -netdev user,id=net0,$(QEMU_FTP),$(QEMU_SSH),$(QEMU_TLN),$(QEMU_GDB) \
    -device virtio-net-device,netdev=net0

RSYNC_ARGS := -rpltv --chmod=a+wr

run-qemu-hs4x:
	qemu-system-arc $(QEMU_COMMON_ARGS) \
	    -M virt -cpu archs -m 2G -kernel build-qemu-hs4x-gnu/images/vmlinux

configure-qemu-hs4x:
	rm -rf build-qemu-hs4x-gnu
	mkdir -p build-qemu-hs4x-gnu
	make -C buildroot O=$(abspath build-qemu-hs4x-gnu) defconfig DEFCONFIG=../defconfigs/qemu_hs4x_defconfig

build-qemu-hs4x:
	make -C build-qemu-hs4x-gnu -j $(NPROC)

setup-gdb-hs4x:
	rsync --port=$(REMOTE_PORT) $(RSYNC_ARGS) /tools/gdb-arc-linux-gnu-native/* root@$(REMOTE_HOST):/

setup-bugs-hs4x:
	rsync --port=$(REMOTE_PORT) $(RSYNC_ARGS) $(BUGS_DIR)/* root@$(REMOTE_HOST):/root/

setup-hs4x: setup-gdb-hs4x setup-bugs-hs4x
