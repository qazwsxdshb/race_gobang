#include "chessData.h"
#include <stdio.h>
#include <string.h>
#include "fun.c"
#include "attack.c"

#define space 0
#define black 1
#define white 2
#define boardsize 21

void cal_score(int board[boardsize][boardsize],int black_score[boardsize][boardsize],int tt,int black_info[boardsize][boardsize][8]){
    memset(black_score,0,boardsize*boardsize*sizeof(int));
    memset(black_info,0,boardsize*boardsize*sizeof(int)*8);
    for(int xx=0;xx<boardsize;xx++){
        for(int yy=0;yy<boardsize;yy++){
            if(0<=xx && xx<boardsize && 0<=yy && yy<boardsize && board[xx][yy]==space){
                int score[2][8]={{10,5,300,10,1000,500,10000,10000},{10,5,45,15,750,70,3000,5000}};
                search(board,black_score,xx,yy,black,score,black_info);
                int score1[2][8]={{10,5,45,15,750,70,3000,5000},{10,5,300,10,1000,500,10000,10000}};
                search(board,black_score,xx,yy,white,score1,black_info);
            }
        }
    }
}

// 偶數自己 奇數
int I_see_future(int board[boardsize][boardsize],int black_score[boardsize][boardsize],int deep,int black_info[boardsize][boardsize][8],int *ansx,int *ansy){
    int anss[10][3]={0};

    // limit deep 4bater
    if(deep==4){return 0;}
    
    //white
    else if(deep%2==0){
        cal_score(board,black_score,black,black_info);sort(black_score,anss);
        // 表層判斷
        if(deep==0){
            for(int i=0;i<10;i++){
                if(black_info[anss[i][0]][anss[i][1]][6]>=2 || black_info[anss[i][0]][anss[i][1]][7]>=2){
                    // printf("x:%d y:%d %d\n",anss[i][0],anss[i][1],anss[i][2]);
                    *ansx=anss[i][0]+1;*ansy=anss[i][1]+1;return 0;
                }
            }
        }

        for(int i=9;i>=2;i--){
            board[anss[i][0]][anss[i][1]]=black;
            anss[i][2]+=I_see_future(board,black_score,deep+1,black_info,ansx,ansy);
            board[anss[i][0]][anss[i][1]]=space;
        }
    }

    else if(deep%2==1){
        cal_score(board,black_score,white,black_info);
        sort(black_score,anss);
        for(int i=9;i>=2;i--){
            board[anss[i][0]][anss[i][1]]=white;
            anss[i][2]+=I_see_future(board,black_score,deep+1,black_info,ansx,ansy);
            board[anss[i][0]][anss[i][1]]=space;
        }
    }

    if(deep==0){
        // printf("\n-------------------------------------------\n");
        // printf("x:%d y:%d %d\n",anss[max_sort(anss)][0],anss[max_sort(anss)][1],anss[max_sort(anss)][2]);
        // for(int i=0;i<10;i++){printf("\nx:%d y:%d %d \n",anss[i][0],anss[i][1],anss[i][2]);}
        *ansx=anss[max_sort(anss)][0]+1;*ansy=anss[max_sort(anss)][1]+1;
    }

    if(deep%2==0){return anss[max_sort(anss)][2];}
    else if(deep%2==1){return anss[min_sort(anss)][2];}
}


// 偶數自己 奇數
int white_see_future(int board[boardsize][boardsize],int white_score[boardsize][boardsize],int deep,int white_info[boardsize][boardsize][8],int *ansx,int *ansy){
    int anss[10][3]={0};

    // limit deep 4bater
    if(deep==4){return 0;}
    
    //white
    else if(deep%2==0){
        cal_score(board,white_score,white,white_info);sort(white_score,anss);
        // 表層判斷
        if(deep==0){
            for(int i=0;i<10;i++){
                if(white_info[anss[i][0]][anss[i][1]][6]>=2 || white_info[anss[i][0]][anss[i][1]][7]>=2){
                    // printf("x:%d y:%d %d\n",anss[i][0],anss[i][1],anss[i][2]);
                    *ansx=anss[i][0]+1;*ansy=anss[i][1]+1;return 0;
                }
            }
        }

        for(int i=9;i>=2;i--){
            board[anss[i][0]][anss[i][1]]=white;
            anss[i][2]+=I_see_future(board,white_score,deep+1,white_info,ansx,ansy);
            board[anss[i][0]][anss[i][1]]=space;
        }
    }

    //black
    else if(deep%2==1){
        cal_score(board,white_score,black,white_info);//need black
        sort(white_score,anss);
        for(int i=9;i>=2;i--){
            board[anss[i][0]][anss[i][1]]=black;
            anss[i][2]+=I_see_future(board,white_score,deep+1,white_info,ansx,ansy);
            board[anss[i][0]][anss[i][1]]=space;
        }
    }

    if(deep==0){
        // printf("\n-------------------------------------------\n");
        // printf("x:%d y:%d %d\n",anss[max_sort(anss)][0],anss[max_sort(anss)][1],anss[max_sort(anss)][2]);
        // for(int i=0;i<10;i++){printf("\nx:%d y:%d %d \n",anss[i][0],anss[i][1],anss[i][2]);}
        *ansx=anss[max_sort(anss)][0]+1;*ansy=anss[max_sort(anss)][1]+1;
    }

    if(deep%2==0){return anss[max_sort(anss)][2];}
    else if(deep%2==1){return anss[min_sort(anss)][2];}
}



void writeChessBoard(Chess* chess, int player, int* x, int* y) {

    int board[boardsize][boardsize]={space},black_score[boardsize][boardsize],black_info[boardsize][boardsize][8];

    for(int i=0;i<chess->size;i++){
        board[(chess->cord[i].x)-1][(chess->cord[i].y)-1]=(chess->cord[i].player)+1;
    }

    // print_matrix(board);
    if(chess->size==0){*x=11;*y=11;}
    else if(chess->size%2==0){I_see_future(board,black_score,0,black_info,x,y);}
    else{white_see_future(board,black_score,0,black_info,x,y);}

    while(1){if(setXY(chess,*x,*y,player)==1) {return;}}
}