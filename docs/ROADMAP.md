# 🍉 Watermelon Roadmap

**Project:** Watermelon – A lightweight scripting language built with C++  
**Goal:** Learn and implement compiler design principles by building an interpreter from scratch.

---

## 🏁 Sprint 1 – Core Foundation & Expression Engine
**Duration:** Oct 24 – Nov 7, 2025  
**Status:** ✅ Completed  

### 🎯 Goal
Establish the base of the interpreter — including the tokenizer, expression parser, memory management, and basic arithmetic operations.

### 🔧 Completed Tasks
- Implemented **Tokenizer** to split source lines into tokens.  
- Created **Token**, **Expression**, and **Memory** classes.  
- Built a **postfix converter (Shunting-Yard Algorithm)** for expression parsing.  
- Supported arithmetic operators: `+`, `-`, `*`, `/`.  
- Added variable declaration and assignment (`int a = 5;`).  
- Implemented evaluation of expressions using stack-based execution.  
- Added `ScriptLine` class to represent source lines and handle comments.  

### 📈 Outcome
✅ The interpreter can now tokenize, parse, and evaluate expressions like:  
```text
a = 1
b = 2
c = a * b + (a + b) * 3 - 4 / 2
```
and store results in memory.

---

## ⚙️ Sprint 2 – Expression Evaluation & Syntax Validation
**Duration:** Nov 7 – Nov 21, 2025  
**Status:** 🟡 In Progress  

### 🎯 Goal
Implement full **expression evaluation**, integrate **operator precedence** from the operator table, and introduce the first version of **syntax validation** and **error reporting**.

### 🔧 Planned Tasks
- Extend the **OperatorTable** with relational, logical, and assignment operators.  
- Implement proper **operator associativity** (`right` vs. `left`).  
- Refactor **Expression::to_postfix()** to read operator precedence from the table.  
- Add **SyntaxValidator** to pre-check parenthesis, quote balance, and identifier validity.  
- Improve **Tokenizer** to store line and column metadata for better error messages.  
- Add **Error reporting system** that includes file, line, and column data.  
- Minor refactor of **ScriptLine** to improve separation of concerns.  
- Begin planning for **Sprint 3: Control Flow & Conditional Statements**.  

### 📈 Expected Outcome
By the end of Sprint 2, Watermelon should:
- Correctly parse and evaluate multi-level arithmetic expressions.  
- Handle assignment operations (`=`, `+=`, etc.) as regular operators.  
- Report syntax errors gracefully with clear source information.  

---

## 🧩 Sprint 3 – Control Flow & Conditional Evaluation
**Duration:** Nov 21 – Dec 5, 2025  
**Status:** ⏳ Planned  

### 🎯 Goal
Introduce **conditional execution** and **basic control flow** (if/else, while) using parsed syntax trees or expression chaining.

### 🔧 Planned Tasks
- Implement boolean comparison operators (`<`, `>`, `<=`, `>=`, `==`, `!=`).  
- Add **if / else** blocks with simple statement grouping.  
- Introduce **while loops** with condition evaluation.  
- Extend tokenizer to support braces `{}` and indentation-based scopes.  
- Add internal **execution context** for scoped variables.  
- Update error system for missing conditions or invalid nesting.  

### 📈 Expected Outcome
By the end of Sprint 3:
- The interpreter can execute conditional logic (e.g. `if (a > b) { ... }`).  
- Watermelon will be capable of **branching and looping execution paths**.

---

## 🧠 Sprint 4 – Functions, Scopes & Call Stack
**Duration:** Dec 5 – Dec 19, 2025  
**Status:** ⏳ Planned  

### 🎯 Goal
Introduce **user-defined functions**, **scope isolation**, and a simple **call stack** to execute nested or recursive code blocks.

### 🔧 Planned Tasks
- Implement `function` definitions and `return` statements.  
- Add stack frames for variable scoping during calls.  
- Handle parameter passing and local variable shadowing.  
- Support built-in functions (e.g., `print()`, `len()`, `input()`).  
- Add proper cleanup of stack frames on function exit.  
- Implement type-checking for return types and arguments.  

### 📈 Expected Outcome
- Code like:
  ```cpp
  function add(a, b) {
      return a + b
  }
  c = add(2, 3)
  ```

will execute and return correct values.

---

🚀 Sprint 5 – Error Handling, Modules & Quality Improvements
------------------------------------------------------------

**Duration:** Dec 19 – Jan 2, 2026  
**Status:** ⏳ Planned

### 🎯 Goal

Enhance developer experience through **structured error handling**, **module imports**, and **debugging utilities**.

### 🔧 Planned Tasks

*   Implement `try / catch` exception-like behavior.
    
*   Add **import system** for loading external script files.
    
*   Add runtime debugging commands (`print_memory`, `trace`, etc.).
    
*   Improve performance of evaluation and operator dispatching.
    
*   Introduce basic optimization for expression re-use.
    
*   Improve documentation and update examples.
    

### 📈 Expected Outcome

*   Watermelon becomes a **usable scripting language prototype** with readable syntax, good error messages, and modular structure.
    

---

🌱 Long-Term Goals (Post-Sprint)
--------------------------------

*   Add **arrays**, **maps**, and **string operations**.
    
*   Implement **file I/O**, **standard library**, and **REPL mode**.
    
*   Build **C++ API embedding support** to run Watermelon scripts from other apps.
    
*   Write **unit tests** for compiler and interpreter layers.
    
*   Optional: transpile Watermelon to C or bytecode for a VM backend.
    

---

### 🧭 Progress Summary

| Sprint | Focus | Status | Progress |
| --- | --- | --- | --- |
| 1 | Core & Arithmetic | ✅ Completed | 100% |
| 2 | Expressions & Validation | 🟡 In Progress | 70% |
| 3 | Control Flow | ⏳ Planned | 0% |
| 4 | Functions & Stack | ⏳ Planned | 0% |
| 5 | Error Handling & Modules | ⏳ Planned | 0% |

---

**Watermelon** is an experimental scripting language for learning compiler and interpreter design —  
built entirely in modern **C++**, with focus on clarity, architecture, and educational value.
