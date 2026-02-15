#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <windows.h>
using namespace std;

// Function to move cursor to specific position
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Get console width for centering
int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

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
void generateTruthTable(int varCount, int table[][5000]);
void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][5000]);
void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][5000]);
int evaluateExpression(char expr[], char vars[], int varCount, int tablerow[]);
bool isValidExpression(char expr[]);
void printInstructionsmenu();
void clearBuffer();
void printsingleexp();
void printdoubleexp();
void printinstructions();

int main()
{
    // for making ascii
    system("mode con cols=200 lines=40");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

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
            static int table[10000][5000];
            cout << "\nSingle expression Selected\n " << endl;
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
            static int table[10000][5000];

            cout << "\nTwo expressions Selected\n " << endl;
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

            cout << "\nProcess Complete. \nPress any key to return back to Menu...";
            cin.get();
        }
        else if (option == 3)
        {
            system("cls");
            printinstructions();
            printInstructionsmenu();
            cout << "\nPress any key to return back to Menu...";
            cin.get();
        }
        else if (option == 4)
        {
            cout << "Exiting Program...\n\n";
            cout << "Thanks For Using Our Program !!!";
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
    system("cls");

    int startX = 35; // horizontal center
    int startY = 2;  // vertical position

    gotoxy(startX, startY);
    cout << R"(██╗      ██████╗  ██████╗ ██╗ ██████╗ █████╗ ██╗          █████╗ ███╗   ██╗ █████╗ ██╗     ██╗   ██╗███████╗███████╗██████╗ )";

    gotoxy(startX, startY + 1);
    cout << R"(██║     ██╔═══██╗██╔════╝ ██║██╔════╝██╔══██╗██║         ██╔══██╗████╗  ██║██╔══██╗██║     ╚██╗ ██╔╝╚══███╔╝██╔════╝██╔══██╗)";

    gotoxy(startX, startY + 2);
    cout << R"(██║     ██║   ██║██║  ███╗██║██║     ███████║██║         ███████║██╔██╗ ██║███████║██║      ╚████╔╝   ███╔╝ █████╗  ██████╔╝)";

    gotoxy(startX, startY + 3);
    cout << R"(██║     ██║   ██║██║   ██║██║██║     ██╔══██║██║         ██╔══██║██║╚██╗██║██╔══██║██║       ╚██╔╝   ███╔╝  ██╔══╝  ██╔══██╗)";

    gotoxy(startX, startY + 4);
    cout << R"(███████╗╚██████╔╝╚██████╔╝██║╚██████╗██║  ██║███████╗    ██║  ██║██║ ╚████║██║  ██║███████╗   ██║   ███████╗███████╗██║  ██║)";

    gotoxy(startX, startY + 5);
    cout << R"(╚══════╝ ╚═════╝  ╚═════╝ ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝    ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚══════╝╚═╝  ╚═╝)";

    cout << endl
         << endl;
}

void printsingleexp()
{
    system("cls");

    int startX = 35; // center horizontally
    int startY = 2;  // top spacing

    gotoxy(startX, startY);
    cout << R"(███████╗██╗███╗   ██╗ ██████╗ ██╗     ███████╗    ███████╗██╗  ██╗██████╗ ██████╗ ███████╗███████╗███████╗██╗ ██████╗ ███╗   ██╗)";

    gotoxy(startX, startY + 1);
    cout << R"(██╔════╝██║████╗  ██║██╔════╝ ██║     ██╔════╝    ██╔════╝╚██╗██╔╝██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝██║██╔═══██╗████╗  ██║)";

    gotoxy(startX, startY + 2);
    cout << R"(███████╗██║██╔██╗ ██║██║  ███╗██║     █████╗      █████╗   ╚███╔╝ ██████╔╝██████╔╝█████╗  ███████╗███████╗██║██║   ██║██╔██╗ ██║)";

    gotoxy(startX, startY + 3);
    cout << R"(╚════██║██║██║╚██╗██║██║   ██║██║     ██╔══╝      ██╔══╝   ██╔██╗ ██╔═══╝ ██╔══██╗██╔══╝  ╚════██║╚════██║██║██║   ██║██║╚██╗██║)";

    gotoxy(startX, startY + 4);
    cout << R"(███████║██║██║ ╚████║╚██████╔╝███████╗███████╗    ███████╗██╔╝ ██╗██║     ██║  ██║███████╗███████║███████║██║╚██████╔╝██║ ╚████║)";

    gotoxy(startX, startY + 5);
    cout << R"(╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝)";

    cout << endl
         << endl;
}

