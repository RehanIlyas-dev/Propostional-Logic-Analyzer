#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <cstring>
#include <string>
using namespace std;

// Expression tree node
struct ExprNode {
  char type;  
  char value; 
  int left;  
  int right;
};

static ExprNode gNodes[5000];
static int gNodeCount = 0;

// ----------------------------
// FUNCTION PROTOTYPES --------
// ----------------------------

void printHeader();
void printMenu();
int getUserChoice();
void inputSingleExpression(char expr[]);
void inputTwoExpressions(char expr1[], char expr2[]);
int detectvariables(char expr[], char vars[]);
void printVariables(int varCount, char vars[]);
int combineVariables(char expr1[], char expr2[], char vars[]);
void generateTruthTable(int varCount, int table[][500]);
void printTruthTableSingle(int varCount, char vars[], char expr[],
                           int table[][500]);
void printTruthTableDouble(int varCount, char vars[], char expr1[],
                           char expr2[], int table[][500]);
int evaluateExpression(char expr[], char vars[], int varCount, int tablerow[]);
bool isValidExpression(char expr[]);
void printInstructionsmenu();
void clearBuffer();
void printsingleexp();
void printdoubleexp();
void printinstructions();
void printStatementMode();
void statementEvaluationMode();
void normalizeExpression(const char src[], char dst[]);
int detectVariablesMultiple(char exprs[][100], int exprCount, char vars[]);
bool checkEntailment(char premises[][100], int premiseCount, char conclusion[],
                     char vars[], int varCount, bool &vacuous);
bool detectSimpleLaw(char premises[][100], int premiseCount, char conclusion[]);

int newNode(char type, char value, int left, int right);
void resetNodes();
int buildTreeFromPostfix(char postfix[]);
int parseToTree(char expr[]);
void treeToStr(int root, char result[], int &pos, int parentPrec, bool isRight);
void getExpressionString(int root, char result[]);
int copyTree(int root);
bool treesEqual(int a, int b);
bool isNegationOf(int a, int b);
bool applyRule(int &root, char lawName[]);
void printStepByStep(char expr[], char finalResult[]);
void stepByStepEquivalenceMode();
void printStepByStepHeader();

int main() {
  int option = 0;

  while (option != 4) {
    printHeader();
    printMenu();
    option = getUserChoice();

    if (option == 1) {
      printsingleexp();
      char expr[100];
      char vars[1000];
      static int table[1000][500];
      cout << "\nSingle Expression Selected\n" << endl;
      inputSingleExpression(expr);

      if (!isValidExpression(expr)) {
        cout << "\n";
        cout << "Press any key to Try Again...";
        cin.get();
        continue;
      }

      int varCount = detectvariables(expr, vars);
      printVariables(varCount, vars);
      generateTruthTable(varCount, table);
      printTruthTableSingle(varCount, vars, expr, table);

      cout << "Process Complete. Press any key to return back to Menu...";
      cin.get();
    } else if (option == 2) {
      printdoubleexp();
      char expr1[100], expr2[100], vars[1000];
      static int table[1000][500];

      cout << "\nTwo Expressions Selected\n" << endl;
      inputTwoExpressions(expr1, expr2);

      if (!isValidExpression(expr1) || !isValidExpression(expr2)) {
        cout << "\n";
        cout << "Press Enter to Try Again...";
        cin.get();
        continue;
      }
      int varCount = combineVariables(expr1, expr2, vars);
      printVariables(varCount, vars);
      generateTruthTable(varCount, table);
      printTruthTableDouble(varCount, vars, expr1, expr2, table);

      cout << "\nProcess Complete.\nPress any key to return back to Menu...";
      cin.get();
    } else if (option == 4) {
      printStatementMode();
      statementEvaluationMode();
    } else if (option == 5) {
      printStepByStepHeader();
      stepByStepEquivalenceMode();
    } else if (option == 3) {
      system("clear");
      printinstructions();
      printInstructionsmenu();
      cout << "\nPress any key to return back to Menu...";
      cin.get();
    } else if (option == 4) {
      cout << "Exiting Program...\n\n";
      cout << "Thanks For Using Our Program!\n";
      return 0;
    }
  }
  return 0;
}

// -----------------------------
// FUNCTION DEFINITIONS --------
// -----------------------------

void clearBuffer() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader() {
  system("clear");
  cout << "=====================================================\n";
  cout << "       LOGICAL ANALYZER - TRUTH TABLE GENERATOR     \n";
  cout << "=====================================================\n\n";
}

void printsingleexp() {
  system("clear");
  cout << "=====================================================\n";
  cout << "               SINGLE EXPRESSION MODE               \n";
  cout << "=====================================================\n\n";
}

void printdoubleexp() {
  system("clear");
  cout << "=====================================================\n";
  cout << "               DOUBLE EXPRESSION MODE               \n";
  cout << "=====================================================\n\n";
}

