#
# Common definitions
#

NPROC 		?= 4
DEBUG_FLAGS 	:= -O0 -g3 -fvar-tracking-assignments
CFLAGS		:= $(DEBUG_FLAGS) # Add -DNCURSES_STATIC for static?
CXXFLAGS	:= $(CFLAGS)

#
# GCC configurations
#

TOOLCHAIN_HS4X_UCLIBC_SYSROOT_PATH	:= $(shell arc-linux-uclibc-gcc -print-sysroot)
GDB_HS4X_UCLIBC_HOST_BUILD_DIR 		:= build-gdb-hs4x-uclibc-host
GDB_HS4X_UCLIBC_HOST_PREFIX 		:= /tools/gdb-arc-linux-uclibc-host
GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR 	:= build-gdb-hs4x-uclibc-native
GDB_HS4X_UCLIBC_NATIVE_PREFIX 		:= /tools/gdb-arc-linux-uclibc-native

TOOLCHAIN_HS4X_GNU_PATH 		:= /tools/gcc-arc-linux-gnu-2023.09-hs4x
TOOLCHAIN_HS4X_GNU_SYSROOT_PATH 	:= $(shell arc-linux-gnu-gcc -print-sysroot)
GDB_HS4X_GNU_HOST_BUILD_DIR 		:= build-gdb-hs4x-gnu-host
GDB_HS4X_GNU_HOST_PREFIX 		:= /tools/gdb-arc-linux-gnu-host
GDB_HS4X_GNU_NATIVE_BUILD_DIR 		:= build-gdb-hs4x-gnu-native
GDB_HS4X_GNU_NATIVE_PREFIX 		:= /tools/gdb-arc-linux-gnu-native

TOOLCHAIN_HS5X_UCLIBC_SYSROOT_PATH 	:= $(shell arc32-linux-uclibc-gcc -print-sysroot)
GDB_HS5X_UCLIBC_HOST_BUILD_DIR 		:= build-gdb-hs5x-uclibc-host
GDB_HS5X_UCLIBC_HOST_PREFIX 		:= /tools/gdb-arc32-linux-uclibc-host
GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR 	:= build-gdb-hs5x-uclibc-native
GDB_HS5X_UCLIBC_NATIVE_PREFIX 		:= /tools/gdb-arc32-linux-uclibc-native
GMP_HS5X_UCLIBC_SYSROOT 		:= /tools/gmp-arc32-linux-uclibc
MPFR_HS5X_UCLIBC_SYSROOT 		:= /tools/mpfr-arc32-linux-uclibc

TOOLCHAIN_HS6X_GNU_SYSROOT_PATH := $(shell arc64-linux-gnu-gcc -print-sysroot)
GDB_HS6X_GNU_HOST_BUILD_DIR 	:= build-gdb-hs6x-gnu-host
GDB_HS6X_GNU_HOST_PREFIX 	:= /tools/gdb-arc64-linux-gnu-host
GDB_HS6X_GNU_NATIVE_BUILD_DIR 	:= build-gdb-hs6x-gnu-native
GDB_HS6X_GNU_NATIVE_PREFIX 	:= /tools/gdb-arc64-linux-gnu-native
GMP_HS6X_GNU_SYSROOT 		:= /tools/gmp-arc64-linux-gnu
MPFR_HS6X_GNU_SYSROOT 		:= /tools/mpfr-arc64-linux-gnu

COMMON_HOST_GDB_CONFIGURES := \
	--disable-multilib \
	--disable-werror \
	--disable-nls \
	--with-expat \
	--without-zstd \
	--with-curses \
	--disable-sim \
	--enable-gdb \
	--disable-gas \
	--disable-binutils \
	--disable-ld \
	--disable-gold \
	--disable-gprof

COMMON_NATIVE_GDB_CONFIGURES := \
	--prefix=/usr \
	--includedir=/usr/include \
	$(COMMON_HOST_GDB_CONFIGURES)

COMMON_GDBSERVER_CONFIGURES := \
	--prefix=/usr \
	--disable-werror \
	--disable-gdb

#
# HS4x uClibc - for host
#

.PHONY: \
	configure-gdb-hs4x-uclibc-host \
	build-gdb-hs4x-uclibc-host \
	install-gdb-hs4x-uclibc-host \
	clean-gdb-hs4x-uclibc-host

configure-gdb-hs4x-uclibc-host:
	rm -rf $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR)
	mkdir -p $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR)
	cd $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc-linux-uclibc \
		--prefix=$(GDB_HS4X_UCLIBC_HOST_PREFIX) \
		--with-sysroot=$(TOOLCHAIN_HS4X_UCLIBC_SYSROOT_PATH) \
		$(COMMON_HOST_GDB_CONFIGURES) \
		GLIBC_CC_FOR_TARGET=arc-linux-uclibc-gcc \
		GLIBC_CXX_FOR_TARGET=arc-linux-uclibc-g++ \
		CFLAGS="$(DEBUG_FLAGS)" \
		CXXFLAGS="$(DEBUG_FLAGS)"

