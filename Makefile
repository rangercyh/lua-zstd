.PHONY: all clean

CC = gcc
CFLAGS = -g3 -O2 -rdynamic -Wall -fPIC -shared -Wextra

CCFLAGS = -DZSTD_DISABLE_ASM

zstd.so: common/*.c compress/*.c decompress/*.c lua-zstd.c
	$(CC) $(CFLAGS) $(CCFLAGS) -o $@ $^

test:
	lua test.lua

clean:
	rm -f *.so

