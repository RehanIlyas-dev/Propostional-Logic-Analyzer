# Propositional Logic Analyzer 🧮

> **CS-101 Discrete Mathematics Project**
> **University of Engineering and Technology, Lahore**

An automated C++ tool designed to generate truth tables, evaluate complex logical expressions, and verify logical equivalence between statements.

---

## 📖 About The Project

This program bridges the gap between Discrete Mathematics theory and practical computer science application. It automates the tedious process of manually creating truth tables, allowing users to instantly visualize how different logical inputs affect the final result of an expression.

### Key Capabilities
* **Truth Table Generation:** Automatically calculates 2^n rows for up to `N` variables.
* **Logic Evaluation:** Uses a custom evaluation engine (Shunting Yard Algorithm) to solve complex boolean algebra.
* **Equivalence Checker:** Compares two separate expressions side-by-side to prove if they are logically identical.
* **Status Detection:** Identifies if an expression is a **Tautology** (Always True), **Contradiction** (Always False), or **Contingency** (Mixed).

---

## ⚙️ Features

* **Dual Modes:** Support for **Single Expression** analysis and **Double Expression** comparison.
* **Smart Variable Detection:** Automatically scans input strings and identifies unique variables (e.g., A, B, C).
* **GUI-like Console:** Features a structured User Interface with ASCII art headers, borders, and centered text using `windows.h`.
* **Robust Validation:** Checks for balanced parentheses and invalid characters before processing.

---

## ⌨️ Supported Syntax & Operators

The analyzer supports standard discrete math operators mapped to keyboard characters:

| Operator Name | Math Symbol | Input Syntax |
| :--- | :---: | :---: |
| **Negation (NOT)** | ¬p | `!` or `~` |
| **Conjunction (AND)** | p ∧ q | `&` |
| **Disjunction (OR)** | p ∨ q | `|` |
| **Exclusive OR (XOR)** | p ⊕ q | `^` |
| **Implication** | p → q | `>` |
| **Biconditional** | p ↔ q | `=` |
| **Grouping** | (p ∧ q) | `( )` |

> **Note:** The program treats Implication (P → Q) as logically equivalent to ¬P ∨ Q.

---

## 🚀 How to Run

1.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/RehanIlyas-dev/Logic-Analyzer.git](https://github.com/RehanIlyas-dev/Logic-Analyzer.git)
    ```
2.  **Compile the Code:**
    Ensure you have a C++ compiler (like g++).
    ```bash
    g++ main.cpp -o logic_analyzer
    ```
3.  **Run the Executable:**
    ```bash
    ./logic_analyzer
    ```
4.  **Usage:**
    * Select **Option 1** for Single Expression Analysis.
    * Select **Option 2** for Equivalence Checking.
    * Select **Option 3** for the User Manual.

---

## 🔮 Future Enhancements
We plan to improve this project with the following features:
* [ ] **GUI Development:** Moving from Console to a Windows Form/Qt application.
* [ ] **Karnaugh Maps:** Automated K-Map generation for simplification.
* [ ] **File Export:** Saving generated tables to `.csv` or `.txt` files.
* [ ] **Step-by-Step Solver:** Displaying intermediate evaluation steps.

---

## 👥 Authors

* **Muhammad Rehan Ilyas** (2025-CS-65) - *Developer*
* **Muhammad Hassan Rauf** (2025-CS-106) - *Developer*

**Submitted To:** Sir Waqas Ali

---

## 📚 References
* *Discrete Mathematics and Its Applications*, 8th Edition - K. H. Rosen.
* Microsoft Documentation (Windows Console Functions).
* C++ Standard Library Documentation.
