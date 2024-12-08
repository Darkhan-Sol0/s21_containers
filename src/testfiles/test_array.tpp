#include "testfile.h"

TEST(array_TEST, test_1) {
  std::array<int, 10> arr1 = {1, 2, 3, 4, 5, 6};
  s21::array<int> arr2 = {1, 2, 3, 4, 5, 6};

  ASSERT_EQ(arr1[2], arr2[2]);
}

TEST(array_TEST, test_2) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  s21::array<int> arr2(arr1);

  ASSERT_EQ(arr1[2], arr2[2]);
}

TEST(array_TEST, test_3) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  s21::array<int> arr2(std::move(arr1));
}

TEST(array_TEST, test_4) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  s21::array<int> arr2 = {1};

  arr2 = std::move(arr1);
}

TEST(array_TEST, test_5) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  ASSERT_EQ(arr1.front(), arr1.at(0));
}

TEST(array_TEST, test_6) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  ASSERT_EQ(arr1.back(), arr1.size());
}

TEST(array_TEST, test_7) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6, 5};
  ASSERT_EQ(arr1.max_size(), arr1.size());
}

TEST(array_TEST, test_8) {
  std::array<int, 6> arr2 = {1, 2, 3, 4, 5, 6};
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  ASSERT_EQ(*arr1.data(), *arr2.data());
  ASSERT_EQ(*arr1.begin(), *arr2.begin());
  ASSERT_EQ(*arr1.end(), *arr1.end());
}

TEST(array_TEST, test_9) {
  s21::array<int> arr1 = {1, 2, 3, 4, 5, 6};
  arr1.fill(8);
  ASSERT_EQ(arr1[3], 8);
}