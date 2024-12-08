#include "testfile.h"

TEST(multiset_TEST, test_1) {
  std::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2 = {2, 1, 2, 2, 3, 4, 5, 6};

  ASSERT_EQ(*arr1.begin(), *arr2.begin());
  ASSERT_EQ(*arr1.end(), *arr2.end());
  ASSERT_EQ(arr1.count(2), arr2.count(2));
  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(multiset_TEST, test_2) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2(std::move(arr1));
}

TEST(multiset_TEST, test_3) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2 = {2};
  arr2 = std::move(arr1);
}

TEST(multiset_TEST, test_4) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2(arr1);
}

TEST(multiset_TEST, test_5) {
  std::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2 = {2, 1, 2, 2, 3, 4, 5, 6};

  arr1.erase(arr1.find(2));
  arr2.erase(arr2.find(2));

  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(arr1.count(2), arr2.count(2));
  ASSERT_EQ(true, arr2.contains(2));
  ASSERT_EQ(arr2.max_size(), arr2.max_size());
  ASSERT_EQ(*arr1.equal_range(2).first, *arr2.equal_range(2).first);
}

TEST(multiset_TEST, test_6) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2 = {4};

  arr2.merge(arr1);
}

TEST(multiset_TEST, test_7) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  s21::multiset<int> arr2 = {4};

  arr1.erase(arr1.find(6));
  arr2.erase(arr2.find(4));
  arr1.erase(arr1.find(1));
}

TEST(multiset_TEST, test_8) {
  s21::multiset<int> arr1 = {2, 1, 2, 2, 3, 4, 5, 6};
  arr1.insert_many(2, 1, 2, 2, 3, 4, 5, 6);
}