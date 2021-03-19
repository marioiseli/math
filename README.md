To compile on MacOS, make sure you have gcc & libgpm installed, then do:

gcc -o googol -lgpm -I /usr/local/include googol.c

Probably you also have to set LIBRARY_PATH=/usr/local/lib, to make sure the linker finds the shared object properly
