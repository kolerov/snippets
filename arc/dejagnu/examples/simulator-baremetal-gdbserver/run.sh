#!/bin/bash -e

# Newlib
# 
# srcdir="/repos/newlib/newlib/testsuite"
# tool="newlib"

srcdir="`realpath ../../../gdb/binutils-gdb/gdb/testsuite`"
simulator="nsim"
tool="gdb"
target="arc-elf32"

if [[ $simulator == "qemu" ]]; then
        board=arc-qemu-baremetal-gdb
        export QEMU_HOME="/tools/qemu-arc"
        export PATH="${QEMU_HOME}/bin:$PATH"
elif [[ $simulator == "nsim" ]]; then
        board=arc-nsim-baremetal-gdb
        export NSIM_HOME="/tools/mwdt-2023.12/nSIM/nSIM_64"
        export PATH="${NSIM_HOME}/bin:$PATH"
        export LD_LIBRARY_PATH="${NSIM_HOME}/lib"
else
        echo "Error: wrong simulator: $simulator"
        exit 1
fi

# Export GCC cross-compilers
export PATH="/tools/gcc-arc-elf-2023.09/bin:$PATH"
export PATH="/tools/gcc-arc64-elf-2023.09/bin:$PATH"

# Export GDB
if [[ $tool == "gdb" ]]; then
        if [[ $target == "arc-elf32" ]]; then
                gdb_home="/tools/gdb-arc-elf32-newlib"
        else
                gdb_home="/tools/gdb-arc64-elf-newlib"
        fi
fi

export PATH="${gdb_home}/bin:$PATH"
gdb="${gdb_home}/bin/$target-gdb"

export DEJAGNU="`realpath ../../dejagnu/site.exp`"
export ARC_MULTILIB_OPTIONS="-mcpu=archs"
export ARC_SPECS_FILE="nsim.specs"
export ARC_GDBSERVER_PORT="49105"

rm -rf log obj tmp
mkdir log obj tmp

runtest --outdir log \
        --objdir obj \
        --tool $tool \
        --srcdir $srcdir \
        --target_board $board \
        GDB="$gdb" \
        arc-dbnz.exp