void printinstructions() {
  cout << "=====================================================\n";
  cout << "                    INSTRUCTIONS                     \n";
  cout << "=====================================================\n\n";
}
void printMenu() {
  cout << "  1. Single Expression\n";
  cout << "  2. Two Expressions\n";
  cout << "  3. User's Manual\n";
  cout << "  4. Statement Evaluation\n";
  cout << "  5. Step-by-Step Simplification\n";
  cout << "  6. Exit\n";
}

int getUserChoice() {
  int choice;
  cout << "\nEnter your choice: ";

  while (!(cin >> choice)) {
    cout << "Invalid input. Please enter 1, 2, 3, 4, or 5: ";
    clearBuffer();
  }
  clearBuffer();

  return choice;
}

void inputSingleExpression(char expr[]) {
  cout << "Enter the logical expression: ";
  cin.getline(expr, 100);
}

void inputTwoExpressions(char expr1[], char expr2[]) {
  cout << "Enter first expression:  ";
  cin.getline(expr1, 100);
  cout << "Enter second expression: ";
  cin.getline(expr2, 100);
}

int detectvariables(char expr[], char vars[]) {
  int count = 0;
  for (int i = 0; expr[i] != '\0'; i++) {
    if (expr[i] >= 'a' && expr[i] <= 'z')
      expr[i] = expr[i] - 32;

    if (expr[i] >= 'A' && expr[i] <= 'Z') {
      bool found = false;
      for (int j = 0; j < count; j++) {
        if (vars[j] == expr[i]) {
          found = true;
          break;
        }
      }
      if (!found) {
        vars[count] = expr[i];
        count++;
      }
    }
  }
  return count;
}

void printVariables(int varCount, char vars[]) {
  cout << "\nVariables detected: ";
  for (int i = 0; i < varCount; i++)
    cout << vars[i] << " ";
  cout << "\n";
}

void generateTruthTable(int varCount, int table[][500]) {
  int rows = pow(2, varCount);

  for (int i = 0; i < rows; i++) {
    int value = i;
    for (int j = varCount - 1; j >= 0; j--) {
      table[i][j] = value % 2;
      value = value / 2;
    }
  }
}

int combineVariables(char expr1[], char expr2[], char vars[]) {
  int count = 0;
  char temp[10];

  int c1 = detectvariables(expr1, temp);
  for (int i = 0; i < c1; i++) {
    vars[count] = temp[i];
    count++;
  }

  int c2 = detectvariables(expr2, temp);
  for (int i = 0; i < c2; i++) {
    bool found = false;
    for (int j = 0; j < count; j++) {
      if (vars[j] == temp[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      vars[count] = temp[i];
      count++;
    }
  }

  return count;
}

int getVariableValue(char var, char vars[], int tableRow[], int varCount) {
  for (int i = 0; i < varCount; i++) {
    if (vars[i] == var)
      return tableRow[i];
  }
  return 0;
}

int getPrecedence(char op) {
  if (op == '!' || op == '~')
    return 5;
  if (op == '&')
    return 4;
  if (op == '|')
    return 3;
  if (op == '^')
    return 2;
  if (op == '>')
    return 1;
  if (op == '=')
    return 0;
  return -1;
}

bool isOperator(char c) {
  return (c == '!' || c == '~' || c == '&' || c == '|' || c == '^' ||
          c == '>' || c == '=');
}

void infixToPostfix(char infix[], char postfix[]) {
  char stack[100];
  int top = -1;
  int j = 0;

  for (int i = 0; infix[i] != '\0'; i++) {
    char c = infix[i];

    if (c == ' ')
      continue;

    if ((c >= 'A' && c <= 'Z') || c == '0' || c == '1') {
      postfix[j] = c;
      j++;
    } else if (c == '(') {
      stack[++top] = c;
    } else if (c == ')') {
      while (top >= 0 && stack[top] != '(') {
        postfix[j] = stack[top];
        j++;
        top--;
      }
      if (top >= 0)
        top--;
    } else if (isOperator(c)) {
      if (c == '!' || c == '~') {
        stack[++top] = c;
      } else {
        while (top >= 0 && stack[top] != '(' &&
               getPrecedence(stack[top]) >= getPrecedence(c)) {
          postfix[j] = stack[top];
          j++;
          top--;
        }
        stack[++top] = c;
      }
    }
  }

  while (top >= 0) {
    postfix[j] = stack[top];
    j++;
    top--;
  }

  postfix[j] = '\0';
}

int evaluatePostfix(char postfix[], char vars[], int varCount, int tableRow[]) {
  int stack[100];
  int top = -1;

  for (int i = 0; postfix[i] != '\0'; i++) {
    char c = postfix[i];

    if (c >= 'A' && c <= 'Z') {
      int value = getVariableValue(c, vars, tableRow, varCount);
      stack[++top] = value;
    } else if (c == '0' || c == '1') {
      stack[++top] = c - '0';
    } else if (isOperator(c)) {
      if (c == '!' || c == '~') {
        if (top >= 0) {
          int operand = stack[top--];
          stack[++top] = !operand;
        }
      } else {
        if (top >= 1) {
          int operand2 = stack[top--];
          int operand1 = stack[top--];
          int result = 0;

          if (c == '&')
            result = operand1 & operand2;
          else if (c == '|')
            result = operand1 | operand2;
          else if (c == '^')
            result = operand1 ^ operand2;
          else if (c == '>')
            result = (!operand1) | operand2;
          else if (c == '=')
            result = (operand1 == operand2);

          stack[++top] = result;
        }
      }
    }
  }

  return (top >= 0) ? stack[top] : 0;
}

int evaluateExpression(char expr[], char vars[], int varCount, int tableRow[]) {
  char postfix[200];
  infixToPostfix(expr, postfix);
  return evaluatePostfix(postfix, vars, varCount, tableRow);
}

void printTruthTableSingle(int varCount, char vars[], char expr[],
                           int table[][500]) {
  bool allTrue = true;
  bool allFalse = true;

  cout << "\nTRUTH TABLE:\n\n";

  int rows = pow(2, varCount);
  int colWidth = 6;
  int totalCols = varCount + 1;

  // Top border
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '-') << "+";
  cout << "\n";

  // Header row
  cout << "|";
  for (int i = 0; i < varCount; i++)
    cout << setw(colWidth / 2 + 1) << vars[i] << setw(colWidth / 2) << "|";
  cout << setw(colWidth / 2 + 1) << "R" << setw(colWidth / 2) << "|";
  cout << "\n";

  // Header separator
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '=') << "+";
  cout << "\n";

  // Data rows
  for (int i = 0; i < rows; i++) {
    cout << "|";
    for (int j = 0; j < varCount; j++)
      cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2)
           << "|";

    int result = evaluateExpression(expr, vars, varCount, table[i]);
    cout << setw(colWidth / 2 + 1) << result << setw(colWidth / 2) << "|";
    cout << "\n";

    if (result == 0)
      allTrue = false;
    if (result == 1)
      allFalse = false;
  }

  // Bottom border
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '-') << "+";
  cout << "\n";

  cout << "\nLOGICAL STATUS:\n";
  if (allTrue)
    cout << "  This expression is a Tautology.\n";
  else if (allFalse)
    cout << "  This expression is a Contradiction / Absurdity.\n";
  else
    cout << "  This expression is a Contingency.\n";
}

