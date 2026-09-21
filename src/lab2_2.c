#include <stdio.h>

long long factorial(int n);

int main(){
    int n;

    printf("Please enter n: ");
    scanf("%d", &n);

    if(n < 0 ){
        printf("!!! ERROR !!!");
        return 1;
    }

    long long result = factorial(n);
    printf("Result: %lld\n", result);
    
    return 0;

}

long long factorial(int n){
    long long f = 1;

    for(int i = 1; i <= n; i++){
        f *= i;
    }

    return f;

}