CXX = g++
CC = gcc

AUTOR = thucydil AKA Darkhan-Sol0 & hollisgr

VERSION = 0.69
BRANCH = none

EXEC = s21_containers.a

SOURCE = $(wildcard s21_conteiners/*/*.tpp s21_conteinersplus/*/*.tpp)
HEADER = $(wildcard s21_containers.h s21_containersplus.h s21_conteiners/*/*.h s21_conteinersplus/*/*.h)

GTEST = $(wildcard testfiles/testfile.cpp)
TPPTEST = $(wildcard testfiles/*.tpp testfiles/*.h)

CXXFLAGS = -std=c++17 -pthread -Wall -Werror -Wextra 
LIBFLAGS = -std=c++17 -lgtest_main -lgtest

VALGRIND = valgrind --tool=memcheck --leak-check=yes

CLANG = clang-format -style=Google

all: clean test

clean: clean_test clean_report
	rm -rf *.o $(EXEC)

test:
	$(CXX) $(CXXFLAGS) -o test $(GTEST) $(LIBFLAGS) 
	./test

clean_test:
	rm -rf test

test_val:
	$(CXX) $(CXXFLAGS) -o test $(GTEST) $(LIBFLAGS) 
	$(VALGRIND) ./test

gcov_report: clean_test clean_report
	$(CXX) --coverage $(GTEST) -o $@ $(LIBFLAGS) -o test
	./test
	gcovr -r . --html-details -o gcov_report.html
	# ~/.local/bin/gcovr -r . --html-details -o gcov_report.html
	mkdir GCOVRreport
	mv *.html *.css GCOVRreport
	rm -rf *.gcno *.gcda

lcov_report: clean_test clean_report
	$(CXX) -fprofile-arcs -ftest-coverage $(GTEST) -o $@ $(LIBFLAGS) -o test
	./test
	lcov --capture --directory . --output-file coverage.info --ignore-errors mismatch,mismatch # --ignore-errors inconsistent 
	genhtml coverage.info --output-directory coverage_report
	rm -rf *.gcno *.gcda
	
open_report_l:
	firefox coverage_report/index.html

open_report:
	firefox GCOVRreport/gcov_report.html

clean_report:
	rm -rf *.gcno *.gcda *.html *.css GCOVRreport *.info coverage_report

format:
	$(CLANG) -n $(SOURCE) $(HEADER) $(GTEST) $(TPPTEST)

setformat:
	$(CLANG) -i $(SOURCE) $(HEADER) $(GTEST) $(TPPTEST)

commit:
	@read -p "Enter commit message: " input; \
	git add -A; \
	git commit -m "$$input - $(EXEC) v:$(VERSION) - $(shell date +'%Y-%m-%d %H:%M')"; \
	git push origin $(BRANCH)