build-gdb-hs4x-uclibc-host:
	make -C $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR) -j $(NPROC)

install-gdb-hs4x-uclibc-host:
	make -C $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR) install

clean-gdb-hs4x-uclibc-host:
	rm -rf $(GDB_HS4X_UCLIBC_HOST_BUILD_DIR)

#
# HS4x uClibc - for target
#

.PHONY: \
	configure-gdb-hs4x-uclibc-native \
	build-gdb-hs4x-uclibc-native \
	install-gdb-hs4x-uclibc-native \
	clean-gdb-hs4x-uclibc-native

configure-gdb-hs4x-uclibc-native:
	rm -rf $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR)
	mkdir -p $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR)
	cd $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc-linux-uclibc \
		--host=arc-linux-uclibc \
		--with-sysroot=$(TOOLCHAIN_HS4X_UCLIBC_SYSROOT_PATH) \
		$(COMMON_NATIVE_GDB_CONFIGURES) \
		GLIBC_CC_FOR_TARGET=arc-linux-uclibc-gcc \
		GLIBC_CXX_FOR_TARGET=arc-linux-uclibc-g++ \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)"

build-gdb-hs4x-uclibc-native:
	make -C $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR) -j $(NPROC)

install-gdb-hs4x-uclibc-native:
	make -C $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR) DESTDIR=$(GDB_HS4X_UCLIBC_NATIVE_PREFIX) install
	cp -rf \
		$(TOOLCHAIN_HS4X_UCLIBC_SYSROOT_PATH)/usr/lib/libexpat.so* \
		$(TOOLCHAIN_HS4X_UCLIBC_SYSROOT_PATH)/usr/lib/libncurses.so* \
		$(GDB_HS4X_UCLIBC_NATIVE_PREFIX)/usr/lib

clean-gdb-hs4x-uclibc-native:
	rm -rf $(GDB_HS4X_UCLIBC_NATIVE_BUILD_DIR)

#
# HS4x GNU - for host
#

.PHONY: \
	configure-gdb-hs4x-gnu-host \
	build-gdb-hs4x-gnu-host \
	install-gdb-hs4x-gnu-host \
	clean-gdb-hs4x-gnu-host

