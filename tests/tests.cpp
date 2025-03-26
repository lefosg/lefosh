#include <gtest/gtest.h>
#include "../src/app/lefosh.hpp"

TEST(ShellRead, ShellRead_S) {
  ASSERT_EQ("ls", shell_read());
}

