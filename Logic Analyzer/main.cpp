#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

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
void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][500]);
void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][500]);
int evaluateExpression(char expr[], char vars[], int varCount, int tablerow[]);
bool isValidExpression(char expr[]);
void printInstructionsmenu();
void clearBuffer();
void printsingleexp();
void printdoubleexp();
void printinstructions();

int main()
{
    int option = 0;

    while (option != 4)
    {
        printHeader();
        printMenu();
        option = getUserChoice();

        if (option == 1)
        {
            printsingleexp();
            char expr[100];
            char vars[1000];
            static int table[1000][500];
            cout << "\nSingle Expression Selected\n" << endl;
            inputSingleExpression(expr);

            if (!isValidExpression(expr))
            {
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
        }
        else if (option == 2)
        {
            printdoubleexp();
            char expr1[100], expr2[100], vars[1000];
            static int table[1000][500];

            cout << "\nTwo Expressions Selected\n" << endl;
            inputTwoExpressions(expr1, expr2);

            if (!isValidExpression(expr1) || !isValidExpression(expr2))
            {
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
        }
        else if (option == 3)
        {
            system("clear");
            printinstructions();
            printInstructionsmenu();
            cout << "\nPress any key to return back to Menu...";
            cin.get();
        }
        else if (option == 4)
        {
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

void clearBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader()
{
    system("clear");
    cout << "=====================================================\n";
    cout << "       LOGICAL ANALYZER - TRUTH TABLE GENERATOR     \n";
    cout << "=====================================================\n\n";
}

void printsingleexp()
{
    system("clear");
    cout << "=====================================================\n";
    cout << "               SINGLE EXPRESSION MODE               \n";
    cout << "=====================================================\n\n";
}

void printdoubleexp()
{
    system("clear");
    cout << "=====================================================\n";
    cout << "               DOUBLE EXPRESSION MODE               \n";
    cout << "=====================================================\n\n";
}

void printinstructions()
{
    cout << "=====================================================\n";
    cout << "                    INSTRUCTIONS                     \n";
    cout << "=====================================================\n\n";
}

void printMenu()
{
    cout << "  1. Single Expression\n";
    cout << "  2. Two Expressions\n";
    cout << "  3. User's Manual\n";
    cout << "  4. Exit\n";
}

int getUserChoice()
{
    int choice;
    cout << "\nEnter your choice: ";

    while (!(cin >> choice))
    {
        cout << "Invalid input. Please enter 1, 2, 3, or 4: ";
        clearBuffer();
    }
    clearBuffer();

    return choice;
}

void inputSingleExpression(char expr[])
{
    cout << "Enter the logical expression: ";
    cin.getline(expr, 100);
}

void inputTwoExpressions(char expr1[], char expr2[])
{
    cout << "Enter first expression:  ";
    cin.getline(expr1, 100);
    cout << "Enter second expression: ";
    cin.getline(expr2, 100);
}

int detectvariables(char expr[], char vars[])
{
    int count = 0;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] >= 'a' && expr[i] <= 'z')
            expr[i] = expr[i] - 32;

        if (expr[i] >= 'A' && expr[i] <= 'Z')
        {
            bool found = false;
            for (int j = 0; j < count; j++)
            {
                if (vars[j] == expr[i])
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                vars[count] = expr[i];
                count++;
            }
        }
    }
    return count;
}

void printVariables(int varCount, char vars[])
{
    cout << "\nVariables detected: ";
    for (int i = 0; i < varCount; i++)
        cout << vars[i] << " ";
    cout << "\n";
}

void generateTruthTable(int varCount, int table[][500])
{
    int rows = pow(2, varCount);

    for (int i = 0; i < rows; i++)
    {
        int value = i;
        for (int j = varCount - 1; j >= 0; j--)
        {
            table[i][j] = value % 2;
            value = value / 2;
        }
    }
}

int combineVariables(char expr1[], char expr2[], char vars[])
{
    int count = 0;
    char temp[10];

    int c1 = detectvariables(expr1, temp);
    for (int i = 0; i < c1; i++)
    {
        vars[count] = temp[i];
        count++;
    }

    int c2 = detectvariables(expr2, temp);
    for (int i = 0; i < c2; i++)
    {
        bool found = false;
        for (int j = 0; j < count; j++)
        {
            if (vars[j] == temp[i])
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            vars[count] = temp[i];
            count++;
        }
    }

    return count;
}

int getVariableValue(char var, char vars[], int tableRow[], int varCount)
{
    for (int i = 0; i < varCount; i++)
    {
        if (vars[i] == var)
            return tableRow[i];
    }
    return 0;
}

int getPrecedence(char op)
{
    if (op == '!' || op == '~') return 5;
    if (op == '&') return 4;
    if (op == '|') return 3;
    if (op == '^') return 2;
    if (op == '>') return 1;
    if (op == '=') return 0;
    return -1;
}

bool isOperator(char c)
{
    return (c == '!' || c == '~' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=');
}

void infixToPostfix(char infix[], char postfix[])
{
    char stack[100];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if (c == ' ')
            continue;

        if ((c >= 'A' && c <= 'Z') || c == '0' || c == '1')
        {
            postfix[j] = c;
            j++;
        }
        else if (c == '(')
        {
            stack[top] = c;
            top++;
        }
        else if (c == ')')
        {
            while (top >= 0 && stack[top] != '(')
            {
                postfix[j] = stack[top];
                j++;
                top--;
            }
            if (top >= 0)
                top--;
        }
        else if (isOperator(c))
        {
            if (c == '!' || c == '~')
            {
                stack[top] = c;
                top++;
            }
            else
            {
                while (top >= 0 && stack[top] != '(' &&
                       getPrecedence(stack[top]) >= getPrecedence(c))
                {
                    postfix[j] = stack[top];
                    j++;
                    top--;
                }
                stack[top] = c;
                top++;
            }
        }
    }

    while (top >= 0)
    {
        postfix[j] = stack[top];
        j++;
        top--;
    }

    postfix[j] = '\0';
}

int evaluatePostfix(char postfix[], char vars[], int varCount, int tableRow[])
{
    int stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (c >= 'A' && c <= 'Z')
        {
            int value = getVariableValue(c, vars, tableRow, varCount);
            stack[++top] = value;
        }
        else if (c == '0' || c == '1')
        {
            stack[++top] = c - '0';
        }
        else if (isOperator(c))
        {
            if (c == '!' || c == '~')
            {
                if (top >= 0)
                {
                    int operand = stack[top--];
                    stack[++top] = !operand;
                }
            }
            else
            {
                if (top >= 1)
                {
                    int operand2 = stack[top--];
                    int operand1 = stack[top--];
                    int result = 0;

                    if (c == '&')      result = operand1 & operand2;
                    else if (c == '|') result = operand1 | operand2;
                    else if (c == '^') result = operand1 ^ operand2;
                    else if (c == '>') result = (!operand1) | operand2;
                    else if (c == '=') result = (operand1 == operand2);

                    stack[top] = result;
                    top++;
                }
            }
        }
    }

    return (top >= 0) ? stack[top] : 0;
}

int evaluateExpression(char expr[], char vars[], int varCount, int tableRow[])
{
    char postfix[200];
    infixToPostfix(expr, postfix);
    return evaluatePostfix(postfix, vars, varCount, tableRow);
}

void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][500])
{
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
    for (int i = 0; i < rows; i++)
    {
        cout << "|";
        for (int j = 0; j < varCount; j++)
            cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2) << "|";

        int result = evaluateExpression(expr, vars, varCount, table[i]);
        cout << setw(colWidth / 2 + 1) << result << setw(colWidth / 2) << "|";
        cout << "\n";

        if (result == 0) allTrue = false;
        if (result == 1) allFalse = false;
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

void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][500])
{
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
    for (int i = 0; i < rows; i++)
    {
        cout << "|";
        for (int j = 0; j < varCount; j++)
            cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2) << "|";

        int result1 = evaluateExpression(expr1, vars, varCount, table[i]);
        int result2 = evaluateExpression(expr2, vars, varCount, table[i]);

        cout << setw(colWidth / 2 + 1) << result1 << setw(colWidth / 2) << "|";
        cout << setw(colWidth / 2 + 1) << result2 << setw(colWidth / 2) << "|";
        cout << "\n";

        if (result1 != result2) equivalent = false;
        if (result1 == 0) allTrue1 = false;
        if (result1 == 1) allFalse1 = false;
        if (result2 == 0) allTrue2 = false;
        if (result2 == 1) allFalse2 = false;
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
    if (allTrue1)       cout << "Tautology\n";
    else if (allFalse1) cout << "Contradiction / Absurdity\n";
    else                cout << "Contingency\n";

    cout << "  Expression 2: ";
    if (allTrue2)       cout << "Tautology\n";
    else if (allFalse2) cout << "Contradiction / Absurdity\n";
    else                cout << "Contingency\n";
}

