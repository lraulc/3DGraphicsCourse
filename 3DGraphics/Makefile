# Build for MACOS - M1
# build:
# 	gcc 3DGraphics/*.c -I/Library/Frameworks/SDL2.framework/Headers -F/Library/frameworks -framework SDL2 -o renderer
# run:
# 	./renderer
# clean:
# 	rm renderer

build:
	gcc 3DGraphics/*.c -I 3DGraphics/include/ -L 3DGraphics/lib -o renderer.exe -lmingw32 -lSDL2main -lSDL2
run:
	./renderer.exe
clean:
	rm renderer.exe