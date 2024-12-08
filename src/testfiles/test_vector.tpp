#include "testfile.h"

TEST(VECTOR_TEST, test_1) {
  s21::vector<int> arr1;
  std::vector<int> arr2;
  arr1.push_back(1);
  arr2.push_back(1);
  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(*arr1.begin(), *arr2.begin());
}

TEST(VECTOR_TEST, test_3) {
  s21::vector<int> arr1;
  std::vector<int> arr2;

  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(VECTOR_TEST, test_4) {
  s21::vector<int> arr1(2);
  std::vector<int> arr2(2);

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(VECTOR_TEST, test_5) {
  s21::vector<int> arr1(2);

  s21::vector<int> arr2(arr1);

  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(VECTOR_TEST, test_6) {
  s21::vector<int> arr1 = {1, 2, 3};

  s21::vector<int> arr2(std::move(arr1));

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(VECTOR_TEST, test_7) {
  s21::vector<int> arr1;
  std::vector<int> arr2;

  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  arr1.push_back(2);
  arr2.push_back(2);

  arr1.pop_back();
  arr2.pop_back();

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(VECTOR_TEST, test_8) {
  s21::vector<int> arr1;

  ASSERT_THROW(arr1.front(), std::out_of_range);
  ASSERT_THROW(arr1.back(), std::out_of_range);

  ASSERT_THROW(*arr1.begin(), std::invalid_argument);
}

TEST(VECTOR_TEST, test_9) {
  s21::vector<int> arr1;
  std::vector<int> arr2;
  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(VECTOR_TEST, test_10) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5};

  s21::vector<int> arr2 = std::move(arr1);

  arr1 = {1, 2, 3, 4, 5};

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(VECTOR_TEST, test_11) {
  s21::vector<int> arr1;

  arr1.insert(arr1.begin(), 1);

  arr1.insert(arr1.begin(), 2);

  arr1.insert(arr1.end(), 3);

  arr1.insert(++arr1.begin(), 1);

  arr1.clear();

  arr1.insert(arr1.end(), 1);

  ASSERT_EQ(arr1.front(), 1);
  ASSERT_EQ(arr1.back(), 1);
}

TEST(VECTOR_TEST, test_12) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5, 6};

  ASSERT_EQ(*arr1.data(), 1);
}

TEST(VECTOR_TEST, test_13) {
  s21::vector<int> arr1 = {1};
  s21::vector<int> arr2 = {1};

  arr1.erase(arr1.begin());
  arr2.erase(arr2.end());

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 0);
}

TEST(VECTOR_TEST, test_14) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5};

  arr1.erase(arr1.begin());

  arr1.erase(++arr1.begin());

  arr1.erase(arr1.end());

  ASSERT_EQ(arr1.front(), 2);
  ASSERT_EQ(arr1.back(), 4);
}

TEST(VECTOR_TEST, test_15) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5, 6};

  ASSERT_EQ(arr1.at(3), 4);
  ASSERT_EQ(arr1[3], 4);
}

TEST(VECTOR_TEST, test_16) {
  s21::vector<int> arr1 = {1};

  arr1.reserve(10);

  ASSERT_EQ(arr1.capacity(), 10);

  arr1.shrink_to_fit();

  ASSERT_EQ(arr1.capacity(), arr1.size());
}

TEST(VECTOR_TEST, test_17) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5, 6};

  arr1.insert_many(arr1.begin(), 1, 2, 3, 4);
}

TEST(VECTOR_TEST, test_18) {
  s21::vector<int> arr1 = {1, 2, 3, 4, 5, 6};

  arr1.insert_many_back(1, 2, 3, 4);
}

TEST(VECTOR_TEST, test_19) {
  s21::vector<int> arr1 = {1};
  arr1.pop_back();
}