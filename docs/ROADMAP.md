# 🍉 Watermelon Roadmap

This roadmap documents the planned and completed sprints for the **Watermelon** scripting language project — a lightweight, experimental interpreter written in C++ for learning compiler and interpreter design.

---

## 🧩 Sprint 1 – Core Architecture Setup
**Duration:** Oct 24 – Nov 7, 2025  
**Status:** ✅ Completed  

### 🎯 Goal
Build the foundational architecture of the Watermelon scripting language, including file reading, line handling, and initial parsing structure.

### 🔧 Key Tasks
- Implemented **Compiler** class for managing file compilation.
- Added **ScriptLine** class for handling comments, empty lines, and line-by-line processing.
- Introduced **Memory** class to store and retrieve variable values.
- Developed **Expression** and **Token** classes to represent and process mathematical and logical expressions.
- Implemented **basic infix → postfix conversion** and simple evaluation logic.
- Added **operator table** for handling arithmetic (`+ - * /`) and logical (`&& || ==`) operators.
- Basic runtime memory output for variable assignments.

### 🧠 Learnings
- Expression parsing requires a flexible operator-precedence-aware approach.
- Static `Memory` or global references cause unwanted coupling; dependency injection is safer.
- Established the need for a proper `Tokenizer` and `SyntaxValidator` abstraction.

### 📊 Example Output
```text
[PARSE] Infix  : c = a * b + ( a + b ) * 3 - 4 / 2
[PARSE] Postfix: c a b * a b + 3 * + 4 2 / -
[MEMORY] c = 1
```

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

### 🧠 Notes for the Future
- Future sprints will focus on control structures (`if`, `while`), function calls, and runtime type system improvements.  
- Consider introducing an intermediate representation (IR) for optimization.  
