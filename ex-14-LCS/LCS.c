#include <stdio.h>
#include <string.h>
#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int lcs_recursivo(char *X, char *Y, int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (X[i - 1] == Y[j - 1])
        return 1 + lcs_recursivo(X, Y, i - 1, j - 1);
    else
        return max(lcs_recursivo(X, Y, i - 1, j), lcs_recursivo(X, Y, i, j - 1));
}

int memo[MAX][MAX];

int lcs_topdown(char *X, char *Y, int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (memo[i][j] != -1) return memo[i][j];
    if (X[i - 1] == Y[j - 1])
        return memo[i][j] = 1 + lcs_topdown(X, Y, i - 1, j - 1);
    else
        return memo[i][j] = max(lcs_topdown(X, Y, i - 1, j), lcs_topdown(X, Y, i, j - 1));
}

int lcs_bottomup(char *X, char *Y, int m, int n) {
    int dp[MAX][MAX];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    return dp[m][n];
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    int m = strlen(X);
    int n = strlen(Y);

    printf("LCS recursivo: %d\n", lcs_recursivo(X, Y, m, n));

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            memo[i][j] = -1;
    printf("LCS top-down: %d\n", lcs_topdown(X, Y, m, n));

    printf("LCS bottom-up: %d\n", lcs_bottomup(X, Y, m, n));

    return 0;
}