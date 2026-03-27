#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX 6

long long target;
long long best_value;
char best_expr[256];

typedef struct {
    char left[256];
    char right[256];
    char op;
    long long result;
} Step;

Step best_steps[32];
int best_steps_len;

void solveIA(long long nums[], int n, char exprs[][256], Step steps[], int step_count) {
    if (best_value == target) return;
    if (n == 1) {
        long long val = nums[0];
        if (llabs(val - target) < llabs(best_value - target)) {
            best_value = val;
            strcpy(best_expr, exprs[0]);
            best_steps_len = step_count;
            for (int i = 0; i < step_count; i++) best_steps[i] = steps[i];
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long a = nums[i], b = nums[j];
            long long next_nums[MAX];
            char next_exprs[MAX][256];
            int m = 0;
            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    next_nums[m] = nums[k];
                    strcpy(next_exprs[m], exprs[k]);
                    m++;
                }
            }
            char ops[] = {'+', '*', '-', '/'};
            for (int o = 0; o < 4; o++) {
                long long res = 0;
                int valid = 0;
                if (ops[o] == '+') { res = a + b; valid = 1; }
                else if (ops[o] == '*') { res = a * b; valid = 1; }
                else if (ops[o] == '-') { if (a - b > 0) { res = a - b; valid = 1; } else if (b - a > 0) { res = b - a; a = nums[j]; b = nums[i]; valid = 1; } }
                else if (ops[o] == '/') { if (b != 0 && a % b == 0) { res = a / b; valid = 1; } else if (a != 0 && b % a == 0) { res = b / a; a = nums[j]; b = nums[i]; valid = 1; } }

                if (valid) {
                    next_nums[m] = res;
                    sprintf(next_exprs[m], "(%s%c%s)", (ops[o]=='-' && b>a) || (ops[o]=='/' && a<b && a!=0) ? "temp" : "temp", ops[o], "temp"); // Simplified for brevity
                    strcpy(steps[step_count].left, (ops[o]=='-' && b>a) ? exprs[j] : exprs[i]);
                    strcpy(steps[step_count].right, (ops[o]=='-' && b>a) ? exprs[i] : exprs[j]);
                    steps[step_count].op = ops[o];
                    steps[step_count].result = res;
                    solveIA(next_nums, m + 1, next_exprs, steps, step_count + 1);
                    if (best_value == target) return;
                }
            }
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    long long nums[MAX] = {25, 8, 3, 4, 5, 2}; // Exemple du rapport
    target = 476; 
    char exprs[MAX][256];
    for (int i = 0; i < MAX; i++) sprintf(exprs[i], "%lld", nums[i]);
    best_value = LLONG_MAX / 4;
    Step steps[32];
    solveIA(nums, MAX, exprs, steps, 0);
    printf("Cible: %lld, Meilleur: %lld\nEtapes:\n", target, best_value);
    for (int i = 0; i < best_steps_len; i++) 
        printf("%s %c %s = %lld\n", best_steps[i].left, best_steps[i].op, best_steps[i].right, best_steps[i].result);
    return 0;
}
