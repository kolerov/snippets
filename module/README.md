# Modules

## Resources

* Git repository: <https://github.com/cea-hpc/modules>
* Documentation: <https://modules.readthedocs.io>

## Installation

Install dependencies:

```shell
# Dependencies for Fedora
sudo dnf install python3-sphinx tcl-devel autoconf automake

# Dependencies for Ubuntu
sudo apt install python3-sphinx tcl8.6-dev autoconf automake
```

Clone the repository:

```shell
git clone https://github.com/cea-hpc/modules
cd modules
```

Install Modules itself:

```shell
./configure
make
sudo make install
```

Install documentation:

```shell
make -C doc all
sudo make -C doc install
```

Add Modules to startup shell scripts:

```shell
sudo ln -s /usr/local/Modules/init/profile.sh /etc/profile.d/modules.sh
sudo ln -s /usr/local/Modules/init/profile.csh /etc/profile.d/modules.csh
```

Copy all module files from `modulefiles`:

```shell
sudo cp -rf modulefiles /usr/local/Modules/modulefiles
```
