# Week 1 – Command Line and Running C Programs

## Lab Logistics

In this class, you are assigned to lab sections, in which you will be in the CSE basement lab rooms to work hands-on on activities related to the tools and techniques that you’ll be using on programming assignments.

Labs are graded by participation, based on your attendance and engagement with the lab activity. Throughout the lab, you will fill in a shared Google Doc with notes and results from what you try and learn. This will be shared with the group of students around you so you have a collective record of your activities (and so we can comment on your progress!)

Your TA lab lead will share the link to the Google Doc with you at the beginning of the lab.

## Github

Much of our work this quarter will happen through [Github](http://github.com), which is a platform for sharing code and collaborating on projects. You should make sure you have a Github account – you're free to use an existing one if you already have one. We will make use of the resources available in the [Github Student Developer Pack](https://education.github.com/discount_requests/application?type=student). This may require signing up with a `@ucsd.edu` email address, or adding it to your account, in order to verify your student status.

### Making an Account

For this lab, you **do** need to make a Github account right away. You **do not** need the Student developer pack yet, but you should submit the application in lab if possible so that you'll have the needed resources going forward.

**Write down in your Google Doc**:

For each student, their `@ucsd` email and their Github username they will use for this class (this is helpful for the TAs to know who is who!), and a link to their Github profile, which looks something like [https://github.com/jpolitz/](https://github.com/jpolitz/).

### Making a Repository

From your Github profile page, click the `+` in the upper right to make a new **repository** (you can call it something like `lab1`). For lab work, your repositories can be _public_ (for assignments we will show you how to make them be _private_).

**Definition**: A **repository** is a place to store code and other files. It has some similarities to a shared folder in Google Drive: it stores a collection of files and folders, and there are ways to share it with others. The main special thing about repositories is that they store a detailed history of changes to files, which turns out to be really important for programming projects.

There are many ways to interact with a repository; we'll see a few today and many more throughout the quarter. After you create the repository, you'll see a page like this:

... FILL SCREENSHOT ...

For a first step, you'll make a README file directly on `github.com`. Click the `Add a README` button, and you'll be taken to an editor where you can write some text. You can write anything you like for this first test; when you're done, click the `Commit new file` button at the bottom.

**Write down in your Google Doc**:

For each student, a screenshot of their repository after adding the README file. If anyone ran into errors or issues, describe them!

### Github Codespaces

Github has a feature called [Codespaces](https://docs.github.com/en/codespaces/overview) that provide an online environment for the full development process – writing code, running programs, and managing a repository. We'll use this feature throughout the course to have a standardized programming environment for everyone; Codespaces is also similar to many production environments in tech companies and research labs.

For this lab, we'll create a Codespace to do our work. Click the `Code` button on your repository page, and then click the `New Codespace` button:

... FILL SCREENSHOT ...

This will open a new Codespace (sometimes it takes a minute to start up), which will look like this:

... FILL SCREENSHOT ...

(The cute invented name will be randomly generated for each new Codespace you make.)



## ieng6 login



Log into ieng6 from Github codespace with ssh from that terminal

**Write down in notes**: screenshots

## Run simple commands

cat, curl, ls, cd, mkdir, pwd and maybe a few others

**Write down in notes**: some descriptions

## Build a C program (in both places)

Give them Hello.c from class, build + run both in Codespace and on ieng6.

Do something to make it have different behavior on the two systems! (environment
var, file, hostname, etc)

`ls ..` to show username dirs on ieng6, different layout entirely in the codespace

**Write down in notes**: compare/contrast

## Edit a C Program

fgets and/or CLI option

**Write down in notes**: some code

## What is the unbounded time exploration?

telnet towel.blinkenlights.nl 23

telnet  freechess.org

Telnet servers

Telnet games

nc fibs.com 4321 (backgammon)

nc mapscii.me 23 (world map)
