#include "testfile.h"

TEST(QUEUE_TEST, out_test) { std::queue<int> arr; }

TEST(QUEUE_TEST, test_1) {
  s21::queue<int> arr1;
  std::queue<int> arr2;

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(QUEUE_TEST, test_2) {
  s21::queue<int> arr1 = {1, 2, 3};

  ASSERT_EQ(arr1.size(), 3);
}

TEST(QUEUE_TEST, test_3) {
  s21::queue<int> arr1 = {1, 2, 3};
  s21::queue<int> arr2(arr1);

  ASSERT_EQ(arr2.size(), 3);
}

TEST(QUEUE_TEST, test_4) {
  s21::queue<int> arr1 = {1, 2, 3};
  s21::queue<int> arr2(std::move(arr1));

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(QUEUE_TEST, test_5) {
  s21::queue<int> arr1 = {1, 2, 3};
  s21::queue<int> arr2;

  arr2 = std::move(arr1);

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(QUEUE_TEST, test_6) {
  s21::queue<int> arr1 = {1, 2, 3};

  ASSERT_EQ(arr1.front(), 1);
  ASSERT_EQ(arr1.back(), 3);
}

TEST(QUEUE_TEST, test_7) {
  s21::queue<int> arr1 = {1, 2, 3};
  arr1.insert_many_back(1, 2, 4, 4, 4, 3);
}