void printdoubleexp()
{
    system("cls");

    int startX = 35; // center horizontally
    int startY = 2;  // top spacing

    gotoxy(startX, startY);
    cout << R"(██████╗  ██████╗ ██╗   ██╗██████╗ ██╗     ███████╗    ███████╗██╗  ██╗██████╗ ██████╗ ███████╗███████╗███████╗██╗ ██████╗ ███╗   ██╗)";

    gotoxy(startX, startY + 1);
    cout << R"(██╔══██╗██╔═══██╗██║   ██║██╔══██╗██║     ██╔════╝    ██╔════╝╚██╗██╔╝██╔══██╗██╔══██╗██╔════╝██╔════╝██╔════╝██║██╔═══██╗████╗  ██║)";

    gotoxy(startX, startY + 2);
    cout << R"(██║  ██║██║   ██║██║   ██║██████╔╝██║     █████╗      █████╗   ╚███╔╝ ██████╔╝██████╔╝█████╗  ███████╗███████╗██║██║   ██║██╔██╗ ██║)";

    gotoxy(startX, startY + 3);
    cout << R"(██║  ██║██║   ██║██║   ██║██╔══██╗██║     ██╔══╝      ██╔══╝   ██╔██╗ ██╔═══╝ ██╔══██╗██╔══╝  ╚════██║╚════██║██║██║   ██║██║╚██╗██║)";

    gotoxy(startX, startY + 4);
    cout << R"(██████╔╝╚██████╔╝╚██████╔╝██████╔╝███████╗███████╗    ███████╗██╔╝ ██╗██║     ██║  ██║███████╗███████║███████║██║╚██████╔╝██║ ╚████║)";

    gotoxy(startX, startY + 5);
    cout << R"(╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝)";

    cout << endl
         << endl;
}

void printinstructions()
{
    int startX = 45; // horizontal centering
    int startY = 2;  // vertical spacing

    gotoxy(startX, startY);
    cout << R"(██╗███╗   ██╗███████╗████████╗██████╗ ██╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗)";

    gotoxy(startX, startY + 1);
    cout << R"(██║████╗  ██║██╔════╝╚══██╔══╝██╔══██╗██║   ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝)";

    gotoxy(startX, startY + 2);
    cout << R"(██║██╔██╗ ██║███████╗   ██║   ██████╔╝██║   ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗)";

    gotoxy(startX, startY + 3);
    cout << R"(██║██║╚██╗██║╚════██║   ██║   ██╔══██╗██║   ██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║)";

    gotoxy(startX, startY + 4);
    cout << R"(██║██║ ╚████║███████║   ██║   ██║  ██║╚██████╔╝╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║)";

    gotoxy(startX, startY + 5);
    cout << R"(╚═╝╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝  ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝)";

    cout << endl
         << endl;
}

void printMenu()
{
    cout << "\n1. Press 1 to give Single Expression " << endl;
    cout << "2. Press 2 to give Two Expressions " << endl;
    cout << "3. Press 3 to See User's Manual " << endl;
    cout << "4. Press 4 to Exit the Program " << endl;
}

int getUserChoice()
{
    int choice;
    cout << "\nEnter your Choice: ";

    while (!(cin >> choice))
    {
        cout << "ERROR!! Please enter a Correct Choice (1, 2, or 3): ";
        clearBuffer();
    }
    clearBuffer();

    return choice;
}

