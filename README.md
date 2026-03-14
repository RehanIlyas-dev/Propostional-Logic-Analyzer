<p align="center">
  <h1 align="center">🧮 Propositional Logic Analyzer</h1>
  <p align="center">
    <strong>A powerful C++ tool for truth tables, logical equivalence, entailment checking, and step-by-step simplification.</strong>
  </p>
  <p align="center">
    <a href="#-features"><img src="https://img.shields.io/badge/Features-6_Modes-blue?style=flat-square" alt="Features"></a>
    <a href="#-supported-operators"><img src="https://img.shields.io/badge/Operators-6_Types-green?style=flat-square" alt="Operators"></a>
    <a href="#-getting-started"><img src="https://img.shields.io/badge/Language-C%2B%2B-orange?style=flat-square" alt="Language"></a>
    <a href="#-logical-laws"><img src="https://img.shields.io/badge/Laws-15%2B_Rules-purple?style=flat-square" alt="Laws"></a>
  </p>
</p>

---


## 📖 About

**Propositional Logic Analyzer** is an interactive console application built in **C++** that bridges the gap between Discrete Mathematics theory and practical computation. It automates the tedious process of manually creating truth tables, checking logical equivalence, validating arguments, and simplifying complex expressions — all from a single menu-driven interface.

> **CS-101 Discrete Mathematics Project** — University of Engineering and Technology, Lahore

---

## ✨ Features

The analyzer offers **six integrated modes** accessible from a unified menu:

### 1️⃣ Single Expression Analysis
Enter any propositional logic expression and instantly receive:
- A complete **truth table** with 2ⁿ rows for `n` variables
- Automatic **status detection**: Tautology, Contradiction, or Contingency

### 2️⃣ Double Expression Comparison
Compare two expressions side-by-side:
- Generates a **combined truth table** with both results
- Performs an **equivalence check** (e.g., proving `P > Q ≡ ~P | Q`)
- Reports individual status for each expression

### 3️⃣ User's Manual
Built-in documentation with operator syntax, usage tips, and examples.

### 4️⃣ Statement Evaluation (Entailment Checker)
Determine if a **conclusion logically follows** from a set of premises:
- Supports up to **10 premises** with one conclusion
- Uses **semantic entailment** (checks all valuations)
- Detects **vacuous truth** (no valuation satisfies all premises)
- Identifies common **inference rules**: Conjunction Introduction/Elimination, Disjunction Introduction, Disjunctive Syllogism

### 5️⃣ Step-by-Step Simplification
Watch expressions get simplified in real-time using named logical laws:
- **Single mode**: Simplify one expression with step-by-step output
- **Comparison mode**: Simplify two expressions and verify equivalence via truth table

### 6️⃣ Exit
Gracefully close the program.

---

## ⌨️ Supported Operators

The analyzer maps standard discrete math operators to keyboard-friendly characters:

| Operator | Math Symbol | Input Syntax | Precedence |
|:---|:---:|:---:|:---:|
| **Negation (NOT)** | ¬P | `!` or `~` | Highest (5) |
| **Conjunction (AND)** | P ∧ Q | `&` | 4 |
| **Disjunction (OR)** | P ∨ Q | `\|` | 3 |
| **Exclusive OR (XOR)** | P ⊕ Q | `^` | 2 |
| **Implication** | P → Q | `>` | 1 |
| **Biconditional** | P ↔ Q | `=` | Lowest (0) |
| **Grouping** | (P ∧ Q) | `( )` | — |

> **Note:** Implication `P > Q` is internally evaluated as `¬P ∨ Q`. Variables are single letters `A–Z` (case-insensitive).

---

## 📐 Logical Laws

The step-by-step simplifier applies **15+ logical laws** automatically using an **expression tree** engine:

| Category | Laws Applied |
|:---|:---|
| **Operator Elimination** | Material Implication, Biconditional Elimination, XOR Definition |
| **Negation Rules** | Double Negation, De Morgan's Law (∧ and ∨ forms) |
| **Simplification** | Complement Law, Idempotent Law, Identity Law, Domination Law, Absorption Law |
| **Constants** | Negation of Constants (`!0 → 1`, `!1 → 0`) |

Each simplification step is annotated with the law name used:
```
  Start:    P>Q
  Step  1:  !P|Q                      [Material Implication]
```

---

## 🏗️ Architecture

