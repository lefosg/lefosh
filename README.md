### lefosh

My own implementation of a shell. 
Reference implementation that helped me get started: [link](https://brennan.io/2015/01/16/write-a-shell-in-c/)

Just wanted to get started with CMake and GoogleTest (even though I write in more of a C-like way).

PS: my nickname is lefos, thus, lefosh :)

### Description

The concept is that a shell is an infinite loop which takes input, processes it, and executes it.
All you need to do is write an `shell_loop` function and call it in `main`. Instictively, the loop function should have some functions within it that do the processing mentioned. Here we implement:
- `shell_read`
- `shell_split_args`
- `shell_exec`

First function reads input from the keyboard (makes sure to clean stdin too) -> beware the buffer overflows!
Second function processes the input. It creates an array of strings, which are the arguments (e.g. "ls -la" becomes "ls" "-la").
Third function executes the input.