void inputSingleExpression(char expr[])
{
    cout << "Enter the logical expression : ";
    cin.getline(expr, 100);
}

void inputTwoExpressions(char expr1[], char expr2[])
{
    cout << "Enter first Expression : ";
    cin.getline(expr1, 100);
    cout << "\nEnter second Expression : ";
    cin.getline(expr2, 100);
}

int detectvariables(char expr[], char vars[])
{
    int count = 0;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (expr[i] >= 'a' && expr[i] <= 'z')
        {
            expr[i] = expr[i] - 32;
        }

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
    cout << "\nVariables Detected are : ";
    for (int i = 0; i < varCount; i++)
    {
        cout << vars[i] << " ";
    }
    cout << endl;
}

void generateTruthTable(int varCount, int table[][5000])
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
        {
            return tableRow[i];
        }
    }
    return 0;
}

// Get precedence of operators
int getPrecedence(char op)
{
    if (op == '!' || op == '~')
    {
        return 5;
    }
    if (op == '&')
    {
        return 4;
    }
    if (op == '|')
    {
        return 3;
    }
    if (op == '^')
    {
        return 2;
    }
    if (op == '>')
    {
        return 1;
    }
    if (op == '=')
    {
        return 0;
    }
    return -1;
}

// Check if character is an operator
bool isOperator(char c)
{
    return (c == '!' || c == '~' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=');
}

// Convert infix expression to postfix using Shunting Yard Algorithm
void infixToPostfix(char infix[], char postfix[])
{
    char stack[100];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        // Skip spaces
        if (c == ' ')
            continue;

        // If operand (variable or constant), add to output
        if ((c >= 'A' && c <= 'Z') || c == '0' || c == '1')
        {
            postfix[j] = c;
            j++;
        }
        // If opening parenthesis, push to stack
        else if (c == '(')
        {
            stack[top] = c;
            top++;
        }
        // If closing parenthesis, pop until opening parenthesis
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
        // If operator
        else if (isOperator(c))
        {
            if (c == '!' || c == '~')
            {
                // Push NOT directly (right associative)
                stack[top] = c;
                top++;
            }
            else
            {
                // Pop operators with higher or equal precedence
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

    // Pop remaining operators from stack
    while (top >= 0)
    {
        postfix[j] = stack[top];
        j++;
        top--;
    }

    postfix[j] = '\0'; // Null terminate
}

// Evaluate postfix expression
int evaluatePostfix(char postfix[], char vars[], int varCount, int tableRow[])
{
    int stack[100];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        // If operand, push to stack
        if (c >= 'A' && c <= 'Z')
        {
            int value = getVariableValue(c, vars, tableRow, varCount);
            stack[++top] = value;
        }
        else if (c == '0' || c == '1')
        {
            stack[++top] = c - '0';
        }
        // If operator, pop operands and apply operation
        else if (isOperator(c))
        {
            if (c == '!' || c == '~')
            {
                // Unary operator - pop one operand
                if (top >= 0)
                {
                    int operand = stack[top--];
                    stack[++top] = !operand;
                }
            }
            else
            {
                // Binary operator - pop two operands
                if (top >= 1)
                {
                    int operand2 = stack[top--];
                    int operand1 = stack[top--];
                    int result = 0;

                    if (c == '&')
                    {
                        result = operand1 & operand2;
                    }
                    else if (c == '|')
                    {
                        result = operand1 | operand2;
                    }
                    else if (c == '^')
                    {
                        result = operand1 ^ operand2;
                    }
                    else if (c == '>')
                    {
                        result = (!operand1) | operand2; // P -> Q = ~P | Q
                    }
                    else if (c == '=')
                    {
                        result = (operand1 == operand2); // P <-> Q
                    }
                    stack[top] = result;
                    top++;
                }
            }
        }
    }

    // Final result is on top of stack
    return (top >= 0) ? stack[top] : 0;
}

// Main evaluation function that uses Shunting Yard Algorithm
int evaluateExpression(char expr[], char vars[], int varCount, int tableRow[])
{
    char postfix[200];

    // Step 1: Convert infix to postfix
    infixToPostfix(expr, postfix);

    // Step 2: Evaluate postfix expression
    return evaluatePostfix(postfix, vars, varCount, tableRow);
}

void printTruthTableSingle(int varCount, char vars[], char expr[], int table[][5000])
{
    bool allTrue = true;
    bool allFalse = true;

    cout << "\n\nTRUTH TABLE:\n\n";

    int rows = pow(2, varCount);
    int colWidth = 6;
    int totalCols = varCount + 1;
    int totalWidth = 1 + totalCols * (colWidth + 1);
    int consoleWidth = getConsoleWidth();
    int startX = (consoleWidth - totalWidth) / 2;
    if (startX < 0)
        startX = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int currentY = csbi.dwCursorPosition.Y;

    // Top border
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '-') << "+";

    // Header row
    gotoxy(startX, currentY++);
    cout << "|";
    for (int i = 0; i < varCount; i++)
    {
        cout << setw(colWidth / 2 + 1) << vars[i] << setw(colWidth / 2) << "|";
    }
    cout << setw(colWidth / 2 + 1) << "R" << setw(colWidth / 2) << "|";

    // Header separator
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '=') << "+";

    // Data rows
    for (int i = 0; i < rows; i++)
    {
        gotoxy(startX, currentY++);
        cout << "|";

        for (int j = 0; j < varCount; j++)
        {
            cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2) << "|";
        }

        int result = evaluateExpression(expr, vars, varCount, table[i]);
        cout << setw(colWidth / 2 + 1) << result << setw(colWidth / 2) << "|";

        if (result == 0)
            allTrue = false;
        if (result == 1)
            allFalse = false;
    }

    // Bottom border
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '-') << "+";

    // Move cursor below table for status messages
    gotoxy(0, currentY + 1);
    cout << "\nLOGICAL STATUS: \n";
    if (allTrue)
    {
        cout << "\nThis Expression is Tautology.\n";
    }
    else if (allFalse)
    {
        cout << "\nThis Expression is Contradiction/Absurdity.\n";
    }
    else
    {
        cout << "\nThis Expression is Contigency.\n";
    }
}

