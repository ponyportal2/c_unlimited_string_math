UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=CK_FORK=no valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
	SYSFLAG=-D LINUX
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=CK_FORK=no leaks -quiet -atExit --
	SYSFLAG=-D APPLE
endif
CFLAGS=-Wall -Werror -Wextra
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCESLIB=unlim_math.c
SOURCES100=tests.c unlim_math.a
SOURCESIB=test_ibbenber.c unlim_math.a
SOURCESLOCALTEST=localtest.c unlim_math.a

TESTS_SOURSES = $(wildcard ./tests/*.check)
TESTS_SOURSESIB = $(wildcard ./*.check)

unlim_math.a: clean
	gcc $(SYSFLAG) $(CFLAGS) -c $(SOURCESLIB)
	ar rc unlim_math.a *.o
	ranlib unlim_math.a
	rm -f *.o

cpplinth:
	python3 ../linters/cpplint.py *.h

style:
	clang-format --style=Google -n *.c *.h

stylef:
	clang-format --style=Google -i *.c *.h

clean:
	rm -f test *.gc* test.info log.xml *.log *.out tests100
	rm -f -rf report *.out.dSYM
	rm -rf *.a *.o *.test .test.c *.gcda *.gcno *.info test.c report test *.input *.output */*.exe

gcov_report: clean
	checkmk clean_mode=1 $(TESTS_SOURSESIB) > test_ibbenber.c
	gcc $(SYSFLAG) $(GFLAGS) $(CFLAGS) $(SOURCESLIB) test_ibbenber.c $(LFLAGS) -g -o test
	-./test > test.log
	bash test_log.sh
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
