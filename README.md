# 🚀 Minishell - 1337 School Project

## 🔹 Introduction
Minishell is a simplified Unix shell that mimics the behavior of Bash. It implements core functionalities such as command execution, pipelines, redirections, and environment variable handling. This project leverages system programming techniques and key system calls like `execve()`, `fork()`, `pipe()`, `dup2()`, and `readline()`.

## 🏗️ Key Components

### 🔸 Lexer (Tokenizer)
Breaks user input into meaningful tokens.

Identifies commands, arguments, operators (`|`, `>`, `<`), and environment variables (`$HOME`).

**Example:**    
ls -la | grep minishell > output.txt



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
        
PIPE /
COMMAND REDIRECT (ls -la) (>) (output.txt)

### ⚙️ System Calls

- **Process Management:** `fork()`, `execve()`, `wait()`, `waitpid()`, `exit()`
- **File & Directory Operations:** `open()`, `read()`, `write()`, `close()`, `opendir()`, `readdir()`, `stat()`, `lstat()`, `unlink()`, `access()`, `getcwd()`, `chdir()`
- **Redirection & Pipes:** `dup()`, `dup2()`, `pipe()`
- **Signal Handling:** `signal()`, `sigaction()`, `kill()`
- **Memory Management:** `malloc()`, `free()`
- **Error Handling:** `strerror()`, `perror()`
- **Environment Variables:** `getenv()`

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

## 📌 Built-in Commands

- `cd` - Change directory
- `echo` - Print messages
- `export` - Set environment variables
- `unset` - Remove environment variables
- `env` - Print environment variables
- `exit` - Terminate the shell

## 📌 Signal Handling
Manages signals like `SIGINT` (Ctrl+C), `SIGQUIT` (Ctrl+\), and `SIGTSTP` (Ctrl+Z).

Uses system calls: `signal()`, `sigaction()`, `kill()`

## 🏗️ Project Structure

minishell/                 
├── src/ # Source files        
│ ├── lexer/ # Tokenization logic            
│ ├── parser/ # Parsing logic          
│ ├── ast/ # Abstract Syntax Tree            
│ ├── executor/ # Command execution          
│ ├── builtins/ # Built-in commands           
│ ├── signals/ # Signal handling            
│ ├── readline/ # User input handling          
│ ├── utils/ # Utility functions          
├── include/ # Header files              
│ └── minishell.h # Main header file          
├── Makefile # Build script             
├── README.md # Documentation              
├── tests/ # Test cases          



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


## 🚀 Features

- ✅ Command Execution
- ✅ Pipes & Redirections
- ✅ Environment Variables
- ✅ Built-in Commands
- ✅ Error Handling
- ✅ Signal Handling
- ✅ Memory Management

## 📌 Next Steps

- ✅ Add support for `&&`, `||`
- ✅ Implement command history (`readline()`)
- ✅ Improve error messages
- ✅ Implement job control (`fg`, `bg`)

## 🎯 Reflection
This project provides a deep understanding of process creation, parsing, and system calls. Implementing pipes, redirections, and a custom shell is both challenging and rewarding. It offers hands-on experience with key concepts in system programming and shell development.

## 🤝 Contributing
Fork the repository and submit a pull request. Contributions to error handling, new features, and performance improvements are always welcome! 🚀

   
