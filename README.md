# urlencode

base64-like encoder and decoder for URL encoding

## Install

An AUR package is provided at
<https://aur.archlinux.org/packages/urlencode/> for Arch Linux and
derivatives. Anyone else must manually build from sources.

### Building from sources

To build the software, run the following commands inside the main source
directory. Tested on Arch and Debian Linux, should work on most
UNIX-like OSes. Windows users should try using MinGW, Cygwin or their
favourite compatibility solution.

```sh
./autogen.sh
./configure
make
```

Then `make install` (must be run with elevated privileges) to install to
a system-wide location (usually `/usr/local/bin`)

## Usage

Reads from standard input, writes to standard output.

### Options

* `-a` encode all characters
* `-b` do not automatically encode non printable (i.e. binary)
  characters
* `-c` specify a different set of reserved characters when encoding
* `-d` decode data
* `-l` encode input line by line
* `-n` do not output the trailing newline when encoding
