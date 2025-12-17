all: mac
linux:
	gcc -c -fPIC mylib.c -o mylib.o
	gcc -shared -o libmylib.so mylib.o

mac:
	clang -c -fPIC mylib.c -o mylib.o
	clang -dynamiclib -undefined dynamic_lookup -o libmylib.dylib mylib.o

install:
	cp libmylib.dylib ../

clean:
	rm -f *.o *.dylib *.so

.PHONY: all linux mac install clean