void printTruthTableDouble(int varCount, char vars[], char expr1[], char expr2[], int table[][5000])
{
    int rows = pow(2, varCount);
    bool equivalent = true;
    bool allTrue1 = true, allFalse1 = true;
    bool allTrue2 = true, allFalse2 = true;

    cout << "\n\nTRUTH TABLE:\n\n";

    int colWidth = 6;
    int totalCols = varCount + 2;
    int totalWidth = 1 + totalCols * (colWidth + 1);
    int consoleWidth = getConsoleWidth();
    int startX = (consoleWidth - totalWidth) / 2;
    if (startX < 0)
        startX = 0;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int currentY = csbi.dwCursorPosition.Y;

    // Top border
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '-') << "+";

    // Header row
    gotoxy(startX, currentY++);
    cout << "|";
    for (int i = 0; i < varCount; i++)
    {
        cout << setw(colWidth / 2 + 1) << vars[i] << setw(colWidth / 2) << "|";
    }
    cout << setw(colWidth / 2) << "R1" << setw(colWidth / 2 + 1) << "|";
    cout << setw(colWidth / 2) << "R2" << setw(colWidth / 2 + 1) << "|";

    // Header separator
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '=') << "+";

    // Data rows
    for (int i = 0; i < rows; i++)
    {
        gotoxy(startX, currentY++);
        cout << "|";

        for (int j = 0; j < varCount; j++)
        {
            cout << setw(colWidth / 2 + 1) << table[i][j] << setw(colWidth / 2) << "|";
        }

        int result1 = evaluateExpression(expr1, vars, varCount, table[i]);
        int result2 = evaluateExpression(expr2, vars, varCount, table[i]);

        cout << setw(colWidth / 2 + 1) << result1 << setw(colWidth / 2) << "|";
        cout << setw(colWidth / 2 + 1) << result2 << setw(colWidth / 2) << "|";

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
    gotoxy(startX, currentY++);
    cout << "+";
    for (int i = 0; i < totalCols; i++)
        cout << string(colWidth, '-') << "+";

    // Move cursor below table for status messages
    gotoxy(0, currentY + 1);
    cout << "\nEQUIVALENCE CHECK: \n";

    if (equivalent)
    {
        cout << "\nThe two Statements are Equivalent.\n";
    }
    else
    {
        cout << "\nThe two Statements are NOT Equivalent.\n";
    }

    cout << "\nLOGICAL STATUS: \n";
    cout << "\nExpression 1 is : ";
    if (allTrue1)
    {
        cout << "Tautology\n";
    }
    else if (allFalse1)
    {
        cout << "Contradiction / Absurdity\n";
    }
    else
    {
        cout << "Contigency\n";
    }

    cout << "\nExpression 2 is : ";
    if (allTrue2)
    {
        cout << "Tautology\n";
    }
    else if (allFalse2)
    {
        cout << " Contradiction / Absurdity\n";
    }
    else
    {
        cout << "Contigency\n";
    }
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

        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '!' || c == '~' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=' || c == '(' || c == ')'))
        {
            cout << " \nError: Invalid character " << c << "\n";
            return false;
        }

        if (c == '(')
        {
            brackets++;
        }
        if (c == ')')
        {
            brackets--;
        }
        if (brackets < 0)
        {
            cout << " \nError: Extra closing bracket ')'\n";
            return false;
        }

        if ((c == '&' || c == '|' || c == '^' || c == '>' || c == '=') &&
            (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '='))
        {
            cout << " \nError: Two operators together\n";
            return false;
        }

        prev = c;
    }

    if (brackets != 0)
    {
        cout << " \nError: Brackets are not balanced\n";
        return false;
    }

    if (prev == '&' || prev == '|' || prev == '^' || prev == '>' || prev == '=')
    {
        cout << " \nError: Expression ends with operator\n";
        return false;
    }

    return true;
}

