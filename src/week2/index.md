# Week 2 – Project Management and Testing

## Meet your Group!

Meet your more permanent group for labs!

**Write down in notes**: In your groups, share, and note in the running notes
document (discussion leaders, you answer these as well!):

- How you'd like people to refer to you (pronounce your name/nickname, pronouns
like he/her/they, etc)
- Your major
- One of these that you didn't share in week 1:
    - A UCSD student organization you're a member of or interested in
    - Your favorite place you've found on campus so far
    - A useful campus shortcut or trick you know
- Your answer to the following question. Get to know your fellow group members!

FILL another icebreaker

## This Week

This week's lab will be focused on PA1, in a few different ways. The main
activity is around writing *good tests*, with some other activities around
managing your code repository.

### What Makes Tests Good?

We ask you for [a few categories of tests in
PA1](https://github.com/ucsd-cse29/pa1-utf8/blob/main/README.md#testing), which
make sure some basic (and not-so-basic) functionality is working. However, these
don't cover all the cases.

But what does it mean to “cover all the cases”? In general, there is no
theoretical limit to the number of strings we can create, so we can't
_exhaustively_ test all possible inputs. So we can't say “cover all the
cases” means that we write a test for every possible string.

Another way to think of this is in terms of _implementations_. There are many
correct and many incorrect (or incomplete) versions of the UTF analyzer that we
can imagine. Some of them are yours! Each test we write would _pass_ or _fail_
on each of these implementations. If it _passes_ on an _incorrect_
implementation, we might say that test doesn't “notice” or “witness” that
implementation being wrong. If it _fails_ on an _incorrect_ implementation
(while _passing_ on all the _correct_ ones), that's great! It means it is a
high-quality test that tells us something about a bug in an implementation.

Then, a way of thinking about “covering all the cases” is “how many bad
implementations would these tests catch?” Of course, there are infinitely many
bad implementations, so in general we can't expect perfection. But most
incorrect implementations are close to correct ones, and targeting tests at
common mistakes that might be made is a useful way to organize our thinking.

To that end, we've handwritten some bad implementations of the UTF8 analyzer.
Your job as a group will be to write a set of tests where some test _fails_ on
each of the bad implementations (while still being a correct test).

You can get started by making a private copy of this repository: FILL

Make just _one_ copy, and add all the members of your group to it.

FILL logistics details of writing the tests and checking what they do



### Managing Your Repository

We recommend making commits, and pushing, to your repository whenever you get to
a useful working checkpoint. That could mean that you got a new test to pass,
for example, or got the first version of one of the functions written, and so
on.  We also recommend using `.gitignore` to manage files that are created by
the compiler (but shouldn't be in version control).

- Practice creating a small commit in lab – add a test and/or some small amount
of code, and make a commit and push. Put a screenshot of the commit that you
pushed to Github into your notes document.

  - If you've been working this way all along, you can just share a small commit
  you made earlier.
  - If you're just getting started, this can be your first commit of the `main`
  function.
  - If you're in the middle of working, you can make one commit and push with
  whatever the current state of your work is, and then another small commit

  Notice that you can click on any commit and see the individual files at that
  point in time! This can help you get back to an earlier state if you're stuck.

- The file you create with `gcc` (probably called `utf8analyzer` or similar)
changes every time you compile, and could be entirely different when compiled on
different computers. It also doesn't have a meaningful “diff” between versions,
since it's a binary file. For these reasons, built files are usually _not_
included in a repository. The file `.gitignore` in the root of a repository can
list files that should be completely ignored by `git` – it won't include them in
the list of files to add or change.
  - Compile your program and show a screenshot of the status of the binary file
  that was created (for example, in the source control/Git tab of the codespace)
  - Change your `.gitignore` to include the path of this file
  - Observe that it no longer shows up as a file to add!

  It's really useful to keep repositories organized and tidy. `.gitignore` is one way to do that, separating the source code of a project from other “build artifacts” that are temporarily important but shouldn't be tracked and saved in the same way as code.


### Working on the PA

Armed with your thorough tests, spend some time working on the PA. You might
choose to just include some of the tests you've written in your own code at
first as you work on invidual milestones.

Feel free to work together, though keep in mind the academic integrity policies
and `CREDITS.md`. In this (and in all things learning-based) focus on what's best
for your _learning and understanding_, not just what's best for _finishing_ the
PA. The conceptual knowledge pays off later in the course, on exams, and in your
career, getting the code complete for a PA without understanding it has little
effect.

(Here we should be able to surface common issues to the TAs and see if there's something worth saying globally/etc)

### Signing Up for An Exam Slot

Next week (week 3) is the first exam. It will have questions in the same
platform you've seen in the PrairieLearn quizzes. You need to sign up for an
_exam slot_ during week 3, which you can do at: FILL

This document is the Triton Testing Center's guide: FILL

You should **not** use lecture or lab time to take the exam; next week will be a
normal week of lecture, lab, quiz, and so on with the added exam at some time
outside of class.

(You can do this outside of lab time, too, but we wanted to make a point to
remind you during lab!)


### Ideas for students who (say they) are done:

- Implement a Zalgo text generator (https://zalgo.org). You can tell them to do
their own research to figure out how that works.
- Implement `reverse` that takes an argument buffer to store the reversed
string. If they do that, then they should do `reverse_in_place` that uses as
little extra memory as possible and reverses in place.
- Research how they'd go about implementing `uppercase`/`lowercase` that
includes accented characters. Can they find a library or tool that would help
them? How do they think that works in software tools like autocorrect that
capitalize the first letter of a sentence?

- DON'T go over the design questions. Leave those to them. I don't want to give
accidentally “official”-seeming answers to those.
