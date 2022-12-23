
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

char *shift(char arr1[10][10]){

    char tarr[10][10];
    char temp[10];
    int shift = 4;


    //copying from the first array
    for(int i = 0; i <10; i++){
        for (int j = 0; j < strlen(arr1[i]);j++){
            tarr[i][j] = arr1[i][j];
        }
    }

    //shifting
    for (int i = shift; i < 10; i++){

        for (int j = 0; j < strlen(arr1[i]);j++){
            temp[j] = arr1[i][j];
        }
        memset(tarr[shift],'\0',10);
        int pos = i+1;
        for (int k = 0; k<strlen(temp);k++){
            tarr[pos][k] = temp[k];
        }
        memset(temp, '\0',10);
    }

    //copying to the first array
    for(int i = 0; i <10; i++){
        memset(arr1[i],'\0',10);
        for (int j = 0; j < strlen(tarr[i]);j++){
            arr1[i][j] = tarr[i][j];
        }
    }


    return *arr1;
}

int main(){
    char arr[10][10];
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 4; j++){
            arr[i][j] = (char)65+i;
        }
    }
    for (int i = 0; i < 10; i++){
        printf("%d: %s\n",i,arr[i]);
    }
    char arr1[10][10] = shift(arr);

    //getting the array value
    for (int i = 0; i < 10; i++){
        printf("%d: %s\n",i,arr1[i]);
    }
}   