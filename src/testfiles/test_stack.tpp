#include "testfile.h"

TEST(STACK_TEST, out_test) { std::stack<int> arr; }

TEST(STACK_TEST, test_1) { s21::stack<int> arr1; }

TEST(STACK_TEST, test_2) {
  s21::stack<int> arr1 = {1, 2, 3};

  ASSERT_EQ(arr1.size(), 3);
}

TEST(STACK_TEST, test_3) {
  s21::stack<int> arr1 = {1, 2, 3};
  s21::stack<int> arr2(arr1);

  ASSERT_EQ(arr2.size(), 3);
}

TEST(STACK_TEST, test_4) {
  s21::stack<int> arr1 = {1, 2, 3};
  s21::stack<int> arr2(std::move(arr1));

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(STACK_TEST, test_5) {
  s21::stack<int> arr1 = {1, 2, 3};
  s21::stack<int> arr2;

  arr2 = std::move(arr1);

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(STACK_TEST, test_6) {
  s21::stack<int> arr1 = {1, 2, 3};

  ASSERT_EQ(arr1.top(), 1);
}

TEST(STACK_TEST, test_7) {
  s21::stack<int> arr1 = {1, 2, 3};

  arr1.insert_many_back(1, 5, 3, 5, 7);
}