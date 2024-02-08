# Developing GDB

## Environment

Clone the repository:

```shell
git clone -b arc64 https://github.com/foss-for-synopsys-dwc-arc-processors/binutils-gdb
```

Load GCC modules:

```shell
module add gcc-arc-linux-gnu gcc-arc-linux-uclibc gcc-arc32-linux-uclibc gcc-arc64-linux-gnu
```

## ARC Specific Tests

They are placed in `gdb/testsuite/gdb.arch`:

```text
arc-analyze-prologue.exp
arc-dbnz.exp
arc-decode-insn.exp
arc-tdesc-cpu.exp
```
