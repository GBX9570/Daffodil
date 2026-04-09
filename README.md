# Daffodil
Daffodil is an x86 kernel (and hopefully, eventually, OS) that has zero standout features

it is not intended to be explicitly unix like or NT like but to take aspects of them both and other designs to create a new one.

to build, you require `clang`, `nasm`, `make`, `xorriso`, `grub` (on debian based distros, `grub2-pc`, on redhat based distros, `grub2`, for most distros, the packge is called `grub`), and `build-essential`.

run `make all` to build
run `make run` to run
run `make clean` to clean

this project is mostly written by hand with the occaisonal excerpt from other sources like the GNU website or the OSDev website. also, the makefile was written by chatgpt for a project i started a long time ago - however, no actual code in this project is written by any AI nor will it ever be.
