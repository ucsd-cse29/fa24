# Pushing PA2 Code Github from `ieng6`

Make sure your `ieng6` account has [Github access](https://ucsd-cse29.github.io/fa24/week3/index.html#42---git-cli-commands).

1. Get your PA2 code onto ieng6; if you've already done a step, skip it
    - Follow the Github Classroom link from the [assignment page](https://github.com/ucsd-cse29/pa2-hashing-and-passwords) to create it
    - Log into ieng6 and clone the repository that was just made using `git clone [your-repository-link]`
    - Change into the directory with your PA2 repository

2. Check status by running `git status`. This will tell you (from the
command-line) what's going in the copy of your code you have checked out in the current working directory. If you haven't done any work yet, you'll see something like:

    ```
    On branch main
    Your branch is up to date with 'origin/main'.

    nothing to commit, working tree clean
    ```

    This means you haven't edited or created any files since you cloned the
    code. If you've done some work, you might see all kinds of things here, most
    likely `pwcrack.c`, which you may have created.

    You can also use `ls` to see what's going on. In a brand-new repository, that will show these files:

    ```
    $ ls
    CREDITS.md  DESIGN.md  README.md
    ```

3.  Create or edit `pwcrack.c`. If you already created `pwcrack.c` and the `git
status` command shows that it is new or modified, there's nothing to do here. If
you created it, but it has no modifications, open it and make a small edit (even
just adding a comment like `/* edit in lab */`) If you haven't created it yet,
you can create it using `vim`:

    ```
    $ vim pwcrack.c
    ```

    Then into the file type:

    ```
    #include <stdio.h>

    int main() {
        printf("did not find a matching password\n");
    }
    ```

    Then save and quit with `:wq`. Now `git status` should show it as a new
    untracked file:

    ```
    $ git status
    On branch main
    Your branch is up to date with 'origin/main'.

    Untracked files:
    (use "git add <file>..." to include in what will be committed)
            pwcrack.c

    nothing added to commit but untracked files present (use "git add" to track)
    ```

4. Add the change you made to “stage” it with `git add pwcrack.c`. After you do
this, `git status` will show it as ready to commit.

    ```
    $ git add pwcrack.c
    $ git status
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes to be committed:
    (use "git restore --staged <file>..." to unstage)
            new file:   pwcrack.c
    ```

5. Commit the file by using `git commit -m "your message here"`, where your
message might just be about adding or editing this file.

    ```
    $ git commit -m "created first version of pwcrack.c"
    [main 91d2f60] created first version of pwcrack.c
    1 file changed, 5 insertions(+)
    create mode 100644 pwcrack.c
    $ git status
    On branch main
    Your branch is ahead of 'origin/main' by 1 commit.
    (use "git push" to publish your local commits)

    nothing to commit, working tree clean
    ```

6. Push your work to Github by using `git push origin main`. Then you should be
able to visit your repository on Github and see the change!

    ```
    $ git push origin main
    Enumerating objects: 4, done.
    Counting objects: 100% (4/4), done.
    Delta compression using up to 8 threads
    Compressing objects: 100% (3/3), done.
    Writing objects: 100% (3/3), 383 bytes | 191.00 KiB/s, done.
    Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
    remote: Resolving deltas: 100% (1/1), completed with 1 local object.
    To github.com:ucsd-cse29-fa24/pa2-hashing-and-passwords-jpolitz.git
       0787d50..91d2f60  main -> main
    $ git status
    On branch main
    Your branch is up to date with 'origin/main'.

    nothing to commit, working tree clean
   ```

Check with the person sitting next to you to see if they got a similar result.
Did you run into any errors? Try understanding and fixing them: maybe you made a
typo in a command, or maybe something isn't set up correctly about your
connection to Github. Make sure you can create and edit files, add and commit
the changes, and push them to Github before moving on.