void printTruthTableDouble(int varCount, char vars[], char expr1[],
                           char expr2[], int table[][500]) {
  int rows = pow(2, varCount);
  bool equivalent = true;
  bool allTrue1 = true, allFalse1 = true;
  bool allTrue2 = true, allFalse2 = true;

  cout << "\nTRUTH TABLE:\n\n";

  int colWidth = 6;
  int totalCols = varCount + 2;

  // Top border
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '-') << "+";
  cout << "\n";

  // Header row
  cout << "|";
  for (int i = 0; i < varCount; i++)
    cout << setw(colWidth / 2 + 1) << vars[i] << setw(colWidth / 2) << "|";
  cout << setw(colWidth / 2) << "R1" << setw(colWidth / 2 + 1) << "|";
  cout << setw(colWidth / 2) << "R2" << setw(colWidth / 2 + 1) << "|";
  cout << "\n";

  // Header separator
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '=') << "+";
  cout << "\n";

  // Data rows
  for (int i = 0; i < rows; i++) {
    cout << "|";
    for (int j = 0; j < varCount; j++)
      cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2)
           << "|";

    int result1 = evaluateExpression(expr1, vars, varCount, table[i]);
    int result2 = evaluateExpression(expr2, vars, varCount, table[i]);

    cout << setw(colWidth / 2 + 1) << result1 << setw(colWidth / 2) << "|";
    cout << setw(colWidth / 2 + 1) << result2 << setw(colWidth / 2) << "|";
    cout << "\n";

    if (result1 != result2)
      equivalent = false;
    if (result1 == 0)
      allTrue1 = false;
    if (result1 == 1)
      allFalse1 = false;
    if (result2 == 0)
      allTrue2 = false;
    if (result2 == 1)
      allFalse2 = false;
  }

  // Bottom border
  cout << "+";
  for (int i = 0; i < totalCols; i++)
    cout << string(colWidth, '-') << "+";
  cout << "\n";

  cout << "\nEQUIVALENCE CHECK:\n";
  if (equivalent)
    cout << "  The two statements are Equivalent.\n";
  else
    cout << "  The two statements are NOT Equivalent.\n";

  cout << "\nLOGICAL STATUS:\n";
  cout << "  Expression 1: ";
  if (allTrue1)
    cout << "Tautology\n";
  else if (allFalse1)
    cout << "Contradiction / Absurdity\n";
  else
    cout << "Contingency\n";

  cout << "  Expression 2: ";
  if (allTrue2)
    cout << "Tautology\n";
  else if (allFalse2)
    cout << "Contradiction / Absurdity\n";
  else
    cout << "Contingency\n";
}