The project is implemented in a **single-file C++ architecture** (~1365 lines) using fundamental data structures:

```
Logic Analyzer/
├── main.cpp              # Complete source code
├── analyzer              # Pre-compiled binary
├── main                  # Pre-compiled binary
├── Data/
│   ├── Input_Single.MD   # Sample single-expression input
│   └── Input_Double.MD   # Sample double-expression input
└── Tests/
    ├── Test01.MD          # Test: Basic AND/OR (Contingency)
    └── Test02.MD          # Test: Tautology check (A | ~A)
```

### Key Algorithms
| Component | Implementation |
|:---|:---|
| **Expression Parsing** | Shunting Yard algorithm (infix → postfix conversion) |
| **Expression Evaluation** | Stack-based postfix evaluator |
| **Simplification Engine** | Recursive expression tree with pattern-matching rule application |
| **Truth Table Generation** | Binary counting over 2ⁿ combinations |
| **Entailment Checking** | Exhaustive valuation with counterexample search |
| **Law Detection** | String-based pattern matching for common inference forms |

---


## 🚀 Getting Started

### Prerequisites
- A C++ compiler supporting **C++11** or later (e.g., `g++`, `clang++`)
- **Linux/macOS** terminal (uses `system("clear")` for screen clearing)

### Build & Run

```bash
# Clone the repository
git clone https://github.com/RehanIlyas-dev/Propostional-Logic-Analyzer.git
cd Propostional-Logic-Analyzer/Logic\ Analyzer

# Compile
g++ main.cpp -o logic_analyzer -lm

# Run
./logic_analyzer
```

### Quick Examples

**Single Expression — Check if tautology:**
```
Enter the logical expression: A | ~A
→ Status: Tautology
```

**Two Expressions — Prove equivalence:**
```
Enter first expression:  P > Q
Enter second expression: ~P | Q
→ The two statements are Equivalent.
```

**Statement Evaluation — Modus Ponens:**
```
Enter number of premises: 2
Enter premise 1: P > Q
Enter premise 2: P
Enter conclusion: Q
→ Conclusion follows from premises.
```

**Step-by-Step Simplification:**
```
Enter expression: !(A & B)
  Start:    !(A&B)
  Step  1:  !A|!B    [De Morgan's Law]
```

---

## 🧪 Test Cases

| Test | Type | Input | Expected Status |
|:---|:---|:---|:---|
| Test 01 | Single Expression | `(A & B) \| C` | Contingency |
| Test 02 | Single Expression | `A \| ~A` | Tautology |

Test files are located in `Logic Analyzer/Tests/` with detailed expected outputs.

---

## ⚙️ Technical Details

- **Input Validation**: Checks for balanced parentheses, invalid characters, and consecutive operators before processing
- **Variable Detection**: Automatically scans expressions and identifies unique propositional variables
- **Expression Tree**: Nodes store type (`V`ariable, `C`onstant, `O`perator), value, and left/right child indices in a static array of 5000 nodes
- **Max Simplification Steps**: Capped at 50 iterations to prevent infinite loops
- **Multiple Premise Support**: Up to 10 premises in statement evaluation mode

---

## 🔮 Future Enhancements

- [ ] **GUI Development** — Migrate from console to a Qt/GTK application
- [ ] **Karnaugh Maps** — Automated K-Map generation for expression simplification
- [ ] **File Export** — Save truth tables to `.csv` or `.txt` files
- [ ] **Step-by-Step Solver** — Display intermediate evaluation steps for truth table cells
- [ ] **Cross-Platform** — Replace `system("clear")` with portable terminal handling

---

## 👥 Authors

| Name | Roll Number | Role |
|:---|:---|:---|
| **Muhammad Rehan Ilyas** | 2025-CS-65 | Developer |
| **Muhammad Hassan Rauf** | 2025-CS-106 | Developer |

**Submitted To:** Sir Waqas Ali  
**Course:** CS-101 Discrete Mathematics  
**Institution:** University of Engineering and Technology, Lahore

---

## 📚 References

- *Discrete Mathematics and Its Applications*, 8th Edition — Kenneth H. Rosen
- C++ Standard Library Documentation
- Shunting Yard Algorithm — Edsger W. Dijkstra

---

## 📄 License

This project is open source and available for educational purposes.

---

<p align="center">
  <sub>Built with ❤️ for Discrete Mathematics</sub>
</p>
