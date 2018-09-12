all: compile run

compile:
	g++ --std=c++11 ../solve.cpp -o ../solve.exe
	g++ --std=c++11 ../tests/tests.cpp -lgtest -lgtest_main -lpthread -o ../tests/tests.exe

run:
	../tests/tests.exe
