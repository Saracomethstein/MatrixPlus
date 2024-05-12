CC = g++
FLAGS = -Wall -Werror -Wextra -W

MAIN_FILE = ManualTest/main.cpp
TEST_FILES = Tests/test.cpp
MATRIX_FILES = ArithAndComarison/*.cpp CalcMatrix/*.cpp CheckCorrect/*.cpp Tools/*.cpp Resize/*.cpp

SRCS = $(wildcard $(MATRIX_FILES))
SRCS_TEST = $(wildcard $(MATRIX_FILES) $(TEST_FILES))


all: s21_matrix_oop.a

style:
	@clang-format --style=Google -i s21_matrix_oop.h $(MAIN_FILE) $(MATRIX_FILES) $(TEST_FILES)

clang:
	@clang-format --style=Google -n s21_matrix_oop.h $(MAIN_FILE) $(MATRIX_FILES) $(TEST_FILES)
	
s21_matrix_oop.a:
	$(CC) $(FLAGS) -c $(SRCS)
	@ar rvs s21_matrix_oop.a *.o

main: s21_matrix_oop.h $(MAIN_FILE) $(MATRIX_FILES)
	@$(CC) $(FLAGS) s21_matrix_oop.h $(MAIN_FILE)  $(MATRIX_FILES) -o main
	@./main
	@rm main
	
test: $(SRCS_TEST)
	@$(CC) $(FLAGS) $(SRCS_TEST) -o test -lgtest -lgmock -pthread
	@./test
	@rm test

clean:
	@rm *.out *.gch *.o *.d test main s21_matrix_oop.a
