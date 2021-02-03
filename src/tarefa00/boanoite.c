#include <stdio.h>

int main() {
    char nome[30];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", nome);
        printf("Boa noite, %s.\n", nome);
    }
}