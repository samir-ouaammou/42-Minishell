# 🚀 Minishell - 1337 School Project

## 🔹 Introduction
Minishell is a simplified Unix shell that mimics the behavior of Bash. It implements core functionalities such as command execution, pipelines, redirections, and environment variable handling. This project leverages system programming techniques and key system calls like `execve()`, `fork()`, `pipe()`, `dup2()`, and `readline()`, `etc...`.

---

## 🏗️ Key Components

### 🔸 Lexer (Tokenizer)
Breaks user input into meaningful tokens.

Identifies commands, arguments, operators (`()`, `||`, `&&`, `|`, `>`, `<`, `>>`, `<<`), and environment variables (`$HOME`).

**Example:**    
ls | wc -l || cat file.txt && echo "Hello world!"

**This is tokenized into:**            
[ls] [|] [wc -l] [||] [cat file.txt] [&&] [echo "Hello world!"]

**AST Tree Representation**        

For the command:                 
[ls] [|] [wc -l] [||] [cat file.txt] [&&] [echo "Hello world!"]

                    &&
                 /      \
               ||       echo "Hello world!"
             /    \
           |     cat file.txt
        ls   wc -l  
      

---
### ⚙️ System Calls

- **Process Management:** `fork()`, `execve()`, `wait()`, `waitpid()`, `exit()`
- **File & Directory Operations:** `open()`, `read()`, `write()`, `close()`, `opendir()`, `readdir()`, `stat()`, `lstat()`, `unlink()`, `access()`, `getcwd()`, `chdir()`
- **Redirection & Pipes:** `dup()`, `dup2()`, `pipe()`
- **Signal Handling:** `signal()`, `sigaction()`, `kill()`
- **Memory Management:** `malloc()`, `free()`
- **Error Handling:** `strerror()`, `perror()`
- **Environment Variables:** `getenv()`
---
## ⚡ Operators & Features

### 🔹 Redirections

- **`<`** - Redirect input:  
  Example: `cat < file.txt`
  
- **`>`** - Redirect output:  
  Example: `ls > output.txt`
  
- **`>>`** - Append output:  
  Example: `ls >> output.txt`
  
- **`<<`** - Here document:  
  Example: `cat << EOF`

### 🔹 Pipes
- **`|`** - Connects the output of one command to the input of another:  
  Example: `ls | grep minishell`

### 🔹 Logical Operators

- **`&&`** - Execute next command if the previous succeeds:  
  Example: `ls && echo "Success"`
  
- **`||`** - Execute next command if the previous fails:  
  Example: `ls || echo "Failed"`

### 🔹 Wildcards

- **`*`** - Matches any number of characters:  
  Example: `ls *.txt`

### 🔹 Environment Variables

- **`$`** - Expands environment variables:  
  Example: `echo $HOME`
  
- **`$?`** - Expands to the last command’s exit status:  
  Example: `echo $?`
  
- **`$USER`** - Expands to the current user:  
  Example: `echo $USER`
---
## 📌 Built-in Commands

- `cd` - Change directory
- `echo` - Print messages
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Print environment variables
- `exit` - Terminate the shell
---
## 📌 Signal Handling
Manages signals like `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+D), and `SIGTSTP` (Ctrl+Z).

Uses system calls: `signal()`, `sigaction()`, `kill()`

---

## 🏗️ Project Structure
```
minishell/                 
├── src/                    # Source files        
│   ├── lexer/              # Tokenization logic            
│   ├── parser/             # Parsing logic          
│   ├── tokens/             # Token parsing logic          
│   ├── tree/               # Binary Tree implementation          
│   ├── AST/                # Abstract Syntax Tree logic            
│   ├── executor/           # Command execution logic          
│   ├── builtins/           # Built-in commands           
│   ├── signals/            # Signal handling logic            
│   ├── readline/           # User input handling logic          
│   ├── utils/              # Utility functions          
├── include/                # Header files              
│   └── minishell.h         # Main header file          
├── Makefile                # Build script             
├── README.md               # Documentation                     

```
---
## 🛠️ Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/samir-ouaammou/1337-Minishell  
   ```

2. Navigate to the project directory:
   ```bash
   cd 1337-Minishell/Projects
   ```

3. Compile the source files using `make`:
   ```bash
   make 
   ```

4. Clean up compiled files:
   ```bash
   make clean
   ```

5. To remove all object files and the executable:
   ```bash
   make fclean
   ```

6. To recompile the project from scratch:
   ```bash
   make re
   ```

---
## 🚀 Features to Implement                               
✅ Command Execution (Using fork(), execve(), and redirections)                          
✅ Pipes & Redirections (Handling |, <, >, >>, <<)                      
✅ Environment Variables (Expanding $HOME, $PATH, $?)                     
✅ Built-in Commands (cd, echo, pwd, export, unset, env, exit)                        
✅ Error Handling (Invalid commands, syntax errors)                     
✅ Signal Handling (Ctrl+C, Ctrl+D)                     
✅ Memory Management (Avoiding memory leaks)                   
                           
---
          
## 📌 Operators to Handle                          
✅ () - Subshell execution                  
✅ && - AND Operator               
✅ || - OR Operator                   
✅ | - Pipe Operator                           
✅ < - Input Redirection             
✅ > - Output Redirection             
✅ << - Here Document                  
✅ >> - Append Output Redirection                
✅ $ - Variable Expansion               
✅ $? - Last Exit Status             
✅ $HOME - Home Directory Expansion                                    

---

## 📌 Next Steps
✅ Add Logical Operators (&&, ||)                       
✅ Implement Command History (readline())                           
✅ Improve Error Messages                       
✅ Implement Job Control (fg, bg)           

---

## 🏆 **Key Achievements**
- Developed a custom shell with support for basic commands, pipelines, and redirections.
- Mastered the use of a lexer to tokenize input and a parser to interpret and structure commands.
- Created and managed tokens to represent individual components of commands for easier processing.
- Built an efficient abstract syntax tree (AST) to represent and execute parsed commands and operators. 🌳
- Used fork() and wait() to manage process execution and synchronization.
- Implemented pipe() for connecting processes and enabling inter-process communication.
- Successfully utilized exec() to execute commands and launch programs. 🚀

---

## 🚀 **Next Steps**
- Starting the Philosophers, cub3D, and Net_Practice projects to deepen my understanding of concurrency, graphics, and networking.
- Continuing to refine my knowledge of system-level programming and dynamic memory management. 💡
- Expanding my skills in C++ to explore object-oriented programming and advanced concepts. 🚀
- Applying the experience gained to tackle increasingly complex and challenging problems. 🌍

---

## 🎯 Reflection
The Minishell project was a fascinating journey into the heart of shell programming. It offered me a hands-on experience with process creation, command parsing, and system calls that are fundamental to building a shell. 🖥️ The challenges of implementing pipes, redirections, and error handling pushed me to think critically about how to manage resources and memory efficiently. 💡
I worked on this project as part of a group of two students, which provided valuable experience in collaborative problem-solving and team communication. By diving deep into system-level programming, I’ve gained invaluable insights into how shells operate under the hood. I’m eager to apply this knowledge to more advanced projects. This experience has fueled my growth as a developer, and I’m excited to continue exploring new topics and pushing my limits. 🚀

---

Thank you for checking out my **minishell** project! 🚀 Stay tuned for more updates as I continue to enhance my skills and tackle new challenges.

