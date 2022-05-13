CPP_SOURCES = main.cpp textures.cpp game.cpp piece.cpp factories.cpp utils.cpp
CFLAGS = -Wall -fno-stack-protector -O2 -Wa, -g


# -S -fverbose-asm -O0 -masm=intel -g


all: build

build: $(CPP_SOURCES)
	g++ \
  -lsfml-graphics \
  -lsfml-window \
  -lsfml-system \
  -liconv \
  $(CFLAGS) $(CPP_SOURCES)
