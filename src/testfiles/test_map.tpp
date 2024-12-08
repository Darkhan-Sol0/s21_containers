#include "testfile.h"

TEST(MAP_TEST, test_1) {
  s21::map<int, int> arr = {{2, 20}, {3, 30}};

  arr.insert({1, 10});
  arr.insert({1, 100});
  arr.insert({4, 50});
  arr.insert(5, 50);
  arr.insert_or_assign(4, 40);
  arr.insert_or_assign(7, 70);
  arr.clear();
  arr.insert_or_assign(7, 70);
  arr.insert_or_assign(6, 70);
}

TEST(MAP_TEST, test_2) {
  s21::map<int, int> arr = {{2, 20}, {3, 30}};

  s21::map<int, int> arr1(arr);
}

TEST(MAP_TEST, test_3) {
  s21::map<int, int> arr = {{2, 20}, {3, 30}};

  s21::map<int, int> arr1(std::move(arr));
}

TEST(MAP_TEST, test_4) {
  s21::map<int, int> arr = {{2, 20}, {3, 30}};

  s21::map<int, int> arr1;

  arr1 = std::move(arr);
}

TEST(MAP_TEST, test_5) {
  s21::map<int, int> arr1 = {{2, 20}, {3, 30}};
  std::map<int, int> arr2 = {{2, 20}, {3, 30}};

  ASSERT_EQ(*arr1.begin(), *arr2.begin());
  ASSERT_EQ(*arr1.end(), *arr2.end());
}

TEST(MAP_TEST, test_6) {
  s21::map<int, int> arr1 = {{2, 20}, {3, 30}, {1, 10}};
  s21::map<int, int> arr2 = {{4, 10}, {5, 10}, {6, 10}};

  arr1.merge(arr2);
}

TEST(MAP_TEST, test_7) {
  s21::map<int, int> arr1 = {{2, 20}, {3, 30}, {1, 10}};
  s21::map<int, int> arr2 = {{4, 10}, {5, 10}, {6, 10}};

  arr1.contains(2);
  arr1.contains(3);
  arr2.contains(2);
}

TEST(MAP_TEST, test_8) {
  s21::map<int, int> arr1 = {{2, 20}, {3, 30}, {1, 10}};

  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr1.max_size(), arr1.max_size());

  ASSERT_EQ(arr1.at(2), arr1[2]);
}

TEST(MAP_TEST, test_9) {
  s21::map<int, int> arr = {{3, 10}, {1, 20}, {4, 20},
                            {2, 20}, {5, 50}, {0, 10}};

  arr.erase(arr.begin());
  arr.erase(++arr.begin());
  arr.erase(arr.end());
}

TEST(MAP_TEST, test_10) {
  s21::map<int, int> arr = {{3, 10}, {1, 20}, {4, 20},
                            {2, 20}, {5, 50}, {0, 10}};

  arr.insert_many(std::make_pair(10, 214), std::make_pair(12, 214),
                  std::make_pair(13, 214));
}