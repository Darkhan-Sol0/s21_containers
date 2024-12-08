#include "testfile.h"

TEST(LIST_TEST, test_1) {
  s21::list<int> arr1;
  std::list<int> arr2;
  arr1.push_back(1);
  arr2.push_back(1);
  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(*arr1.begin(), *arr2.begin());
}

TEST(LIST_TEST, test_2) {
  s21::list<int> arr1;
  std::list<int> arr2;

  arr1.push_front(1);
  arr2.push_front(1);

  arr1.pop_front();
  arr2.pop_front();

  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(arr1.empty(), arr2.empty());
}

TEST(LIST_TEST, test_3) {
  s21::list<int> arr1;
  std::list<int> arr2;

  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(*arr1.end(), *arr2.end());
}

TEST(LIST_TEST, test_4) {
  s21::list<int> arr1(2);
  std::list<int> arr2(2);

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(LIST_TEST, test_5) {
  s21::list<int> arr1(2);

  s21::list<int> arr2(arr1);

  ASSERT_EQ(arr1.size(), arr2.size());
  ASSERT_EQ(arr1.max_size(), arr2.max_size());
}

TEST(LIST_TEST, test_6) {
  s21::list<int> arr1 = {1, 2, 3};

  s21::list<int> arr2(std::move(arr1));

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 3);
}

TEST(LIST_TEST, test_7) {
  s21::list<int> arr1;
  std::list<int> arr2;

  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  arr1.push_back(2);
  arr2.push_back(2);

  arr1.pop_back();
  arr2.pop_back();

  arr1.pop_front();
  arr2.pop_front();

  ASSERT_EQ(arr1.size(), arr2.size());
}

TEST(LIST_TEST, test_8) {
  s21::list<int> arr1;

  ASSERT_THROW(arr1.front(), std::out_of_range);
  ASSERT_THROW(arr1.back(), std::out_of_range);

  ASSERT_THROW(*arr1.begin(), std::invalid_argument);
  ASSERT_EQ(*arr1.end(), arr1.size());
}

TEST(LIST_TEST, test_9) {
  s21::list<int> arr1;
  std::list<int> arr2;
  arr1.push_back(1);
  arr2.push_back(1);

  arr1.push_back(2);
  arr2.push_back(2);

  arr1.push_front(3);
  arr2.push_front(3);

  arr1.push_front(4);
  arr2.push_front(4);

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_10) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5};
  s21::list<int> arr2 = std::move(arr1);

  arr1 = {1, 2, 3, 4, 5};

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_11) {
  s21::list<int> arr1;
  std::list<int> arr2;

  arr1.insert(arr1.begin(), 1);
  arr2.insert(arr2.begin(), 1);

  arr1.insert(arr1.begin(), 1);
  arr2.insert(arr2.begin(), 1);

  arr1.insert(arr1.end(), 1);
  arr2.insert(arr2.end(), 1);

  arr1.insert(++arr1.begin(), 1);
  arr2.insert(++arr2.begin(), 1);

  arr1.clear();
  arr2.clear();

  arr1.insert(arr1.end(), 1);
  arr2.insert(arr2.end(), 1);

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_12) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5};

  arr1.erase(arr1.begin());

  arr1.erase(++arr1.begin());

  arr1.erase(arr1.end());

  ASSERT_EQ(arr1.front(), 2);
  ASSERT_EQ(arr1.back(), 4);
}

TEST(LIST_TEST, test_13) {
  s21::list<int> arr1 = {1};
  s21::list<int> arr2 = {1};

  arr1.erase(arr1.begin());
  arr2.erase(arr2.end());

  ASSERT_EQ(arr1.size(), 0);
  ASSERT_EQ(arr2.size(), 0);
}

TEST(LIST_TEST, test_14) {
  s21::list<int> arr1 = {4, 3, 2, 1};
  s21::list<int> arr2 = {1, 2, 3, 4};

  arr1.sort();

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_15) {
  s21::list<int> arr1 = {4, 3, 2, 1};
  s21::list<int> arr2 = {1, 2, 3, 4};

  arr1.reverse();

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_16) {
  s21::list<int> arr1 = {1, 2, 3, 3, 3, 4, 4, 5, 6, 6, 6};
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.unique();

  ASSERT_EQ(arr1.front(), arr2.front());
  ASSERT_EQ(arr1.back(), arr2.back());
}

TEST(LIST_TEST, test_17) {
  s21::list<int> arr1 = {2, 3, 4};
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.merge(arr2);
}

TEST(LIST_TEST, test_18) {
  s21::list<int> arr1 = {2, 3, 4};
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.splice(arr1.begin(), arr2);
}

TEST(LIST_TEST, test_19) {
  s21::list<int> arr1 = {2, 3, 4};
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.splice(++arr1.begin(), arr2);
}

TEST(LIST_TEST, test_20) {
  s21::list<int> arr1 = {2, 3, 4};
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.splice(arr1.end(), arr2);
}

TEST(LIST_TEST, test_21) {
  s21::list<int> arr1;
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.splice(arr1.begin(), arr2);
}

TEST(LIST_TEST, test_22) {
  s21::list<int> arr1;
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.splice(arr1.end(), arr2);
}

TEST(LIST_TEST, test_23) {
  s21::list<int> arr1;
  s21::list<int> arr2 = {1, 2, 3, 4, 5, 6};

  arr1.merge(arr2);
}

TEST(LIST_TEST, test_24) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5, 6};
  s21::list<int> arr2;

  arr1.merge(arr2);
}

TEST(LIST_TEST, test_25) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5, 6};

  arr1.insert_many(arr1.begin(), 1, 2, 3, 4, 5);
}

TEST(LIST_TEST, test_26) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5, 6};

  arr1.insert_many_back(1, 2, 3, 4, 5);
}

TEST(LIST_TEST, test_27) {
  s21::list<int> arr1 = {1, 2, 3, 4, 5, 6};

  arr1.insert_many_front(1, 2, 3, 4, 5);
}