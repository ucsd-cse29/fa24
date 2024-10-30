## Other Helpful Functions

This PA explores several features that are straightforward to use, but there are
_many_ of them. We might add more to this list as the PA goes on! Here are a few
functions you'll probably find useful; try `man` on them, or follow the links,
or do your own searching and research. Don't forget all the functions from class
(e.g. `malloc` and other allocation functions, `strstr` and other string
manipulation functions, and so on). This list is mainly focused on things we
haven't tried in class.

- [`atoi`](https://cplusplus.com/reference/cstdlib/atoi/?kw=atoi): convert `char*` to integer

  For example:

  ```
  #include <stdio.h>
  #include <stdlib.h>

  int main() {
    char numeric[] = "123";
    int asnum = atoi(numeric);
    printf("%d\n", asnum * 2);
  }
  ```
- Time functions:
    - [`time`](https://en.cppreference.com/w/c/chrono/time): get the current time
    - [`localtime`](https://en.cppreference.com/w/c/chrono/localtime): convert the time to the current local time zone
    - [`strftime`](https://en.cppreference.com/w/c/chrono/strftime): print the time in a given format

      For example:

      ```
      #include <time.h>
      #include <stdio.h>

      int main() {
          char buffer[100];
          time_t now = time(NULL);
          struct tm *tm_info = localtime(&now);
          strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
          printf("%s", buffer);
      }
      ```