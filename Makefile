CC = g++
FLAGS = -Wall -Werror -Wextra -W

MAIN_FILE = ManualTest/main.cpp
TEST_FILES = Tests/test.cpp
MATRIX_FILES = ArithAndComarison/*.cpp CalcMatrix/*.cpp CheckCorrect/*.cpp Tools/*.cpp Resize/*.cpp

SRCS = $(wildcard $(MATRIX_FILES))
SRCS_TEST = $(wildcard $(MATRIX_FILES) $(TEST_FILES))


all: matrix.a

style:
	@clang-format --style=Google -i matrix.h $(MAIN_FILE) $(MATRIX_FILES) $(TEST_FILES)

clang:
	@clang-format --style=Google -n matrix.h $(MAIN_FILE) $(MATRIX_FILES) $(TEST_FILES)
	
matrix.a:
	$(CC) $(FLAGS) -c $(SRCS)
	@ar rvs matrix.a *.o

main: matrix.h $(MAIN_FILE) $(MATRIX_FILES)
	@$(CC) $(FLAGS) matrix.h $(MAIN_FILE)  $(MATRIX_FILES) -o main
	@./main
	@rm main
	
test: $(SRCS_TEST)
	@$(CC) $(FLAGS) $(SRCS_TEST) -o test -lgtest -lgmock -pthread
	@./test
	@rm test

clean:
	@rm *.out *.gch *.o *.d test main matrix.a
