#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define space 0
#define black 1
#define white 2
#define boardsize 21

// void print_matrix(int chess[boardsize][boardsize]){
//     for(int y=0;y<boardsize;y++){
//         for(int x=0;x<boardsize;x++){
//             if(chess[x][y]!=0){
//                 printf("%d  ",chess[x][y]);
//             }
//             else{
//                 printf("*  ");
//             }
//         }
//         printf("  %d \n",y+1);
//     }
//     printf("1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21\n\n");
// }


void sort(int board[boardsize][boardsize],int ans[10][3]){
    for(int y=0;y<boardsize;y++){
        for(int x=0;x<boardsize;x++){
            if(ans[0][2]<board[x][y]){
                int i=1;
                for(i;i<10;i++){
                    if(board[x][y]<ans[i][2]){
                        ans[i-1][2]=board[x][y];
                        ans[i-1][0]=x;ans[i-1][1]=y;break;
                    }
                    else{
                        ans[i-1][2]=ans[i][2];
                        ans[i-1][0]=ans[i][0];ans[i-1][1]=ans[i][1];
                    }
                }
                if(i==10){
                    ans[i-1][2]=board[x][y];
                    ans[i-1][0]=x;ans[i-1][1]=y;
                }
            }
        }
    }
}

int max_sort(int ans[10][3]){
    int index=0,value=0;
    for(int i=0;i<10;i++){
        if(ans[i][2]>value){index=i;value=ans[i][2];}
    }
    return index;
}

int min_sort(int ans[10][3]){
    int index=0,value=ans[0][3];
    for(int i=1;i<10;i++){
        if(ans[i][2]<value){index=i;value=ans[i][2];}
    }
    return index;
}
