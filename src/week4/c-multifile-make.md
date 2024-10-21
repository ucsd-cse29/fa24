# Working across multiple C files

<!-- ADD INTRO BLURB HERE?? -->

While on your `ieng6` account within your PA2 repo directory perform the following steps:

1. Create a new file called `pwcrack.h` with the following content:
    ```
    #ifndef PWCRACK_H
    #define PWCRACK_H

    uint8_t hex_to_byte(unsigned char h1, unsigned char h2);

    #endif
    ```
    This file is known as a C header file (hence the `.h` extension). It contains function declarations and other definitions that can be shared across multiple C files. The functions declared in this file will be defined in another `.c` file (`pwcrack.c` in case).

    <!-- ADD EXPLANATION FOR HEADER FILE HERE -->

2. Open your `pwcrack.c` file that we created/renamed in the previous portion of the lab. We are providing an incomplete implementation of the `hex_to_byte` function. Add the following function to your C file and complete it by determining what the function should return. To see what the functions intended behavior is refer to the [PA2 spec found here](https://github.com/ucsd-cse29/pa2-hashing-and-passwords?tab=readme-ov-file#functions---milestone-1).
**NOTE:** If you have already implemented your own `hex_to_byte` function, you can skip this step.
    ```
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>

    uint8_t hex_to_byte(unsigned char h1, unsigned char h2) {
        uint8_t x = 0;
        uint8_t y = 0;

        // Convert h1 to a decimal value
        if (h1 >= '0' && h1 <= '9') {
            x += h1 - 48;
        }
        else if (h1 >= 'a' && h1 <= 'f') {
            x += h1 - 87;
        }

        // Convert h2 to a decimal value
        if (h2 >= '0' && h2 <= '9') {
            y += h2 - 48;
        }
        else if (h2 >= 'a' && h2 <= 'f') {
            y += h2 - 87;
        }
        // TODO: Determine what the function should return
    }
    ```

3. You may have noticed that we did not include a `main()` function in either of these files. So a logical next question may be, "Where will my program execution start from?" The answer is that the `main()` function will be in a separate file. 

    Additionally, we will be creating two different files with `main()` functions that will server different purposes. One to be used for unit testing the various functions you will be implementing for PA2 using `assert()` statements and the other to be used for running your password cracker as a whole with the command-line argument(s) it will need to take. In this lab, we will be demonstrating the use of command-line arguments to only test the `hex_to_byte` function but you will extend this to work for your complete password cracker implementation.
    <br>

    Create a new file called `main.c` and add the following content:
    ```
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include "pwcrack.h"


    int main(int argc, char **argv) {
            if (argc < 2) {
                printf("Error: not enough arguments provided!\n");
                printf("Usage: %s <byte 1 in hex> <byte 2 in hex> ...\n", argv[0]);
                printf("Example: %s a2 b7 99\n", argv[0]);
                return 1;
            }
            int i = 1;
            for (; i < argc; i++) {
                printf("Value of hex byte %s is %d\n", argv[i], hex_to_byte(argv[i][0], argv[i][1]));
            }
    }
    ```
    This file contains the `main()` function that will call the `hex_to_byte` function on the command-line arguments passed to the program (notice the use of `argv`). The `#include "pwcrack.h"` line includes the header file we created earlier. This allows the `main()` function to know about the `hex_to_byte` function we defined in `pwcrack.c`.

    <br>

4. Now, create another file called `test.c` and add the following content:
    ```
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <assert.h>

    #include "functions.h"

    int main() {

        assert(hex_to_byte('a', '2') == 162);
        // ADD MORE TESTS HERE. MAKE SURE TO ADD TESTS THAT FAIL AS WELL TO SEE WHAT HAPPENS!
        
        printf("ALL TESTS PASSED!\n");
    }
    ```

    This file contains the `main()` function that will call the `hex_to_byte` function with various inputs and use `assert()` statements to check if the function is working as expected. If the function is working as expected, the program will print `ALL TESTS PASSED!` to the console. If the function is not working as expected, the program will print an error message for the failing test and exit.

    <br>

    This `test.c` file can now be used to test each individual function you write with `assert()` statements without the need to run the program as a whole. This can be very useful for debugging and ensuring that each function is working as expected before moving on to the next one.

5. Since we have split up the function's definition and the `main()` function into separate files, we will need to tell `gcc` to compile all the files necessary to get our executable. To do this, run the following command:
    ```
    gcc -o test.out test.c pwcrack.c
    ```
    This command tells `gcc` to compile the `test.c` file and the `pwcrack.c` file and output the executable as `test.out`. If you have any other files that need to be compiled, you can add them to the end of the command.
    Running `./test.out` will run the various `assert()` statements in the `test.c` file and print out the results of the tests.
    <br>
    
    Similarly, to compile the `main.c` file, run the following command:
    ```
    gcc -o main.out main.c pwcrack.c
    ```
    and run `main.out` with the appropriate command-line arguments to see the results of your `hex_to_byte` function for various inputs.

    <!-- ADD A WRITE IN NOTES SECTION HERE -->

6. **Commit and push your changes to Github.** Make sure to include the new files you created in your commit.

# Makefiles
Thus far, we have been typing out the various `gcc` commands needed to compile our C programs. We have also learned some command-line flags that can be useful when compiling our programs like `-g` for debugging information (and we will be learning an additional one in the next section of this lab!). Wouldn't it be nice if we could just type one command and have all the necessary files compiled with the correct flags? This is where `Makefiles` come in.

A `Makefile` is a file that contains a set of rules that tell the `make` utility what commands it should run for that rule. We will be creating a `Makefile` with rules to compile our C programs with the correct flags and dependencies.

1. In your PA2 repository, create a new file named `Makefile` and add the following content to it:
    <!-- MAYBE WE HAVE THE STUDENTS ADD THE all RULE THEMSELVES AND ASK A QUESTION ABOUT IT AT THE END? -->
    ```
    all: main test

    main: main.c pwcrack.c
        gcc main.c pwcrack.c -g -o main.out

    test: test.c pwcrack.c
            gcc test.c pwcrack.c -g -o test.out

    clean:
            rm -rf *.out
    ```
    **IMPORTANT NOTE:** The indentation in the `Makefile` is done with a `TAB` character, not spaces. Make sure to use a `TAB` character when indenting the commands in the `Makefile`.
    **NOTE:** If your file names are different than what is given above at this point, change the rules to match the file names you are using.
    ***EXPLANATION FOR MAKEFILE HERE***
    <!-- ADD EXPLANATION FOR MAKEFILE HERE -->

2. Now, in your terminal, run `make main`. This will perform the same operation as running `gcc -o main.out main.c pwcrack.c -g`. You should see the `main.out` file in your directory. However, if you run `make main` again, you will see that `make` will not recompile the files because they have not changed since the last time they were compiled. This is one of the benefits of using `make` to compile your programs.
    <br>

    Similarly, running `make test` will compile the `test.c` file and the `pwcrack.c` file into an executable called `test.out`.

3. Now run `make clean`. This will remove all the `.out` executable files in your directory.
4. Next, run simply `make`. **Write in your notes:** What do you see when you run `make` without any arguments? Why do you think this is the case?

We now have a clean and simple way to compile our C programs with the correct flags and dependencies using `make`. This will be very useful as we continue to work on our PA2 project and need to compile our programs multiple times.