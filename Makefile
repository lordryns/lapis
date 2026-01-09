CC=clang
TARGET=main.c dock.c applauncher.c event.c background.c settings.c
CFLAGS=`pkg-config --cflags gtk4` `pkg-config --cflags gtk4-layer-shell-0` -Wextra -Wall
LFLAGS=`pkg-config --libs gtk4` `pkg-config --libs gtk4-layer-shell-0`
OUTPUT=lapis

build:
	$(CC) $(TARGET) -o $(OUTPUT) $(CFLAGS) $(LFLAGS)


clean:
	rm -rf $(OUTPUT)

.PHONY: build clean
