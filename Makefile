.SILENT:
FLAG = --std=c++11 -Dlinux
CPP = g++
DEPENDENCIES = ./Block.o ./main.o ./ConsoleIO.o
ifdef MAKE_RELEASE
	FLAG += -O2
endif
ifdef MAKE_DEBUG
	FLAG += -DDEBUG -g
endif
ifdef MAKE_STATIC
	FLAG += -static
endif

default:
	make release

tetris: $(DEPENDENCIES)
	 echo "[4/4] Building tetris"
	$(CPP) $(DEPENDENCIES) $(FLAG) -o tetris

./Block.o: ./Block.cpp
	echo "[1/4] Compiling ./Block.cpp"
	$(CPP) -c $(FLAG) $< -o ./Block.o
./main.o: ./main.cpp
	echo "[2/4] Compiling ./main.cpp"
	$(CPP) -c $(FLAG) $< -o ./main.o
./ConsoleIO.o: ./ConsoleIO.cpp
	echo "[3/4] Compiling ./ConsoleIO.cpp"
	$(CPP) -c $(FLAG) $< -o ./ConsoleIO.o

clean:
	echo "Cleaning files"
	rm -rf ./Block.o ./main.o ./ConsoleIO.o
install:
	echo "Installing tetris to /usr/local/bin"
	cp ./tetris /usr/local/bin/
debug:
	echo "Building a debug version"
	env MAKE_DEBUG=true make tetris
static:
	echo "Building a statically linked version"
	env MAKE_STATIC=true make tetris
release:
	echo "Building a release version"
	env MAKE_RELEASE=true make tetris
