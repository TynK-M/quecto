#include "../quecto.h"

TEST(assert_true) { ASSERT(1); }

TEST(assert_expression) {
  int a = 2;
  int b = 3;

  ASSERT(a + b == 5);
}
