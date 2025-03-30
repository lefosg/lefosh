#include <gtest/gtest.h>
#include "../src/app/lefosh.hpp"
#include <string.h>


// Mock for stdin to provide static test input
class StdinMock {
  	public:
      	static void setInput(const char* input) {
			// Create a temporary file
			FILE* temp = tmpfile();
			if (temp) {
				fputs(input, temp);
				rewind(temp);
				// Redirect stdin to our temp file
				_original_stdin = stdin;
				stdin = temp;
			}
		}
      
		static void restore() {
			if (_original_stdin) {
				// Close the temp file and restore stdin
				fclose(stdin);
				stdin = _original_stdin;
				_original_stdin = nullptr;
			}
		}
	private:
		static FILE* _original_stdin;
};
  
FILE* StdinMock::_original_stdin = nullptr;

//no spaces in input
TEST(ShellReadLength, NormalInput) {
	StdinMock::setInput("ls");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(2, len);
}

TEST(ShellReadLength, NoTrailingSpace) {
	StdinMock::setInput("ls ");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(2, len);
}

TEST(ShellReadLength, OnlyOneSpaceBetweenArgs) {
	StdinMock::setInput("python3  -m     http.server");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(22, len);
}