configure-gdb-hs4x-gnu-host:
	rm -rf $(GDB_HS4X_GNU_HOST_BUILD_DIR)
	mkdir -p $(GDB_HS4X_GNU_HOST_BUILD_DIR)
	cd $(GDB_HS4X_GNU_HOST_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc-linux-gnu \
		--prefix=$(GDB_HS4X_GNU_HOST_PREFIX) \
		--with-sysroot=$(TOOLCHAIN_HS4X_GNU_SYSROOT_PATH) \
		$(COMMON_HOST_GDB_CONFIGURES) \
		GLIBC_CC_FOR_TARGET=arc-linux-gnu-gcc \
		GLIBC_CXX_FOR_TARGET=arc-linux-gnu-g++ \
		CFLAGS="$(DEBUG_FLAGS)" \
		CXXFLAGS="$(DEBUG_FLAGS)"

build-gdb-hs4x-gnu-host:
	make -C $(GDB_HS4X_GNU_HOST_BUILD_DIR) -j $(NPROC)

install-gdb-hs4x-gnu-host:
	make -C $(GDB_HS4X_GNU_HOST_BUILD_DIR) install

clean-gdb-hs4x-gnu-host:
	rm -rf $(GDB_HS4X_GNU_HOST_BUILD_DIR)

#
# HS4x GNU - for target
#

.PHONY: \
	configure-gdb-hs4x-gnu-native \
	build-gdb-hs4x-gnu-native \
	install-gdb-hs4x-gnu-native \
	clean-gdb-hs4x-gnu-native

configure-gdb-hs4x-gnu-native:
	rm -rf $(GDB_HS4X_GNU_NATIVE_BUILD_DIR)
	mkdir -p $(GDB_HS4X_GNU_NATIVE_BUILD_DIR)
	cd $(GDB_HS4X_GNU_NATIVE_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc-linux-gnu \
		--host=arc-linux-gnu \
		--prefix=/usr \
		--with-sysroot=$(TOOLCHAIN_HS4X_GNU_SYSROOT_PATH) \
		--includedir=/usr/include \
		--disable-multilib \
		--disable-werror \
		--disable-nls \
		--with-expat \
		--without-zstd \
		--with-curses \
		--disable-sim \
		--enable-gdb \
		--disable-gas \
		--disable-binutils \
		--disable-ld \
		--disable-gold \
		--disable-gprof \
		GLIBC_CC_FOR_TARGET=arc-linux-gnu-gcc \
		GLIBC_CXX_FOR_TARGET=arc-linux-gnu-g++ \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)"

build-gdb-hs4x-gnu-native:
	make -C $(GDB_HS4X_GNU_NATIVE_BUILD_DIR) -j $(NPROC)

install-gdb-hs4x-gnu-native:
	make -C $(GDB_HS4X_GNU_NATIVE_BUILD_DIR) DESTDIR=$(GDB_HS4X_GNU_NATIVE_PREFIX) install
	cp -rf \
		$(TOOLCHAIN_HS4X_GNU_SYSROOT_PATH)/usr/lib/libexpat.so* \
		$(TOOLCHAIN_HS4X_GNU_SYSROOT_PATH)/usr/lib/libncurses.so* \
		$(GDB_HS4X_GNU_NATIVE_PREFIX)/usr/lib

clean-gdb-hs4x-gnu-native:
	rm -rf $(GDB_HS4X_GNU_NATIVE_BUILD_DIR)

#
# HS5x uClibc - for host
#

.PHONY: \
	configure-gdb-hs5x-uclibc-host \
	build-gdb-hs5x-uclibc-host \
	install-gdb-hs5x-uclibc-host \
	clean-gdb-hs5x-uclibc-host

configure-gdb-hs5x-uclibc-host:
	rm -rf $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR)
	mkdir -p $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR)
	cd $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc32-linux-uclibc \
		--prefix=$(GDB_HS5X_UCLIBC_HOST_PREFIX) \
		--with-sysroot=$(TOOLCHAIN_HS5X_UCLIBC_SYSROOT_PATH) \
		$(COMMON_HOST_GDB_CONFIGURES) \
		GLIBC_CC_FOR_TARGET=arc32-linux-uclibc-gcc \
		GLIBC_CXX_FOR_TARGET=arc32-linux-uclibc-g++ \
		CFLAGS="$(DEBUG_FLAGS)" \
		CXXFLAGS="$(DEBUG_FLAGS)"

build-gdb-hs5x-uclibc-host:
	make -C $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR) -j $(NPROC)

install-gdb-hs5x-uclibc-host:
	make -C $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR) install

clean-gdb-hs5x-uclibc-host:
	rm -rf $(GDB_HS5X_UCLIBC_HOST_BUILD_DIR)

#
# HS5x uClibc - for target - only gdbserver
#

.PHONY: \
	configure-gdb-hs5x-uclibc-native \
	build-gdb-hs5x-uclibc-native \
	install-gdb-hs5x-uclibc-native \
	clean-gdb-hs5x-uclibc-native

configure-gdb-hs5x-uclibc-native:
	rm -rf $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR)
	mkdir -p $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR)
	cd $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc32-linux-uclibc \
		--host=arc32-linux-uclibc \
		$(COMMON_GDBSERVER_CONFIGURES) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)"

build-gdb-hs5x-uclibc-native:
	make -C $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR) all-gdbserver -j $(NPROC)

install-gdb-hs5x-uclibc-native:
	make -C $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR) install-gdbserver DESTDIR=$(GDB_HS5X_UCLIBC_NATIVE_PREFIX)

clean-gdb-hs5x-uclibc-native:
	rm -rf $(GDB_HS5X_UCLIBC_NATIVE_BUILD_DIR)

#
# HS6x GNU - for target - only gdbserver
#

.PHONY: \
	configure-gdb-hs6x-gnu-native \
	build-gdb-hs6x-gnu-host \
	install-gdb-hs6x-gnu-host \
	clean-gdb-hs6x-gnu-host

