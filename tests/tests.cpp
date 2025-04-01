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


TEST(ShellReadLength, NoInput) {
	StdinMock::setInput("");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(0, len);
	ASSERT_STREQ("", input);
}

TEST(ShellReadLength, NormalInput) {
	StdinMock::setInput("ls");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(2, len);
	ASSERT_STREQ("ls", input);
}

TEST(ShellReadLength, NoTrailingSpace) {
	StdinMock::setInput("ls ");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(2, len);
	ASSERT_STREQ("ls", input);
}

TEST(ShellReadLength, OnlyOneSpaceBetweenArgs) {
	StdinMock::setInput("python3  -m     http.server");
	char* input = shell_read();
	StdinMock::restore();

	size_t len = strnlen(input, INPUT_MAX_SIZE);
	ASSERT_EQ(22, len);
	ASSERT_STREQ("python3 -m http.server", input);
}

TEST(ShellSplitArgs, SplitOneArg) {
	StdinMock::setInput("ls");
	char* input = shell_read();
	StdinMock::restore();

	char **args = shell_split_args(input);
	ASSERT_STREQ("ls", args[0]);
	ASSERT_EQ(NULL, args[1]);
}

TEST(ShellSplitArgs, SplitTwoArgs) {
	StdinMock::setInput("ls -la");
	char* input = shell_read();
	StdinMock::restore();

	char **args = shell_split_args(input);
	ASSERT_STREQ("ls", args[0]);
	ASSERT_STREQ("-la", args[1]);
	ASSERT_EQ(NULL, args[2]);
}

TEST(ShellSplitArgs, Split10Args) {
	StdinMock::setInput("python3 run.py this py file has way too many parameters");
	char* input = shell_read();
	StdinMock::restore();

	char **args = shell_split_args(input);
	ASSERT_STREQ("python3", args[0]);
	ASSERT_STREQ("run.py", args[1]);
	ASSERT_STREQ("this", args[2]);
	ASSERT_STREQ("py", args[3]);
	ASSERT_STREQ("file", args[4]);
	ASSERT_STREQ("has", args[5]);
	ASSERT_STREQ("way", args[6]);
	ASSERT_STREQ("too", args[7]);
	ASSERT_STREQ("many", args[8]);
	ASSERT_STREQ("parameters", args[9]);
	ASSERT_EQ(NULL, args[10]);
}