bool isValidExpression(char expr[]) {
  int brackets = 0;
  char prev = '\0';

  for (int i = 0; expr[i] != '\0'; i++) {
    char c = expr[i];

    if (c == ' ')
      continue;

    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '!' ||
          c == '~' || c == '&' || c == '|' || c == '^' || c == '>' ||
          c == '=' || c == '(' || c == ')')) {
      cout << "\nError: Invalid character '" << c << "'\n";
      return false;
    }

    if (c == '(')
      brackets++;
    if (c == ')')
      brackets--;

    if (brackets < 0) {
      cout << "\nError: Extra closing bracket ')'\n";
      return false;
    }

    if ((c == '&' || c == '|' || c == '^' || c == '>' || c == '=') &&
        (prev == '&' || prev == '|' || prev == '^' || prev == '>' ||
         prev == '=')) {
      cout << "\nError: Two operators in a row\n";
      return false;
    }

    prev = c;
  }

  if (brackets != 0) {
    cout << "\nError: Brackets are not balanced\n";
    return false;
  }

  if (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '=') {
    cout << "\nError: Expression ends with an operator\n";
    return false;
  }

  return true;
}

void printInstructionsmenu() {
  cout << "=================== USER'S MANUAL ===================\n\n";
  cout << "1. This program generates Truth Tables for Logical Expressions.\n";
  cout << "2. You can input either a Single Expression or Two Expressions.\n\n";
  cout << "3. Supported Logical Operators:\n";
  cout << "   ! or ~  :  NOT\n";
  cout << "   &       :  AND\n";
  cout << "   |       :  OR\n";
  cout << "   ^       :  XOR\n";
  cout << "   >       :  IMPLICATION  (P -> Q)\n";
  cout << "   =       :  BICONDITIONAL / EQUIVALENCE  (P <-> Q)\n\n";
  cout << "4. Variables should be single letters (A-Z or a-z).\n";
  cout << "5. Expressions can include parentheses '()' for grouping.\n\n";
  cout << "6. After entering expressions, the program:\n";
  cout << "   - Detects all unique variables.\n";
  cout << "   - Generates a Truth Table for all possible combinations.\n";
  cout << "   - Evaluates the expression(s) and shows results.\n\n";
  cout << "7. For two expressions, it also checks whether they are "
          "Equivalent.\n\n";
  cout << "8. Expression Results:\n";
  cout << "   Tautology      : True for all combinations\n";
  cout << "   Contradiction  : False for all combinations\n";
  cout << "   Contingency    : True for some, False for others\n\n";
  cout << "=====================================================\n";
}

void printStatementMode() {
  system("clear");
  cout << "=====================================================" << endl;
  cout << "               STATEMENT EVALUATION MODE             " << endl;
  cout << "=====================================================" << endl
       << endl;
}

void normalizeExpression(const char src[], char dst[]) {
  int j = 0;
  for (int i = 0; src[i] != '\0'; i++) {
    char c = src[i];
    if (c == ' ')
      continue;
    if (c >= 'a' && c <= 'z')
      c = c - 32;
    dst[j++] = c;
  }
  dst[j] = '\0';
}

int detectVariablesMultiple(char exprs[][100], int exprCount, char vars[]) {
  int count = 0;
  for (int k = 0; k < exprCount; k++) {
    for (int i = 0; exprs[k][i] != '\0'; i++) {
      char c = exprs[k][i];
      if (c >= 'a' && c <= 'z')
        c = c - 32;
      if (c >= 'A' && c <= 'Z') {
        bool found = false;
        for (int j = 0; j < count; j++) {
          if (vars[j] == c) {
            found = true;
            break;
          }
        }
        if (!found) {
          vars[count++] = c;
        }
      }
    }
  }
  return count;
}

bool checkEntailment(char premises[][100], int premiseCount, char conclusion[],
                     char vars[], int varCount, bool &vacuous) {
  static int table[1000][500];
  generateTruthTable(varCount, table);
  int rows = pow(2, varCount);
  vacuous = true;

  for (int i = 0; i < rows; i++) {
    bool allPremisesTrue = true;
    for (int p = 0; p < premiseCount; p++) {
      int r = evaluateExpression(premises[p], vars, varCount, table[i]);
      if (r == 0) {
        allPremisesTrue = false;
        break;
      }
    }
    if (allPremisesTrue) {
      vacuous = false;
      int conclVal = evaluateExpression(conclusion, vars, varCount, table[i]);
      if (conclVal == 0)
        return false; // counterexample found
    }
  }

  return true; // holds (possibly vacuously)
}

