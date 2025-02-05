# C to Assembly Compiler Repository

## Repository Structure
```
📦 C-to-Assembly-Compiler
├── 📁 src
│   └── 📁 Analyses         
│   │    ├── 📄 AnalyseLexicale.cpp      
│   │    ├── 📄 AnalyseSemantique.cpp    
│   │    └──  📄 AnalyseSyntaxique.cpp    
│   └── 📁 Objets     
│   │    ├── 📄 Noeud.cpp      
│   │    ├── 📄 Operateur.cpp      
│   │    ├── 📄 Sybole.cpp      
│   │    └── 📄 Token.cpp          
│   └── 📁 Tests     
│        └── 📄 prog.c   
├── 📄 compilation.cpp       
├── 📄 GenCode.cpp    
├── 📄 Types.cpp    
└── 📄 README.md              
```

## Description
This repository contains a **compiler** that translates a C program into an **assembly script**. It performs lexical analysis, syntax analysis, semantic analysis, and code generation to produce assembly code from a given C program.

## Features
- **Lexical Analysis**: Tokenizes the input C source code.
- **Syntax Analysis**: Checks for syntactical correctness and builds an Abstract Syntax Tree (AST).
- **Semantic Analysis**: Ensures proper type checking and variable scope handling.
- **Code Generation**: Converts the AST into assembly code for execution.

## Installation & Compilation
### Prerequisites
- A C++ compiler (e.g., `g++`)
- Basic knowledge of C and Assembly language

### Compilation
To compile the project, run the following command:
```bash
    g++ compilation.cpp -o compilation
```

### Running the Compiler
To execute the compiler, make sure to set the correct input file path inside `compilation.cpp`:
```cpp
std::string chemin = "path/to/your/c_program.c";
```
Then, run the compiled binary:
```bash
./compilation
```

### Input
The compiler reads a **C program** from the specified file and processes it.

### Output
The generated **assembly code** is printed to the standard output (terminal).

## Example
A sample C program:
```c
int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    return c;
}
```
Would be converted into:
```assembly
.start
prep main
call 0
halt
.push 5
.push 10
add
ret
```
