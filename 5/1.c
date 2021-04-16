#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OK 1
#define FOUND 0x1337
#define NOT_FOUND 0x666

int check(int level, int i, int m, char **tab) {
    for (int j = 1; j <= level; j++)
        if ((i - j >= 0 && tab[level - j][i - j] == 'X') || tab[level - j][i] == 'X' ||
            (i + j < m && tab[level - j][i + j] == 'X'))
            return 0xDEAD;
    return OK;
}

int full(int level, char **tab, int n, int m) {
    if (level == n - 1) {
        for (int i = 0; i < m; ++i) {
            if (tab[level][i] == '?' && check(level, i, m, tab) == OK) {
                tab[level][i] = 'X';
                return FOUND;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        if (tab[level][i] == '?' && check(level, i, m, tab) == OK) {
            tab[level][i] = 'X';
            if (full(level + 1, tab, n, m) == FOUND) return FOUND;
            tab[level][i] = '?';
        }
    }
    return NOT_FOUND;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    char **tab = (char **) calloc(n, sizeof(char *));
    for (int i = 0; i < n; ++i) {
        tab[i] = (char *) calloc(m + 1, sizeof(char));
        scanf("%s", tab[i]);
    }
    char *mask = (char *) malloc(m * sizeof(char));
    memset(mask, 0, m * sizeof(char));
    if (full(0, tab, n, m) == FOUND) {
        printf("YES\n");
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                printf("%c", (tab[i][j] == '?') ? '.' : tab[i][j]);
            }
            printf("\n");
        }
    } else
        printf("NO\n");
    return 0;
}