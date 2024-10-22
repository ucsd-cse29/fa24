# Testing with `assert` and Makefiles
<!-- ADD INTRO BLURB HERE?? -->
In this section, we will be working on one of the functions that is part of PA2 and provide a cool way to incorporate unit testing into your `main()` functions without needing to change/comment lots of lines of code!

Finally, we will introduce a convenient way to compile our programs using `Makefiles` and the `make` utility!

## Testing with `assert`

**Task:** While on your `ieng6` account within your PA2 repo directory perform the following steps:

<!-- 1. Create a new file called `pwcrack.h` with the following content:
    ```
    #ifndef PWCRACK_H
    #define PWCRACK_H

    uint8_t hex_to_byte(unsigned char h1, unsigned char h2);

    #endif
    ```
    This file is known as a C header file (hence the `.h` extension). Similar to an interface in Java, the header contains function signatures and other definitions that can be shared across multiple C files. Any function **not** declared in the `.h` file cannot be accessed by other source files.The functions declared in the header will be defined in its corresponding `.c` file (`pwcrack.c` in this case). As you continue to work on your PA, you can (and should) add the function declarations for the other functions you implement to this file.

    **NOTE:** Any new functions or changes to the function signature in the `.c` file **must** be updated in the corresponding `.h` file. -->



1. Open your `pwcrack.c` file that we created/renamed in the previous portion of the lab. We are providing an incomplete implementation of the `hex_to_byte` function. Add the following function to your C file and complete it by determining what the function should return. To see the function's intended behavior, refer to the PA2 spec found [here](https://github.com/ucsd-cse29/pa2-hashing-and-passwords?tab=readme-ov-file#functions---milestone-1).

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
            x += h1 - '0';
        }
        else if (h1 >= 'a' && h1 <= 'f') {
            x += h1 - 'a' + 10;
        }

        // Convert h2 to a decimal value
        if (h2 >= '0' && h2 <= '9') {
            y += h2 - '0';
        }
        else if (h2 >= 'a' && h2 <= 'f') {
            y += h2 - 'a' + 10;
        }
        // TODO: Determine what the function should return
    }
    ```

    <!-- **In your notes:** Mention what the function should return based on the PA2 spec and why? -->


<!-- 3. You may have noticed that we did not include a `main()` function in either of these files. A `main()` function is necessary to execute a program, so a logical next question may be, "Where will my program execution start from?" We'll include the `main()` function in a seperate file, to isolate it away from our other functions. 

    We will be creating two different files with `main()` functions that will serve different purposes: 
    - `main.c` will be used for running your password cracker as a whole with the command-line argument(s) it will need to take. 
    - `test.c` will use `assert()` statements to unit test the various functions you will be implementing for PA2. 


    In this lab, we will be demonstrating the use of command-line arguments to only test the `hex_to_byte` function but you will extend this to work for your complete password cracker implementation.
    <br>

    Create a new file called `main.c` and add the following content:
    
    **IMPORTANT NOTE:** If you have already defined a `main()` function somewhere in your code, move your function to this new file. You may keep the portion of your `main()` function that you have written and simply add the `#include "pwcrack.h"` line to the top of the file and the for loop provided in the code below for the purposes of this lab! -->

2. Now we will need to add a `main()` function to this file to give the program an entrypoint. Copy the following main function into your `pwcrack.c` file.

    **NOTE:** If you already have a `main()` function from working on the PA, you can keep it as is and focus on the unit testing portion of the code given below.

    ```
    int main(int argc, char **argv) {

        // UNIT TESTING SECTION
        int test = 0; // Set this variable to 1 to run unit tests instead of the entire program
        if (test) {
            assert(hex_to_byte('a', '2') == 162);
            // ADD MORE TESTS HERE. MAKE SURE TO ADD TESTS THAT FAIL AS WELL TO SEE WHAT HAPPENS!
            
            printf("ALL TESTS PASSED!\n");
            return 0;
        }

        // MAIN PROGRAM SECTION
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
    You will note that this `main()` function serves two purposes:
    
    - It parses your command-line arguments to your program and runs your password cracker. In this lab, we will be demonstrating the use of command-line arguments to only test the `hex_to_byte` function but you will extend this to work for your complete password cracker implementation.
    - The `if` statement at the beginning of the `main()` function is a way to unit test specific functions as you work on your PA. Setting the value of the `test` variable to `1` will run the code within the `if` statement that should have several `assert()` statements to test your individual functions (we have provided an example test for `hex_to_byte`). If all your tests pass, the program will print `ALL TESTS PASSED!` and exit successfully. If not, you will receive an error when you run your program with `int test = 1;`.


    
    <!-- This file contains the `main()` function that will call the `hex_to_byte` function on the command-line arguments passed to the program (notice the use of `argv`). The `#include "pwcrack.h"` line includes the header file we created earlier. This allows the `main()` function to know about the `hex_to_byte` function we defined in `pwcrack.c`. Notice that the C libraries implemented use the `<>` around the filename, while the custom header file uses `""`.  -->

