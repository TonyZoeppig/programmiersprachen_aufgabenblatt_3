#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definition for clear
TEST_CASE("list clear()", "list") {
    List<int> int_list{};
    for (int i = 0; i <= 10; ++i) {
        int_list.push_front(i);
    }
    int_list.clear();
    REQUIRE(int_list.size() == 0);

    List<double> double_list{};
    double_list.clear();
    REQUIRE(double_list.size() == 0);

    List<char> char_list{};
    char_list.push_back('a');
    char_list.clear();
    REQUIRE(char_list.size() == 0);
}

//test case definition for copy constructor
TEST_CASE("List(List<T> const& list)", "list") {
    List<int> int1{};
    for (int i = 0; i <= 42; ++i) {
        int1.push_front(i);
    }
    List<int> int2(int1);
    REQUIRE(int1.front() == int2.front());
    REQUIRE(int1.back() == int2.back());
    REQUIRE(int1.size() == int2.size());

    List<int> int3{};
    List<int> int4(int3);
    REQUIRE(int3.size() == 0);
    REQUIRE(int4.size() == 0);

    List<char> char1{};
    char1.push_front('v');
    List<char> char2(char1);
    REQUIRE(char1.front() == char2.front());
    REQUIRE(char1.back() == char2.back());
    REQUIRE(char1.size() == char2.size());
}

//test case definition for unifying assignment operator
TEST_CASE("operator =", "list") {
    List<int> int1{};
    for (int i = 0; i <= 42; ++i) {
        int1.push_front(i);
    }
    int first_element = int1.front();
    int last_element = int1.back();
    int list_size = int1.size();

    List<int> int2 = int1;
    REQUIRE(int2.front() == first_element);
    REQUIRE(int2.back() == last_element);
    REQUIRE(int2.size() == list_size);

    List<int> int3{};
    List<int> int4 = int3;
    REQUIRE(int3.size() == 0);
    REQUIRE(int4.size() == 0);

    List<char> char1{};
    char1.push_front('v');
    List<char> char2 = char1;
    REQUIRE(char2.front() == 'v');
    REQUIRE(char2.size() == 1);
}

//test case definition for member reverse function
TEST_CASE("member reverse function", "list") {
    List<int> int1{};
    for (int i = 0; i <= 30; ++i) {
        int1.push_front(i);
    }
    int first_element = int1.front();
    int last_element = int1.back();
    int1.reverse();
    REQUIRE(int1.front() == last_element);
    REQUIRE(int1.back() == first_element);

    List<double> double1{};
    double1.reverse();
    REQUIRE(double1.size() == 0);

    List<char> char1{};
    char1.push_front('z');
    char1.reverse();
    REQUIRE(char1.back() == 'z');
}

//test case definition for free reverse function
TEST_CASE("free reverse function", "list") {
    List<int> int1{};
    for (int i = 0; i <= 30; ++i) {
        int1.push_front(i);
    }
    int first_element = int1.front();
    int last_element = int1.back();
    List<int> int2 = reverse(int1);
    REQUIRE(int2.front() == last_element);
    REQUIRE(int2.back() == first_element);

    List<double> double1{};
    List<double> double2 = reverse(double1);
    REQUIRE(double2.size() == 0);

    List<char> char1{};
    char1.push_front('z');
    List<char> char2 = reverse(char1);
    REQUIRE(char2.back() == 'z');
}

//test case definition for == operator
TEST_CASE("operator ==", "list") {
    List<int> int1{};
    List<int> int2{};
    REQUIRE(int1 == int2);

    List<int> int3{};
    for (int i = 0; i <= 30; ++i) {
        int3.push_front(i);
    }
    List<int> int4{};
    int4.push_front(2);
    REQUIRE(!(int3 == int4));

    List<char> char1{};
    char1.push_front('1');
    char1.push_front('A');
    List<char> char2{};
    char2.push_front('1');
    char2.push_front('A');
    REQUIRE(char1 == char2);
}

//test case definition for != operator
TEST_CASE("operator !=", "list") {
    List<int> int1{};
    List<int> int2{};
    REQUIRE(!(int1 != int2));

    List<int> int3{};
    for (int i = 0; i <= 10; ++i) {
        int3.push_front(i);
    }
    List<int> int4{};
    int4.push_front(0);
    REQUIRE(int3 != int4);

    List<char> char1{};
    char1.push_front('1');
    char1.push_front('A');
    List<char> char2{};
    char2.push_front('1');
    char2.push_front('A');
    REQUIRE(!(char1 != char2));
}

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}




