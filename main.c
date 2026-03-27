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
    if (best_value == target) return; [cite: 2236, 2994]
    if (n == 1) { [cite: 2239, 2998]
        long long val = nums[0];
        long long current_diff = llabs(val - target);
        long long best_diff = llabs(best_value - target);
        if (current_diff < best_diff) {
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
            char exprA[256], exprB[256];
            strcpy(exprA, exprs[i]);
            strcpy(exprB, exprs[j]);

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

            // Test des 4 opérations (+, *, -, /) [cite: 2259, 3031, 3043, 3061, 3087]
            long long results[6] = {a+b, a*b, a-b, b-a, (b!=0 && a%b==0)?a/b:0, (a!=0 && b%a==0)?b/a:0};
            char ops[6] = {'+', '*', '-', '-', '/', '/'};
            char *l_expr[6] = {exprA, exprA, exprA, exprB, exprA, exprB};
            char *r_expr[6] = {exprB, exprB, exprB, exprA, exprB, exprA};

            for(int o=0; o<6; o++) {
                if (o == 2 && a-b <= 0) continue; 
                if (o == 3 && b-a <= 0) continue;
                if (o >= 4 && results[o] == 0) continue;

                next_nums[m] = results[o];
                sprintf(next_exprs[m], "(%s%c%s)", l_expr[o], ops[o], r_expr[o]);
                strcpy(steps[step_count].left, l_expr[o]);
                strcpy(steps[step_count].right, r_expr[o]);
                steps[step_count].op = ops[o];
                steps[step_count].result = results[o];

                solveIA(next_nums, m + 1, next_exprs, steps, step_count + 1);
                if (best_value == target) return;
            }
        }
    }
}

int main() {
    srand((unsigned)time(NULL)); [cite: 2021, 3342]
    long long original_nums[MAX];
    // Génération selon les règles du jeu [cite: 2056, 2890]
    int grands[] = {25, 50, 75, 100};
    int nb_grand = rand() % 2 + 1;
    for (int i = 0; i < nb_grand; i++) original_nums[i] = grands[rand() % 4];
    for (int i = nb_grand; i < MAX; i++) original_nums[i] = (rand() % 10) + 1;
    target = (rand() % 900) + 100;

    char exprs[MAX][256];
    for (int i = 0; i < MAX; i++) sprintf(exprs[i], "%lld", original_nums[i]);
    best_value = LLONG_MAX / 4;
    Step steps[32];

    printf("Cible : %lld\nNombres : ", target);
    for(int i=0; i<MAX; i++) printf("%lld ", original_nums[i]);
    
    solveIA(original_nums, MAX, exprs, steps, 0);

    printf("\n\nSolution IA : %s = %lld\n", best_expr, best_value);
    for (int i = 0; i < best_steps_len; i++)
        printf("Etape %d : %s %c %s = %lld\n", i+1, best_steps[i].left, best_steps[i].op, best_steps[i].right, best_steps[i].result);
    return 0;
}
