# Crack the Password

The relevant files for this part of the lab are found within the `password-crack` directory in the `lab7-starter` repository you cloned earlier.

You are provided with an executable binary that performs a similar task to your password cracker from PA2. It randomly selects a word as the password (this word is unique to your student ID) and displays the hash of this word and then prompts you to guess the password. You are also given the `main.c` file that calls the function that generates the secret word and hashes it. However, you do not have the source code for the word generator itself.

Your goal is to crack the password given only the hash and the `main.c` file.

```
./ctf
Generating and hashing secret word...
the hash is 229478424054275
What is the password?: 
yash
Password not found, Try again 
hello
Password not found, Try again 
return
Password not found, Try again
.
.
.
```

**TASK:**
1. Using tools you have learned about in CSE 29, determine what your random secret word is and crack the password!

**In your notes:** Describe the tool(s)/process you used and provide a screenshot of you cracking the password!