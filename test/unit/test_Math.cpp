#include "CppUTest/TestHarness.h"
#include "Math.h"

TEST_GROUP(Math) {
};

TEST(Math, FirstTest) {
	FAIL("fail me");
}

TEST(Math, Sign_Int_Zero) {
	int number = 0;
	int expected = 0;
	int result = Math::sign(number);
	CHECK(expected == result);
}

TEST(Math, Sign_Int_Positive) {
	int number = 1;
	int expected = 1;
	int result = Math::sign(number);
	CHECK(expected == result);
}

TEST(Math, Sign_Int_Negative) {
	int number = -1;
	int expected = -1;
	int result = Math::sign(number);
	CHECK(expected == result);
}

TEST(Math, Sign_Double_Zero) {
	double number = 0.0;
	int expected = 0;
	int result = Math::sign(number);
	CHECK(expected == result);
}

TEST(Math, Sign_Double_Positive) {
	double number = 1.0;
	int expected = 1;
	int result = Math::sign(number);
	CHECK(expected == result);
}

TEST(Math, Sign_Double_Negative) {
	double number = -1.0;
	int expected = -1;
	int result = Math::sign(number);
	CHECK(expected == result);
}
