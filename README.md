# 🍉 Watermelon

**Watermelon** is a lightweight scripting language written in **C++**,  
designed as a personal compiler project that grows feature by feature —  
just like the Diyarbakır watermelons it’s named after 🍉  

---

## 🚀 Project Overview

Watermelon is a mini-compiler that supports:
- Expression parsing and evaluation (`+`, `-`, `*`, `/`, `=`, etc.)
- Integer, float, string and boolean variable definitions
- Memory model with variable assignment and lookup
- Postfix expression evaluation (Shunting Yard algorithm)
- Syntax validation and error handling (in progress)

Its goal is to evolve into a **simple scripting language**, with readable syntax,  
custom operators, and runtime memory management — all built from scratch in C++.

---

## 🧱 Architecture

```plaintext
Compiler
 ├── Tokenizer        → Converts text lines into tokens
 ├── SyntaxValidator  → Checks parentheses, quotes, identifiers, etc.
 ├── Expression       → Converts infix → postfix, evaluates results
 ├── OperatorTable    → Manages precedence and operation logic
 ├── Memory           → Stores and retrieves variable values
 └── ScriptLine       → Represents a single line of code
 ```
 
Each module is independent and testable,
designed with clean separation of parsing, evaluation, and runtime logic.

## 📘 Example Script
```plaintext
// Comments are supported
a = 1
b = 2
c = a + b * (a + 3)
s = "hello" + " world"
is_valid = true && (a < 10)
```

#### Output (Debug mode):
```plaintext
[PARSE] Infix  : a = 1
[PARSE] Postfix: a 1 =
[MEMORY] a = 1

[PARSE] Infix  : b = 2
[PARSE] Postfix: b 2 =
[MEMORY] b = 2

[PARSE] Infix  : c = a + b * ( a + 3 )
[PARSE] Postfix: c a b a 3 + * + =
[MEMORY] c = 8

[PARSE] Infix  : s = "hello" + " world"
[PARSE] Postfix: s "hello" " world" + =
[MEMORY] s = "hello world"

[PARSE] Infix  : is_valid = true && ( a < 10 )
[PARSE] Postfix: is_valid true a 10 < && =
[MEMORY] is_valid = true
```

## 📅 Development Plan

Watermelon is developed using a Sprint-based structure to simulate
real compiler design phases and organized progress tracking.

| Sprint       | Status         | Goal                                                       |
| :----------- | :------------- | :--------------------------------------------------------- |
| **Sprint 0** | ✅ Done         | Core system (Tokenizer, Expression, OperatorTable, Memory) |
| **Sprint 1** | 🚧 In Progress | SyntaxValidator + Error reporting (line, column info)      |
| **Sprint 2** | ⏳ Planned      | Functions, Scopes, and Type System                         |
| **Sprint 3** | ⏳ Planned      | REPL mode + Debug shell                                    |
| **Sprint 4** | ⏳ Planned      | Intermediate Representation + Optimizations                |


## 🧩 Technical Highlights

C++17 Standard – modern and lightweight

Custom Stack implementation

Operator Precedence Parsing (Shunting Yard)

Dynamic Value system supporting multiple data types

Runtime memory management

## 💡 Future Ideas

Built-in functions (print, input)

Type inference & casting

Import system for scripts

REPL (interactive console)

Bytecode backend

## 🧠 Philosophy

“Grow it piece by piece, test it as you go.”

Watermelon started as an experiment — not to reinvent the compiler,
but to understand it deeply by building one from scratch.

## 🧑‍💻 Author

Developed by: Umutcan Ekinci

Inspired by: Diyarbakır’s legendary watermelons 🍉
Language: C++

## 🪪 License

MIT License © 2025 Umutcan Ekinci
