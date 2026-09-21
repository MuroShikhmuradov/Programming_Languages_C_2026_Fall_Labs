#include <stdio.h>

int is_prime(int n);

int main(){
    int n;

    printf("Please enter n: ");
    scanf("%d", &n);

    if(n < 2){
        printf("!!! ERROR !!!");

        return 1;

    }

    printf("Primes to %d: ", n);
    for (int i = 2; i <= n; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

}

int is_prime(int n){
    if (n < 2){
        return 0;
    }

    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return 0;
        }
    }

    return 1;
}