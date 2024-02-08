#!/bin/bash -e

srcdir="`realpath ../../../gdb/binutils-gdb/gdb/testsuite`"
board=arc-linux-gdbserver
target="arc-linux-uclibc"

if [[ $target == "arc-linux-uclibc" ]]; then
        gcc_home="/tools/gcc-$target-2023.09-hs4x"
        gdb_host_home="/tools/gdb-$target-host"
        gdb_native_home="/tools/gdb-$target-native"
elif [[ $target == "arc-linux-gnu" ]]; then
        gcc_home="/tools/gcc-$target-2023.09-hs4x"
        gdb_host_home="/tools/gdb-$target-host"
        gdb_native_home="/tools/gdb-$target-native"
elif [[ $target == "arc32-linux-uclibc" ]]; then
        gcc_home="/tools/gcc-$target-2023.09"
        gdb_host_home="/tools/gdb-$target-host"
        gdb_native_home="/tools/gdb-$target-native"
elif [[ $target == "arc64-linux-gnu" ]]; then
        gcc_home="/tools/gcc-$target-2023.09"
        gdb_host_home="/tools/gdb-$target-host"
        gdb_native_home="/tools/gdb-$target-native"
else
        echo "Error: wrong target: $target"
        exit 1
fi

gdb="${gdb_host_home}/bin/${target}-gdb"
export PATH="${gcc_home}/bin:${gdb_host_home}/bin:$PATH"

export DEJAGNU="`realpath ../../dejagnu/site.exp`"
export ARC_TARGET_TRIPLET="$target"
export ARC_TARGET_ALIAS="${ARC_TARGET_TRIPLET}"
export ARC_GDBSERVER_HOSTNAME="127.0.0.1"
export ARC_GDBSERVER_PORT="12345"
export ARC_SYSROOT_PATH="`${gcc_home}/bin/${target}-gcc -print-sysroot`"
export ARC_SSH_HOSTNAME="arc-qemu-root"
export ARC_SSH_USERNAME="root"
export ARC_SSH_PORT="2022"
export ARC_SSH_PROG="ssh"
export ARC_SCP_PROG="scp"

${ARC_SCP_PROG} -P ${ARC_SSH_PORT} \
        ${gdb_native_home}/usr/bin/gdbserver \
        ${ARC_SSH_USERNAME}@${ARC_SSH_HOSTNAME}:/usr/bin

rm -rf log obj tmp
mkdir log obj tmp

runtest --outdir log \
        --objdir obj \
        --tool gdb \
        --srcdir "$srcdir" \
        --target_board "$board" \
        GDB="$gdb" \
        arc-dbnz.exp