bool detectSimpleLaw(char premises[][100], int premiseCount, char conclusion[]) {
  char nprem[10][120];
  char ncon[120];
  for (int i = 0; i < premiseCount; i++)
    normalizeExpression(premises[i], nprem[i]);
  normalizeExpression(conclusion, ncon);

  string con(ncon);
  // strip outer parentheses if present
  auto strip = [](const string &s) {
    if (s.size() >= 2 && s.front() == '(' && s.back() == ')')
      return s.substr(1, s.size() - 2);
    return s;
  };

  // Conjunction Introduction: premises contain P and Q, conclusion is P&Q
  if (premiseCount >= 2) {
    for (int i = 0; i < premiseCount; i++) {
      for (int j = i + 1; j < premiseCount; j++) {
        string a = strip(string(nprem[i]));
        string b = strip(string(nprem[j]));
        string comb = a + "&" + b;
        string comb2 = b + "&" + a;
        if (strip(con) == comb || strip(con) == comb2) {
          return true;
        }
      }
    }
  }

  // Conjunction Elimination: premise is P&Q and conclusion is P or Q
  if (premiseCount == 1) {
    string p0 = strip(string(nprem[0]));
    size_t pos = p0.find('&');
    if (pos != string::npos) {
      string left = p0.substr(0, pos);
      string right = p0.substr(pos + 1);
      if (strip(con) == left || strip(con) == right)
        return true;
    }
  }

  // Disjunction Introduction: from P infer P|Q
  if (premiseCount == 1) {
    string p0 = strip(string(nprem[0]));
    string c = strip(con);
    size_t pos = c.find('|');
    if (pos != string::npos) {
      string left = c.substr(0, pos);
      string right = c.substr(pos + 1);
      if (left == p0 || right == p0)
        return true;
    }
  }

  // Disjunctive Syllogism: P|Q and ~P => Q (or symmetric)
  if (premiseCount >= 2) {
    for (int i = 0; i < premiseCount; i++) {
      for (int j = 0; j < premiseCount; j++) {
        if (i == j)
          continue;
        string a = strip(string(nprem[i]));
        string b = strip(string(nprem[j]));
        // find disjunction
        size_t pos = a.find('|');
        if (pos != string::npos) {
          string left = a.substr(0, pos);
          string right = a.substr(pos + 1);
          // check b is negation of left
          string nb = b;
          if ((nb.size() >= 2 && (nb[0] == '!' || nb[0] == '~')) && nb.substr(1) == left) {
            if (strip(con) == right)
              return true;
          }
          // check b is negation of right
          if ((nb.size() >= 2 && (nb[0] == '!' || nb[0] == '~')) && nb.substr(1) == right) {
            if (strip(con) == left)
              return true;
          }
        }
      }
    }
  }

  return false;
}

