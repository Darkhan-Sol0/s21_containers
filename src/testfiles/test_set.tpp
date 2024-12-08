#include "testfile.h"

TEST(SET_TEST, test_1) {
  s21::set<int> arr;

  arr.insert(1);
  arr.insert(2);
  arr.insert(3);
  arr.insert(4);

  arr.clear();
}

TEST(SET_TEST, test_2) {
  s21::set<int> arr = {1, 2, 3};

  s21::set<int> arr1(arr);
}

TEST(SET_TEST, test_3) {
  s21::set<int> arr = {1, 2, 3};

  s21::set<int> arr1(std::move(arr));
}

TEST(SET_TEST, test_4) {
  s21::set<int> arr = {1, 2, 3};

  s21::set<int> arr1;

  arr1 = std::move(arr);
}

TEST(SET_TEST, test_5) {
  s21::set<int> arr1 = {1, 2, 3};
  std::set<int> arr2 = {1, 2, 3};

  ASSERT_EQ(*arr1.begin(), *arr2.begin());
  ASSERT_EQ(*arr1.end(), *arr2.end());
}

TEST(SET_TEST, test_6) {
  s21::set<int> arr1 = {1, 2, 3};
  s21::set<int> arr2 = {4, 5, 2};

  arr1.merge(arr2);
}

TEST(SET_TEST, test_7) {
  s21::set<int> arr1 = {1, 2, 3};
  s21::set<int> arr2 = {4, 5, 6};

  arr1.contains(2);
  arr1.contains(3);
  arr2.contains(2);
}

TEST(SET_TEST, test_8) {
  s21::set<int> arr1 = {1, 2, 3};

  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.max_size(), arr1.max_size());
}

TEST(SET_TEST, test_9) {
  s21::set<int> arr = {1, 2, 3, 4, 5, 6};

  arr.erase(arr.begin());
  arr.erase(++arr.begin());
  arr.erase(arr.end());
}

TEST(SET_TEST, test_10) {
  s21::set<int> arr1 = {4, 2, 3, 1};

  arr1.find(3);
}

TEST(SET_TEST, test_11) {
  s21::set<int> arr1 = {4, 2, 3, 1};

  arr1.insert_many(3, 4, 5, 7, 0, 8);
}