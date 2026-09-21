#include <stdio.h>

int sum_to_n(int n);

int main() {
    int n;

    printf("Please enter n: ");
    scanf("%d", &n);

    if(n < 1){
        printf("!!! ERROR !!!");
        return 1;
    }

    int result = sum_to_n(n);
    printf("Result: %d\n", result);

    return 0;

}

int sum_to_n(int n){
    int sum = 0;

    for(int i = 1; i <= n; i++){
        sum += i;
    }

    return sum;
}