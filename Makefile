CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g
SRC = *.cc
SRC_TEST = tests/*.cc
OBJ = $(patsubst %.cc, %.o, $(wildcard $(SRC)))
OBJ_TEST = $(patsubst %.cc, %.o, $(wildcard $(SRC_TEST)))

.PHONY: all clean test gtest
$(OBJ): s21_matrix_oop.h
$(OBJ_TEST): tests/s21_matrix_oop_test.h

NAME:=$(shell uname -s)
ifeq ($(NAME), Linux) 
		LDFLAGS= -lgtest -lgmock -lpthread
else ifeq ($(NAME), Darwin)
		LDFLAGS= -lgtest -lgmock
endif
all: clean s21_matrix_oop.a  

s21_matrix_oop.a: $(OBJ)
		ar rcs s21_matrix_oop.a $^
		ranlib s21_matrix_oop.a
test: $(OBJ_TEST) s21_matrix_oop.a
		$(CXX) $^ $(LDFLAGS) -o $@
		./test
%.o: %.cc
		$(CXX) $(CXXFLAGS) -c $< -o $@
brew:
		/bin/bash -c "cd /opt/goinfre/${USER} && git clone https://github.com/Homebrew/brew homebrew"
		printf "eval \"%c(/opt/goinfre/${USER}/homebrew/bin/brew shellenv)\"\n\
brew update --force --quiet\n\
chmod -R go-w \"%c(brew --prefix)/share/zsh\"" "$$" "$$" >> /Users/${USER}/.zprofile 
install_gtest: 
		/bin/zsh -c "cd /opt/goinfre/${USER} && brew install lcov && \
		git clone https://github.com/google/googletest.git && \
		cd googletest && mkdir build && cd build && cmake .. && make && cp lib/*.a ../../homebrew/lib && \
		cp -r ../googletest/include/gtest ../../homebrew/include"		

clean:
		@rm -rf $(OBJ) $(OBJ_TEST)
		@rm -rf s21_matrix_oop.a test gtest test.dSYM/ 
		@rm -rf *.info *.gcno *.gcda report
		@rm -rf test/*.info tests/*.gcda tests/*.gcno

leaks: clean test
		leaks -atExit -- ./test
val: clean test
		valgrind --tool=memcheck --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
check:
		@cp ../materials/linters/.clang-format ./
		clang-format -n *.cc *.h tests/*.cc tests/*.h
		@rm -rf .clang-format
check2:
		@cp ../materials/linters/.clang-format ./
		clang-format -i *.cc *.h tests/*.cc tests/*.h
		@rm -rf .clang-format
gcov_report: clean add_coverage s21_matrix_oop.a $(OBJ_TEST)
		@$(CXX) $(CXXFLAGS) $(OBJ_TEST) s21_matrix_oop.a	$(LDFLAGS) -o test
		@./test
		@mkdir report
		lcov --ignore-errors mismatch --no-external -t "test" -q --no-recursion  -o test.info -c -d .  
		genhtml -o report test.info
		open report/index.html
		rm -rf *.gcda *.gcno *.out
add_coverage:
	$(eval CXXFLAGS += --coverage)