configure-gdb-hs6x-gnu-host:
	rm -rf $(GDB_HS6X_GNU_HOST_BUILD_DIR)
	mkdir -p $(GDB_HS6X_GNU_HOST_BUILD_DIR)
	cd $(GDB_HS6X_GNU_HOST_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc64-linux-gnu \
		--prefix=$(GDB_HS6X_GNU_HOST_PREFIX) \
		--with-sysroot=$(TOOLCHAIN_HS6X_GNU_SYSROOT_PATH) \
		$(COMMON_HOST_GDB_CONFIGURES) \
		GLIBC_CC_FOR_TARGET=arc64-linux-gnu-gcc \
		GLIBC_CXX_FOR_TARGET=arc64-linux-gnu-g++ \
		CFLAGS="$(DEBUG_FLAGS)" \
		CXXFLAGS="$(DEBUG_FLAGS)"

build-gdb-hs6x-gnu-host:
	make -C $(GDB_HS6X_GNU_HOST_BUILD_DIR) -j $(NPROC)

install-gdb-hs6x-gnu-host:
	make -C $(GDB_HS6X_GNU_HOST_BUILD_DIR) install

clean-gdb-hs6x-gnu-host:
	rm -rf $(GDB_HS6X_GNU_HOST_BUILD_DIR)

#
# HS6x GNU - for target
#

.PHONY: \
	configure-gdb-hs6x-gnu-native \
	build-gdb-hs6x-gnu-native \
	install-gdb-hs6x-gnu-native \
	clean-gdb-hs6x-gnu-native

configure-gdb-hs6x-gnu-native:
	rm -rf $(GDB_HS6X_GNU_NATIVE_BUILD_DIR)
	mkdir -p $(GDB_HS6X_GNU_NATIVE_BUILD_DIR)
	cd $(GDB_HS6X_GNU_NATIVE_BUILD_DIR) && \
	../binutils-gdb/configure \
		--target=arc64-linux-gnu \
		--host=arc64-linux-gnu \
		$(COMMON_GDBSERVER_CONFIGURES) \
		CFLAGS="$(CFLAGS)" \
		CXXFLAGS="$(CXXFLAGS)"

build-gdb-hs6x-gnu-native:
	make -C $(GDB_HS6X_GNU_NATIVE_BUILD_DIR) all-gdbserver -j $(NPROC)

install-gdb-hs6x-gnu-native:
	make -C $(GDB_HS6X_GNU_NATIVE_BUILD_DIR) install-gdbserver DESTDIR=$(GDB_HS6X_GNU_NATIVE_PREFIX)

clean-gdb-hs6x-gnu-native:
	rm -rf $(GDB_HS6X_GNU_NATIVE_BUILD_DIR)

#
# GMP and MPFR
#

GMP_SRC_DIR_NAME := gmp
MPFR_SRC_DIR_NAME := mpfr
GMP_HS5X_UCLIBC_BUILD_DIR_NAME := build-gmp-hs5x-uclibc
MPFR_HS5X_UCLIBC_BUILD_DIR_NAME := build-mpfr-hs5x-uclibc

clone-gmp:
	hg clone https://gmplib.org/repo/gmp-6.3/ $(GMP_SRC_DIR_NAME)
	cd $(GMP_SRC_DIR_NAME) && ./.bootstrap

clone-mpfr:
	git clone -b 4.2.1 https://gitlab.inria.fr/mpfr/mpfr.git $(MPFR_SRC_DIR_NAME)
	cd $(MPFR_SRC_DIR_NAME) && ./autogen.sh

.PHONY: \
	configure-gmp-hs5x-uclibc \
	build-gmp-hs5x-uclibc \
	install-gmp-hs5x-uclibc \
	configure-mpfr-hs5x-uclibc \
	build-mpfr-hs5x-uclibc \
	install-mpfr-hs5x-uclibc

configure-gmp-hs5x-uclibc:
	mkdir -p $(GMP_HS5X_UCLIBC_BUILD_DIR_NAME)
	cd $(GMP_HS5X_UCLIBC_BUILD_DIR_NAME) && \
		../$(GMP_SRC_DIR_NAME)/configure --prefix=/usr --host=arc32-linux-uclibc --enable-shared=no --enable-maintainer-mode

build-gmp-hs5x-uclibc:
	make -C $(GMP_HS5X_UCLIBC_BUILD_DIR_NAME) -j $(nproc)

install-gmp-hs5x-uclibc:
	make -C $(GMP_HS5X_UCLIBC_BUILD_DIR_NAME) DESTDIR=$(GMP_HS5X_UCLIBC_SYSROOT) install

configure-mpfr-hs5x-uclibc:
	mkdir -p $(MPFR_HS5X_UCLIBC_BUILD_DIR_NAME)
	cd $(MPFR_HS5X_UCLIBC_BUILD_DIR_NAME) && \
		CC=arc32-linux-uclibc-gcc LD=arc32-linux-uclibc-ld \
		../$(MPFR_SRC_DIR_NAME)/configure \
			--host=arc32-linux-uclibc \
			--prefix=/usr \
			--enable-shared=no \
			--with-gmp=$(GMP_HS5X_UCLIBC_SYSROOT)/usr

build-mpfr-hs5x-uclibc:
	make -C $(MPFR_HS5X_UCLIBC_BUILD_DIR_NAME) -j $(nproc)

install-mpfr-hs5x-uclibc:
	make -C $(MPFR_HS5X_UCLIBC_BUILD_DIR_NAME) DESTDIR=$(MPFR_HS5X_UCLIBC_SYSROOT) install
