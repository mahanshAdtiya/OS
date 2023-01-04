#include <stdio.h>
#include <sys/syscall.h>
// #include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

void check_equal(int arr1[][5], int arr2[][5]){
    printf("Original Matrix:\n");
    for(int i = 0; i < 5; i ++){
        for(int j = 0 ; j <5; j++){
            printf("%f ",arr1[i][j]);
        }
        printf("\n");
    }
    printf("\nCopied Matrix:\n");
    for(int i = 0; i < 5; i ++){
        for(int j = 0 ; j <5; j++){
            printf("%f ",arr2[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 5; i ++){
        for(int j = 0 ; j <5; j++){
            if(arr1[i][j] != arr2[i][j]){
                printf("Error !.\nMatrices are not same.\n");
                return;
            }
        }
    }
    printf("Matrices are smae !!.\n");
}

int main(){
    int original[][5] = {{1, 2, 3, 4, 5},{2, 3, 4, 5, 1},{3, 4, 5, 2, 1},{4, 5, 1, 2, 3},{5, 1, 2, 3, 4}};
    int copied[5][5];

    long sys_call_status = syscall(452, original, copied,5,5);

    if (sys_call_status != EFAULT){
        check_equal(original, copied);
    }

    return 0;
}