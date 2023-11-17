CFLAGS = -Wall -Wextra -Werror -std=c11 
GCOV = -fprofile-arcs -ftest-coverage -fPIC -L/usr/local/Cellar/check/0.15.2/lib
FILES = back/*.c

OS = $(shell uname)

ifeq (${OS}, Linux)
	TEST_FLAGS = -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
else
	TEST_FLAGS = -lcheck
endif

all:
	uninstall install

gcov_report: test
	lcov -t viewer.a -o viewer.info -c -d .
	genhtml -o report viewer.info

ifeq (${OS}, Linux)
	cd report && firefox index.html
else
	cd report && open index.html
endif

test: clean viewer.a
	gcc ./tests/test.c -c
	gcc ${CFLAGS} ${TEST_FLAGS} ${GCOV} ${FILES} test.o -o test -I/usr/local/Cellar/check/0.15.2/include
	./test

viewer.a : viewer.o
	ar rc libs21_viewer.a *.o
	ranlib libs21_viewer.a
	cp libs21_viewer.a viewer.a

viewer.o: ${FILES}
	gcc ${CFLAGS} -c ${FILES}

clean:
	rm -rf *.o gcov_report *.a *.gcda *.gcno report viewer.info

rebuild: clean viewer.a

install: clean 
	mkdir build
	cd build && qmake ../view/ && make
	mkdir $(HOME)/Desktop/viewer/
	mkdir $(HOME)/Desktop/viewer/models
	cp -rf build/openGL_test.app $(HOME)/Desktop/viewer.app
	tar -xvf ./obj.zip
	cp -rf models/cat.obj $(HOME)/Desktop/viewer/models
	cp -rf models/cuberubik.obj $(HOME)/Desktop/viewer/models
	cp -rf models/simple_cube.obj $(HOME)/Desktop/viewer/models
	cp -rf models/skull.obj $(HOME)/Desktop/viewer/models
	

uninstall: clean 
	rm -rf build
	rm -rf $(HOME)/Desktop/viewer.app
	rm -rf ../Makefile
	rm -rf $(HOME)/Desktop/viewer
	rm -rf cat.obj cuberubik.obj simple_cube.obj skull.obj

dvi:
	doxygen Doxyfile
	open html/index.html

dist: 
	mkdir 3d_viewer1.0/
	mkdir 3d_viewer1.0/src
	cp back/*.c back/*.h view/*.h view/*.cpp Makefile 3d_viewer1.0/src/
	tar cvzf 3d_viewer1.0.tgz 3d_viewer1.0/
	rm -rf 3d_viewer1.0/