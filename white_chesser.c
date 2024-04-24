#include <stdio.h>
#include <string.h>
#include "fun.c"
#include "attack.c"

#define space 0
#define black 1
#define white 2
#define size 21

void cal_score(int chess[size][size],int white_score[size][size],int tt,int white_info[size][size][8]){
    // for(int xx=x-5;xx<x+6;xx++){
        // for(int yy=y-5;yy<y+6;yy++){
    memset(white_score,0,size*size*sizeof(int));
    memset(white_info,0,size*size*sizeof(int)*8);
    for(int xx=0;xx<size;xx++){
        for(int yy=0;yy<size;yy++){
            if(0<=xx && xx<size && 0<=yy && yy<size){
                int score[2][8]={{10,5,300,10,1000,500,10000,10000},{10,5,45,15,2000,70,3000,5000}};
                search(chess,white_score,xx,yy,black,score,white_info);
                int score1[2][8]={{10,5,45,15,2000,70,3000,5000},{10,5,300,10,1000,500,10000,10000}};
                search(chess,white_score,xx,yy,white,score1,white_info);
            }
        }
    }
}

// 偶數自己 奇數
int I_see_future(int chess[size][size],int white_score[size][size],int deep,int white_info[size][size][8]){
    int anss[10][3]={0};

    // limit deep 4bater
    if(deep==4){return 0;}
    
    //white
    else if(deep%2==0){
        cal_score(chess,white_score,white,white_info);//need white
        sort(white_score,anss);

        // 表層判斷
        if(deep==0){
            for(int i=0;i<10;i++){

                printf("x:%d y:%d %d\n",anss[i][0],anss[i][1],anss[i][2]);
                for(int u=0;u<8;u++){
                    printf("%d ",white_info[anss[i][0]][anss[i][1]][u]);
                }printf("\n\n");

                if(white_info[anss[i][0]][anss[i][1]][6]>=1 || white_info[anss[i][0]][anss[i][1]][7]>=1){
                    chess[anss[i][0]][anss[i][1]]=white;
                    printf("x:%d y:%d %d\n",anss[i][0],anss[i][1],anss[i][2]);
                    xxwrite(anss[i][0],anss[i][1],'2');
                    return 0;
                }
            }

        }

        for(int i=9;i>=2;i--){
            chess[anss[i][0]][anss[i][1]]=white;
            anss[i][2]+=I_see_future(chess,white_score,deep+1,white_info);
            chess[anss[i][0]][anss[i][1]]=space;
        }
    }

    //black
    else if(deep%2==1){
        cal_score(chess,white_score,black,white_info);//need black
        sort(white_score,anss);
        for(int i=9;i>=2;i--){
            chess[anss[i][0]][anss[i][1]]=black;
            anss[i][2]+=I_see_future(chess,white_score,deep+1,white_info);
            chess[anss[i][0]][anss[i][1]]=space;
        }
    }

    if(deep==0){
        printf("\n-------------------------------------------\n");
        printf("x:%d y:%d %d\n",anss[max_sort(anss)][0],anss[max_sort(anss)][1],anss[max_sort(anss)][2]);
        for(int i=0;i<10;i++){printf("\nx:%d y:%d %d \n",anss[i][0],anss[i][1],anss[i][2]);}
        chess[anss[max_sort(anss)][0]][anss[max_sort(anss)][1]]=white;

        xxwrite(anss[max_sort(anss)][0],anss[max_sort(anss)][1],'2');

    }

    if(deep%2==0){
        // printf("x:%d y:%d %d\n",anss[max_sort(anss)][0],anss[max_sort(anss)][1],anss[max_sort(anss)][2]);
        // for(int i=0;i<8;i++){
        //     printf("%d ",white_info[anss[max_sort(anss)][0]][anss[max_sort(anss)][1]][i]);
        // }printf("\n\n");
        return anss[max_sort(anss)][2];
    }
    else if(deep%2==1){
        // printf("x:%d y:%d %d\n",anss[min_sort(anss)][0],anss[min_sort(anss)][1],anss[min_sort(anss)][2]);
        // for(int i=0;i<8;i++){
        //     printf("%d ",white_info[anss[min_sort(anss)][0]][anss[min_sort(anss)][1]][i]);
        // }printf("\n\n");
        return anss[min_sort(anss)][2];
    }
}

int main(){
    int chess[size][size]={space},white_score[size][size],white_info[size][size][8],tttt=2;
    char file[11]={0},file1[10000]={0};
    chess[10][10]=black;

    read("inboard.txt", file1);
    if(file1[0]=='W'){
        int ans1[10000]={0},co=0;
        recatchXY(file1,ans1,&co);
        for(int i=0;i<co;i=i+3){
            printf("%d %d\n",ans1[i],ans1[i+1]);
            chess[ans1[i]][ans1[i+1]]=ans1[i+2];
        }
    }
    print_matrix(chess);

    while(1){
        int ans[2]={0};
        read("a.txt", file);
        catchXY(file,ans);
        
        if(tttt==white){
            I_see_future(chess,white_score,0,white_info);
            // clrscr();
            print_matrix(chess);
            tttt=tttt%2+1;
        }

        //white show
        if(file[0]=='W' && tttt==black){
            chess[ans[0]][ans[1]]=tttt;
            tttt=tttt%2+1;
            write("a.txt","R\n0 0");
            xxwrite(ans[0],ans[1],'1');
        }
    }
}