void printInstructionsmenu()
{
    cout << endl
         << endl;
    cout << "=================== USER'S MANUAL ===================\n";
    cout << "1. This program generates Truth Tables for Logical Expressions.\n";
    cout << "2. You can input either a Single Expression or Two Expressions.\n";
    cout << "3. Supported Logical Operators:\n";
    cout << "   - ! or ~ : NOT\n";
    cout << "   - &      : AND\n";
    cout << "   - |      : OR\n";
    cout << "   - ^      : XOR\n";
    cout << "   - >      : IMPLICATION (P -> Q)\n";
    cout << "   - =      : BICONDITIONAL / EQUIVALENCE (P <-> Q)\n";
    cout << "4. Variables should be single letters (A-Z or a-z).\n";
    cout << "5. Expressions can include parentheses '()' for grouping.\n";
    cout << "6. After entering expressions, the program:\n";
    cout << "   - Detects all unique variables.\n";
    cout << "   - Generates a Truth Table for all possible combinations.\n";
    cout << "   - Evaluates the expression(s) and shows results.\n";
    cout << "7. For two expressions, it also checks whether the two are Equivalent.\n";
    cout << "8. Expression Results:\n";
    cout << "   - Tautology: True for all combinations\n";
    cout << "   - Contradiction / Absurdity: False for all combinations\n";
    cout << "   - Contingency: True for some and False for some combinations\n";
    cout << "=====================================================\n";
    cout << endl;
}