void statementEvaluationMode() {
  char premises[10][100];
  char conclusion[100];
  char vars[1000];
  int premiseCount = 0;

  cout << "Enter number of premises (1-10): ";
  int n;
  while (!(cin >> n) || n < 1 || n > 10) {
    cout << "Invalid number. Enter 1-10: ";
    clearBuffer();
  }
  premiseCount = n;
  clearBuffer();

  for (int i = 0; i < premiseCount; i++) {
    cout << "Enter premise " << (i + 1) << ": ";
    cin.getline(premises[i], 100);
  }

  cout << "Enter conclusion: ";
  cin.getline(conclusion, 100);

  // validate
  bool bad = false;
  for (int i = 0; i < premiseCount; i++) {
    if (!isValidExpression(premises[i])) {
      bad = true;
      break;
    }
  }
  if (!bad && !isValidExpression(conclusion))
    bad = true;

  if (bad) {
    cout << "\nInvalid expressions entered. Press any key to return...";
    cin.get();
    return;
  }

  int varCount = detectVariablesMultiple(premises, premiseCount, vars);
  // include conclusion variables
  char tempvars[1000];
  int ccon = detectvariables(conclusion, tempvars);
  for (int i = 0; i < ccon; i++) {
    bool found = false;
    for (int j = 0; j < varCount; j++) {
      if (vars[j] == tempvars[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      vars[varCount++] = tempvars[i];
    }
  }

  printVariables(varCount, vars);

  bool vacuous = false;
  bool entails = checkEntailment(premises, premiseCount, conclusion, vars, varCount, vacuous);

  bool lawMatched = detectSimpleLaw(premises, premiseCount, conclusion);

  cout << "\nRESULTS:\n";
  if (lawMatched)
    cout << "  A simple logical law (conjunction/disjunction/disjunctive syllogism) applies.\n";
  cout << "  Semantic entailment: ";
  if (entails) {
    if (vacuous)
      cout << "Holds vacuously (no valuation makes all premises true).\n";
    else
      cout << "Conclusion follows from premises.\n";
  } else {
    cout << "Conclusion does NOT follow (counterexample exists).\n";
  }

  cout << "\nPress any key to return back to Menu...";
  cin.get();
}

// =============================================
// STEP-BY-STEP SIMPLIFICATION FUNCTIONS -------
// =============================================

int newNode(char type, char value, int left, int right) {
  int idx = gNodeCount++;
  gNodes[idx].type = type;
  gNodes[idx].value = value;
  gNodes[idx].left = left;
  gNodes[idx].right = right;
  return idx;
}

void resetNodes() { gNodeCount = 0; }

int buildTreeFromPostfix(char postfix[]) {
  int stack[200];
  int top = -1;
  for (int i = 0; postfix[i] != '\0'; i++) {
    char c = postfix[i];
    if ((c >= 'A' && c <= 'Z') || c == '0' || c == '1') {
      char t = (c >= 'A' && c <= 'Z') ? 'V' : 'C';
      stack[++top] = newNode(t, c, -1, -1);
    } else if (c == '!' || c == '~') {
      int child = stack[top--];
      stack[++top] = newNode('O', '!', -1, child);
    } else if (isOperator(c)) {
      int right = stack[top--];
      int left = stack[top--];
      stack[++top] = newNode('O', c, left, right);
    }
  }
  return (top >= 0) ? stack[top] : -1;
}

int parseToTree(char expr[]) {
  char normalized[200];
  normalizeExpression(expr, normalized);
  char postfix[200];
  infixToPostfix(normalized, postfix);
  return buildTreeFromPostfix(postfix);
}

void treeToStr(int root, char result[], int &pos, int parentPrec,
               bool isRight) {
  if (root < 0)
    return;
  ExprNode &nd = gNodes[root];

  if (nd.type == 'V' || nd.type == 'C') {
    result[pos++] = nd.value;
    result[pos] = '\0';
    return;
  }

  if (nd.value == '!') {
    result[pos++] = '!';
    if (nd.right >= 0 && gNodes[nd.right].type == 'O' &&
        gNodes[nd.right].value != '!' && gNodes[nd.right].value != '~') {
      result[pos++] = '(';
      treeToStr(nd.right, result, pos, -1, false);
      result[pos++] = ')';
    } else {
      treeToStr(nd.right, result, pos, 5, false);
    }
    result[pos] = '\0';
    return;
  }

  int myPrec = getPrecedence(nd.value);
  bool needParens =
      (myPrec < parentPrec) || (myPrec == parentPrec && isRight);

  if (needParens)
    result[pos++] = '(';
  treeToStr(nd.left, result, pos, myPrec, false);

  // Print operator symbol readably
  if (nd.value == '>')
    result[pos++] = '>';
  else if (nd.value == '=')
    result[pos++] = '=';
  else
    result[pos++] = nd.value;

  treeToStr(nd.right, result, pos, myPrec, true);
  if (needParens)
    result[pos++] = ')';
  result[pos] = '\0';
}

void getExpressionString(int root, char result[]) {
  int pos = 0;
  treeToStr(root, result, pos, -1, false);
  result[pos] = '\0';
}

int copyTree(int root) {
  if (root < 0)
    return -1;
  int l = copyTree(gNodes[root].left);
  int r = copyTree(gNodes[root].right);
  return newNode(gNodes[root].type, gNodes[root].value, l, r);
}

bool treesEqual(int a, int b) {
  if (a < 0 && b < 0)
    return true;
  if (a < 0 || b < 0)
    return false;
  if (gNodes[a].type != gNodes[b].type)
    return false;
  if (gNodes[a].value != gNodes[b].value)
    return false;
  return treesEqual(gNodes[a].left, gNodes[b].left) &&
         treesEqual(gNodes[a].right, gNodes[b].right);
}

bool isNegationOf(int a, int b) {
  if (a >= 0 && gNodes[a].type == 'O' && gNodes[a].value == '!') {
    return treesEqual(gNodes[a].right, b);
  }
  return false;
}

bool applyRule(int &root, char lawName[]) {
  if (root < 0)
    return false;
  ExprNode &n = gNodes[root];

  // --- Operator Elimination Rules ---

  // Material Implication: P>Q -> !P|Q
  if (n.type == 'O' && n.value == '>') {
    int notP = newNode('O', '!', -1, n.left);
    root = newNode('O', '|', notP, n.right);
    strcpy(lawName, "Material Implication");
    return true;
  }

  // Biconditional Elimination: P=Q -> (P&Q)|(!P&!Q)
  if (n.type == 'O' && n.value == '=') {
    int pCopy = copyTree(n.left);
    int qCopy = copyTree(n.right);
    int pq = newNode('O', '&', n.left, n.right);
    int notP = newNode('O', '!', -1, pCopy);
    int notQ = newNode('O', '!', -1, qCopy);
    int npnq = newNode('O', '&', notP, notQ);
    root = newNode('O', '|', pq, npnq);
    strcpy(lawName, "Biconditional Elimination");
    return true;
  }

  // XOR Definition: P^Q -> (P&!Q)|(!P&Q)
  if (n.type == 'O' && n.value == '^') {
    int pCopy = copyTree(n.left);
    int qCopy = copyTree(n.right);
    int notQ = newNode('O', '!', -1, n.right);
    int notP = newNode('O', '!', -1, pCopy);
    int pnq = newNode('O', '&', n.left, notQ);
    int npq = newNode('O', '&', notP, qCopy);
    root = newNode('O', '|', pnq, npq);
    strcpy(lawName, "XOR Definition");
    return true;
  }

  // --- Negation Rules ---

  // Double Negation: !!P -> P
  if (n.type == 'O' && n.value == '!' && n.right >= 0) {
    ExprNode &child = gNodes[n.right];
    if (child.type == 'O' && child.value == '!') {
      root = child.right;
      strcpy(lawName, "Double Negation Law");
      return true;
    }
  }

  // De Morgan's Law: !(P&Q) -> !P|!Q
  if (n.type == 'O' && n.value == '!' && n.right >= 0) {
    ExprNode &child = gNodes[n.right];
    if (child.type == 'O' && child.value == '&') {
      int notL = newNode('O', '!', -1, child.left);
      int notR = newNode('O', '!', -1, child.right);
      root = newNode('O', '|', notL, notR);
      strcpy(lawName, "De Morgan's Law");
      return true;
    }
  }

  // De Morgan's Law: !(P|Q) -> !P&!Q
  if (n.type == 'O' && n.value == '!' && n.right >= 0) {
    ExprNode &child = gNodes[n.right];
    if (child.type == 'O' && child.value == '|') {
      int notL = newNode('O', '!', -1, child.left);
      int notR = newNode('O', '!', -1, child.right);
      root = newNode('O', '&', notL, notR);
      strcpy(lawName, "De Morgan's Law");
      return true;
    }
  }

  // --- Simplification Rules ---

  // Complement: P&!P -> 0
  if (n.type == 'O' && n.value == '&') {
    if (isNegationOf(n.right, n.left) || isNegationOf(n.left, n.right)) {
      root = newNode('C', '0', -1, -1);
      strcpy(lawName, "Complement Law");
      return true;
    }
  }

  // Complement: P|!P -> 1
  if (n.type == 'O' && n.value == '|') {
    if (isNegationOf(n.right, n.left) || isNegationOf(n.left, n.right)) {
      root = newNode('C', '1', -1, -1);
      strcpy(lawName, "Complement Law");
      return true;
    }
  }

  // Idempotent: P&P -> P
  if (n.type == 'O' && n.value == '&' && treesEqual(n.left, n.right)) {
    root = n.left;
    strcpy(lawName, "Idempotent Law");
    return true;
  }

  // Idempotent: P|P -> P
  if (n.type == 'O' && n.value == '|' && treesEqual(n.left, n.right)) {
    root = n.left;
    strcpy(lawName, "Idempotent Law");
    return true;
  }

  // Identity: P&1 -> P
  if (n.type == 'O' && n.value == '&') {
    if (n.right >= 0 && gNodes[n.right].type == 'C' &&
        gNodes[n.right].value == '1') {
      root = n.left;
      strcpy(lawName, "Identity Law");
      return true;
    }
    if (n.left >= 0 && gNodes[n.left].type == 'C' &&
        gNodes[n.left].value == '1') {
      root = n.right;
      strcpy(lawName, "Identity Law");
      return true;
    }
  }

  // Identity: P|0 -> P
  if (n.type == 'O' && n.value == '|') {
    if (n.right >= 0 && gNodes[n.right].type == 'C' &&
        gNodes[n.right].value == '0') {
      root = n.left;
      strcpy(lawName, "Identity Law");
      return true;
    }
    if (n.left >= 0 && gNodes[n.left].type == 'C' &&
        gNodes[n.left].value == '0') {
      root = n.right;
      strcpy(lawName, "Identity Law");
      return true;
    }
  }

  // Domination: P&0 -> 0
  if (n.type == 'O' && n.value == '&') {
    if ((n.right >= 0 && gNodes[n.right].type == 'C' &&
         gNodes[n.right].value == '0') ||
        (n.left >= 0 && gNodes[n.left].type == 'C' &&
         gNodes[n.left].value == '0')) {
      root = newNode('C', '0', -1, -1);
      strcpy(lawName, "Domination Law");
      return true;
    }
  }

  // Domination: P|1 -> 1
  if (n.type == 'O' && n.value == '|') {
    if ((n.right >= 0 && gNodes[n.right].type == 'C' &&
         gNodes[n.right].value == '1') ||
        (n.left >= 0 && gNodes[n.left].type == 'C' &&
         gNodes[n.left].value == '1')) {
      root = newNode('C', '1', -1, -1);
      strcpy(lawName, "Domination Law");
      return true;
    }
  }

  // Absorption: P&(P|Q) -> P
  if (n.type == 'O' && n.value == '&') {
    if (n.right >= 0 && gNodes[n.right].type == 'O' &&
        gNodes[n.right].value == '|') {
      if (treesEqual(n.left, gNodes[n.right].left) ||
          treesEqual(n.left, gNodes[n.right].right)) {
        root = n.left;
        strcpy(lawName, "Absorption Law");
        return true;
      }
    }
    if (n.left >= 0 && gNodes[n.left].type == 'O' &&
        gNodes[n.left].value == '|') {
      if (treesEqual(n.right, gNodes[n.left].left) ||
          treesEqual(n.right, gNodes[n.left].right)) {
        root = n.right;
        strcpy(lawName, "Absorption Law");
        return true;
      }
    }
  }

  // Absorption: P|(P&Q) -> P
  if (n.type == 'O' && n.value == '|') {
    if (n.right >= 0 && gNodes[n.right].type == 'O' &&
        gNodes[n.right].value == '&') {
      if (treesEqual(n.left, gNodes[n.right].left) ||
          treesEqual(n.left, gNodes[n.right].right)) {
        root = n.left;
        strcpy(lawName, "Absorption Law");
        return true;
      }
    }
    if (n.left >= 0 && gNodes[n.left].type == 'O' &&
        gNodes[n.left].value == '&') {
      if (treesEqual(n.right, gNodes[n.left].left) ||
          treesEqual(n.right, gNodes[n.left].right)) {
        root = n.right;
        strcpy(lawName, "Absorption Law");
        return true;
      }
    }
  }

  // Negation of constant: !0 -> 1, !1 -> 0
  if (n.type == 'O' && n.value == '!' && n.right >= 0 &&
      gNodes[n.right].type == 'C') {
    if (gNodes[n.right].value == '0') {
      root = newNode('C', '1', -1, -1);
      strcpy(lawName, "Negation of Constant");
      return true;
    }
    if (gNodes[n.right].value == '1') {
      root = newNode('C', '0', -1, -1);
      strcpy(lawName, "Negation of Constant");
      return true;
    }
  }

  // --- Recurse into children ---
  if (n.left >= 0) {
    if (applyRule(n.left, lawName))
      return true;
  }
  if (n.right >= 0) {
    if (applyRule(n.right, lawName))
      return true;
  }

  return false;
}

void printStepByStep(char expr[], char finalResult[]) {
  resetNodes();
  int root = parseToTree(expr);

  char result[500];
  getExpressionString(root, result);
  cout << "  Start:    " << result << endl;

  char lawName[100];
  int step = 1;
  while (applyRule(root, lawName)) {
    getExpressionString(root, result);
    cout << "  Step " << setw(2) << step << ":   " << result;
    // Pad the expression for alignment
    int len = strlen(result);
    if (len < 30) {
      for (int i = 0; i < 30 - len; i++)
        cout << ' ';
    } else {
      cout << "  ";
    }
    cout << "[" << lawName << "]" << endl;
    step++;
    if (step > 50) {
      cout << "  (Maximum simplification steps reached)" << endl;
      break;
    }
  }

  if (step == 1)
    cout << "  (No simplification rules apply)" << endl;

  getExpressionString(root, result);
  strcpy(finalResult, result);
}

void printStepByStepHeader() {
  system("clear");
  cout << "=====================================================" << endl;
  cout << "           STEP-BY-STEP SIMPLIFICATION MODE           " << endl;
  cout << "=====================================================" << endl
       << endl;
}

void stepByStepEquivalenceMode() {
  int mode;
  cout << "  1. Simplify a single expression" << endl;
  cout << "  2. Compare two expressions step-by-step" << endl;
  cout << "\nEnter choice (1 or 2): ";
  while (!(cin >> mode) || (mode != 1 && mode != 2)) {
    cout << "Enter 1 or 2: ";
    clearBuffer();
  }
  clearBuffer();

  if (mode == 1) {
    char raw[100];
    cout << "\nEnter expression: ";
    cin.getline(raw, 100);

    if (!isValidExpression(raw)) {
      cout << "\nInvalid expression. Press any key to return...";
      cin.get();
      return;
    }

    cout << "\n--- Step-by-Step Simplification ---\n" << endl;
    char finalResult[500];
    printStepByStep(raw, finalResult);
    cout << "\n  Final Result: " << finalResult << endl;

  } else {
    char raw1[100], raw2[100];
    cout << "\nEnter first expression:  ";
    cin.getline(raw1, 100);
    cout << "Enter second expression: ";
    cin.getline(raw2, 100);

    if (!isValidExpression(raw1) || !isValidExpression(raw2)) {
      cout << "\nInvalid expression(s). Press any key to return...";
      cin.get();
      return;
    }

    char final1[500], final2[500];

    cout << "\n--- Simplifying Expression 1 ---\n" << endl;
    printStepByStep(raw1, final1);

    cout << "\n--- Simplifying Expression 2 ---\n" << endl;
    printStepByStep(raw2, final2);

    // Check simplified forms
    cout << "\n=====================================================" << endl;
    cout << "  Expression 1 simplifies to: " << final1 << endl;
    cout << "  Expression 2 simplifies to: " << final2 << endl;

    if (strcmp(final1, final2) == 0) {
      cout << "\n  RESULT: Both expressions simplify to the same form.";
      cout << "\n          The expressions are LOGICALLY EQUIVALENT." << endl;
    } else {
      // Verify with truth table even if forms differ
      char norm1[100], norm2[100];
      normalizeExpression(raw1, norm1);
      normalizeExpression(raw2, norm2);
      char vars[100];
      int varCount = combineVariables(norm1, norm2, vars);
      static int table[1000][500];
      generateTruthTable(varCount, table);
      int rows = (int)pow(2, varCount);
      bool equivalent = true;
      for (int i = 0; i < rows; i++) {
        int r1 = evaluateExpression(norm1, vars, varCount, table[i]);
        int r2 = evaluateExpression(norm2, vars, varCount, table[i]);
        if (r1 != r2) {
          equivalent = false;
          break;
        }
      }
      if (equivalent) {
        cout << "\n  RESULT: Simplified forms differ, but truth table";
        cout << "\n          confirms they are LOGICALLY EQUIVALENT." << endl;
      } else {
        cout << "\n  RESULT: The expressions are NOT EQUIVALENT." << endl;
      }
    }
    cout << "=====================================================" << endl;
  }

  cout << "\nPress any key to return back to Menu...";
  cin.get();
}