bool isValidExpression(char expr[])
{
    int brackets = 0;
    char prev = '\0';

    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];

        if (c == ' ')
            continue;

        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              c == '!' || c == '~' || c == '&' || c == '|' ||
              c == '^' || c == '>' || c == '=' || c == '(' || c == ')'))
        {
            cout << "\nError: Invalid character '" << c << "'\n";
            return false;
        }

        if (c == '(') brackets++;
        if (c == ')') brackets--;

        if (brackets < 0)
        {
            cout << "\nError: Extra closing bracket ')'\n";
            return false;
        }

        if ((c == '&' || c == '|' || c == '^' || c == '>' || c == '=') &&
            (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '='))
        {
            cout << "\nError: Two operators in a row\n";
            return false;
        }

        prev = c;
    }

    if (brackets != 0)
    {
        cout << "\nError: Brackets are not balanced\n";
        return false;
    }

    if (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '=')
    {
        cout << "\nError: Expression ends with an operator\n";
        return false;
    }

    return true;
}

void printInstructionsmenu()
{
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
    cout << "7. For two expressions, it also checks whether they are Equivalent.\n\n";
    cout << "8. Expression Results:\n";
    cout << "   Tautology      : True for all combinations\n";
    cout << "   Contradiction  : False for all combinations\n";
    cout << "   Contingency    : True for some, False for others\n\n";
    cout << "=====================================================\n";
}