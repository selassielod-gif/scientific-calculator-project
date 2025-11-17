#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

/* ---------- Input Buffer Cleaner ---------- */
void clearInputBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

/* ---------- Menu Choice ---------- */
int getMenuChoice(){
    int choice;

    printf("\n========== SCIENTIFIC CALCULATOR ==========\n");
    printf("1. Addition(+)\n");
    printf("2. Subtraction(-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("5. Square Root (sqrt)\n");
    printf("6. Power (x^y)\n");
    printf("7. Sine sin(x)\n");
    printf("8. Cosine cos(x)\n");
    printf("9. Tangent tan(x)\n");
    printf("10. Log base 10 (log10)\n");
    printf("11. Natural log (ln)\n");
    printf("Choose an Operation: ");

    while(scanf("%d", &choice) != 1 || choice < 1 || choice > 11){
        printf("Invalid Choice! Enter a number from 1 to 11: ");
        clearInputBuffer();
    }

    return choice;
}

/* ---------- Two-Number Input ---------- */
void getTwoNUmbers(double * a, double *b){
    printf("Enter TWO numbers: ");
    clearInputBuffer();

    while(scanf("%lf%*[, ]%lf", a, b) != 2){
        printf("Invalid Input! Enter two numbers: ");
        clearInputBuffer();
    }
}

/* ---------- One-NUmber Input ----------*/
double getOneNUmber(){
    double x;
    printf("Enter your Number: ");
    clearInputBuffer();

    while(scanf("%lf", &x) != 1){
        printf("Invalid Input! Enter a valid number\n");
        clearInputBuffer();
    }

    return x;
}

/* ---------- Yes/No for Memory (1 or 0) ----------*/
int getYesNoChoice(){
    int x;
    printf("Enter 1 (Yes) or 0 (No): ");

    while(scanf("%d", &x) != 1 || (x != 1 && x != 0)){
        printf("Invalid! Enter 1 or 0: ");
        clearInputBuffer();
    }

    return x;
}

/* ---------- Continue Choice ----------*/
char getContinueChoice(){
    char c;
    printf("Continue? (y/Y to continue, n/N to exit): ");
    clearInputBuffer();

    scanf("%c", &c);
    while(c != 'y' && c != 'Y' && c != 'n' && c != 'N'){
        printf("Invalid! Enter y/Y or n/N: ");
        clearInputBuffer();
        scanf("%c", &c);
    }

    return c;
}

/* ---------- Math Operations ---------- */
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }

double divide(double a, double b){
    while(b == 0){
        printf("Error: Division by zero! Enter new divisor: ");
        clearInputBuffer();
        scanf("%lf", &b);
    }
    return a / b;
}

double squareRoot(double x) { return sqrt(x); }
double power(double base, double exp) { return pow(base, exp); }
double sineDeg(double x) { return sin(x * M_PI / 180); }
double cosineDeg(double x) { return cos(x * M_PI / 180); }
double tangentDeg(double x) { return tan(x * M_PI / 180); }
double logBase10(double x) { return log10(x); }
double naturalLog(double x) { return log(x); }

/* ---------- Repeat Operation (Memory Feature) ---------- */
double repeatOperation(int op, double last, double second){

    switch (op)
    {
        case 1: return add(last, second);
        case 2: return subtract(last, second);
        case 3: return multiply(last, second);
        case 4: return divide(last, second);
        case 6: return power(last, second);
        default: return last;
    }
}

/* ============================================================ 
                    MAIN PROGRAM LOOP
   ============================================================ */

int main(){

    double num1, num2, result;
    int op_choice, use_last;
    char cont;

    do{

        op_choice = getMenuChoice();

        /* Input depending on operation */
        if((op_choice >= 1 && op_choice <= 4) || op_choice == 6){
            getTwoNUmbers(&num1, &num2);
        }
        else{
            num1 = getOneNUmber();
        }

        /* Prcess Selected Operation */
        switch(op_choice){
            case 1: result = add(num1, num2); break;
            case 2: result = subtract(num1, num2); break;
            case 3: result = multiply(num1, num2); break;
            case 4: result = divide(num1, num2); break;
            case 5: result = squareRoot(num1); break;
            case 6: result = power(num1, num2); break;
            case 7: result = sineDeg(num1); break;
            case 8: result = cosineDeg(num1); break;
            case 9: result = tangentDeg(num1); break;
            case 10: result = logBase10(num1); break;
            case 11: result = naturalLog(num1); break;
        }

        printf("Result: %.4lf\n", result);

        /* Memory Feature */
        printf("Use this result as the FIRST number in the next operation?\n");
        use_last = getYesNoChoice();

        if(use_last == 1){
            double newSecond;
            printf("Enter the second number: ");

            clearInputBuffer();
            while(scanf("%lf", &newSecond) != 1){
                printf("Invalid input! Enter a valid number: ");
                clearInputBuffer();
            }

            result = repeatOperation(op_choice, result, newSecond);
            printf("New Result: %.4lf\n", result);
        }

        /* Continue Prompt*/
        cont = getContinueChoice();
    }

    while (cont == 'y' || cont == 'Y');

    printf("\nGoodbye\n");
    return 0;
}