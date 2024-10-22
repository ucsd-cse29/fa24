# Pushing PA2 Code to Github from `ieng6`

Make sure your `ieng6` account has [Github access](https://ucsd-cse29.github.io/fa24/week3/index.html#42---git-cli-commands).
0. Run `cs29fa24` after you are logged in. If you have already started working on your PA2 and had cloned the repository without running this command, you will need to reclone after running this command and continue working. This command sets up your working directory for CSE29 which is where you want to be working! 

1. Get your PA2 code onto ieng6; if you've already done a step, skip it
    - Follow the Github Classroom link from the [assignment page](https://github.com/ucsd-cse29/pa2-hashing-and-passwords) to create it
    - Log into ieng6 and clone the repository that was just made using `git clone [your-repository-link]`
    ```
    ~$ git clone git@github.com:ucsd-cse29/pa2-hashing-and-passwords.git
    Cloning into 'pa2-hashing-and-passwords'...
    remote: Enumerating objects: 34, done.
    remote: Counting objects: 100% (34/34), done.
    remote: Compressing objects: 100% (23/23), done.
    remote: Total 34 (delta 10), reused 0 (delta 0), pack-reused 0 (from 0)
    Receiving objects: 100% (34/34), 16.35 KiB | 8.17 MiB/s, done.
    Resolving deltas: 100% (10/10), done.
    ```
    - Change into the directory with your PA2 repository. In the example above, that would be `cd pa2-hashing-and-passwords`

2. Check status by running `git status`. This will tell you (from the
command-line) what's going in the copy of your code you have checked out in the current working directory. If you haven't done any work yet, you'll see something like:

    ```
    On branch main
    Your branch is up to date with 'origin/main'.

    nothing to commit, working tree clean
    ```
    You can also use `ls` to see what's going on. In a brand-new repository, that will show these files:

    ```
    $ ls
    CREDITS.md  DESIGN.md  README.md
    ```
    This means you haven't edited or created any files since you cloned the
    code. If you've done some work, you might see all kinds of things here, most
    likely `pwcrack.c`, which you may have created.

    **IMPORTANT NOTE:** If you have already done some work and your file name is not `pwcrack.c`, use the command `mv <your_file_name>.c pwcrack.c` to rename it (`mv` is also used to move files from one place to another in a filesystem). This will be important for future sections of the lab!

    

1.  Create or edit `pwcrack.c`. If you already created `pwcrack.c` and the `git
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

1. Add the change you made to “stage” it with `git add pwcrack.c`. After you do
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

1. Commit the file by using `git commit -m "your message here"`, where your
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

1. Push your work to Github by using `git push origin main`. Then you should be
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

**Write in your notes**: A screenshot of the commit(s) you pushed to Github from your terminal
and also a screenshot of the commit(s) on the Github website.

Check with the person sitting next to you to see if they got a similar result.
Did you run into any errors? Try understanding and fixing them: maybe you made a
typo in a command, or maybe something isn't set up correctly about your
connection to Github. Make sure you can create and edit files, add and commit
the changes, and push them to Github before moving on.
