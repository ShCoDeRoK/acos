all: compile run

compile:
	g++ ../solve.cpp -o ../solve.exe
	g++ ../tests/tests.cpp -lgtest -lgtest_main -lpthread -o ../tests/tests.exe

run:
	../tests/tests.exe
