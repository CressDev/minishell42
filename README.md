_This project has been made as part of the 42 curriculum by Amonteag, Kmarrero_

# **Description**

This project consists of the implementation of a basic Linux shell, developed in the C programming language as part of the 42 Common Core. Its main objective is to gain a deep understanding of how a shell works and how the operating system interprets and executes commands entered by the user.
A shell acts as an interface between the user and the system, allowing programs to be executed through human-readable commands. Internally, these commands must be analyzed, interpreted, and translated into instructions that the system can execute.

This project recreates that process from scratch, including:
-	A lexer to analyze user input.
-	Syntax error handling for invalid commands.
-	The creation of data structures to parse command arguments.
-	The interpretation of those arguments as executable commands.
-	The execution of programs via their binaries using the execve system call.
Through this implementation, the project provides a solid understanding of process management, memory handling, system calls, and the internal workings of a Unix-like shell.

# **Instructions**

## **Requirements**
To compile this project, you need a C compiler installed on your system. On Debian-based distributions, you can install gcc with the following commands:

`sudo apt update`
`sudo apt install gcc`

**Installation**
Clone the repository using SSH into a directory of your choice (commonly inside your home directory):

`git clone git@github.com:YourUserName/minishell42.git`

## **Compilation**
Navigate to the project directory using the terminal:

`cd ~/path/to/minishell42`

Then compile the project by running:

`Make`

This command will generate the minishell executable.

## **Usage**

Once compiled, you can launch the shell with:

`./minishell`

The program will start and behave as a basic Unix shell, allowing you to enter and execute commands.

# **Resources**
To make the development of this project possible, we use the following information:

Compiler Design | Neso Academy
Shell Command Language
Scanning · Crafting Interpreters
8. Pipes — GNU/Linux para Bioinformática
https://www.youtube.com/watch?v=KM5sRWAYqaw&pp=ygUWbGludXggZmlsZSBkZXNjcmlwdG9ycw%3D%3D

Additionally, AI tools such as GitHub Copilot and ChatGPT were used **strictly as learning and research aids**.

They were mainly consulted during the early stages of the project to better understand theoretical concepts related to compilers and shells, such as:
- What a compiler is and how it works
- The purpose and structure of a **Finite State Machine (FSM)**
- How Bash handles quotes and tokenization
- Common syntax errors made by users

These tools were also used to assist in debugging by helping identify potential causes of errors.  
All architectural decisions, logic design, and code implementation were done manually by ourselfes.