<!-- 4. Now, create another file called `test.c` and add the following content:
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

    This `test.c` file can now be used to test each individual function you write with `assert()` statements without the need to run the program as a whole. This can be very useful for debugging and ensuring that each function is working as expected before moving on to the next one. -->

<!-- 5. Since we have split up the function's definition and the `main()` function into separate files, we will need to tell `gcc` to compile all the files necessary to get our executable. To do this, run the following command:
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
    and run `main.out` with the appropriate command-line arguments to see the results of your `hex_to_byte` function for various inputs. -->

3. **Commit and push your changes to Github.** Make sure to include the new files you created in your commit.

**In your notes:** Briefly explain what you had the `hex_to_byte` function return and why?

## Makefiles
Thus far, we have been typing out the various `gcc` commands needed to compile our C programs. We have also learned some command-line flags that can be useful when compiling our programs like `-g` for debugging information, `-std=c11` to use the correct C version when compiling on `ieng6` and `-fsanitize` for memory errors. Wouldn't it be nice if we could just type one command and have all the necessary files compiled with the correct flags? This is where `make` comes in.

`make` is a utility for building C programs. A `Makefile` is a file that contains a set of rules that tell the `make` utility what commands it should run for that rule. We will be creating a `Makefile` with rules to compile our C programs with the correct flags and dependencies.

**Task:** Perform the following steps to create a `Makefile` for your PA2 project:
1. In your PA2 repository, create a new file named `Makefile` and add the following content to it:
    <!-- MAYBE WE HAVE THE STUDENTS ADD THE all RULE THEMSELVES AND ASK A QUESTION ABOUT IT AT THE END? -->
    ```
    all: pwcrack
      
    pwcrack: pwcrack.c
        gcc -std=c11 -Wall -Wno-unused-variables -fsanitize=address -g pwcrack.c -o pwcrack
    
    clean:
        rm -f pwcrack
    ```
    **IMPORTANT NOTE:** The indentation in the `Makefile` is done with a `TAB` character, not spaces. Make sure to use a `TAB` character when indenting the commands in the `Makefile`.

    **NOTE:** If your file names are different than what is given above at this point, change the rules to match the file names you are using.

2. Now, in your terminal, run `make all`. This will perform the same operation as running `gcc -std=c11 -fsanitize=address -g pwcrack.c -o pwcrack.out` without needing to type or remember that command! You should see the `pwcrack` file in your directory. However, if you run `make all` again, you will see that it doesn't recompile the files because they have not changed since the last time they were compiled. This is one of the benefits of using `make` to compile your programs.

3. Now run `make clean`. This should delete the executable file.
4. Next, run just `make` with no arguments. 

**In your notes:** What happend when you ran `make` without any arguments? Why do you think this is the case?

We now have a clean and simple way to compile our C programs with the correct flags and dependencies using `make`. This will be very useful as we continue to work on our PA2 project and need to compile our programs multiple times.


## If you are done early
- Work on PA2! Use the remaining time in lab to make progress on PA2 along with your group members and your tutor!
- Try adding a separate rule that would build pwcrack without address sanitizer enabled. Rename the rules so that one generates `pwcrack.asan`, and the other generates `pwcrack`. You may need to adjust `all` and `clean` as well to work correctly with this.
- If you are done with PA2 here is a fun extension you could work on: Extend your password cracker such that when given a hash, it will attempt to go through **all possible passwords of length 6** until the password is found.
