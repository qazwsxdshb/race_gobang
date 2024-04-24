#include <stdio.h>
#include <string.h>
#define boardsize 21
#define black 1
#define white 2

void Threat_window(int input[11],int ans[11],int me,int you,int score[2][8],int board[11][8]){
    int live,die,tmp[6],xx[6],x[11]={0},co,z;
    for(int i=0;i<6;i++){
        live=0;die=0;co=0;z=0;memset(tmp,-1,6);memset(xx,0,6);
        for(int u=0;u<6;u++){
            if(input[i+u]==0 && die==0){xx[co]=z;tmp[co++]=(i+u);z=0;}
            if(input[i+u]==me && die==0){live++;z++;}
            else if(input[i+u]==you){die+=1;z=0;}//break???
        }
        // live 1
        if(live==1 && die==0){
            for(int i=0;i<co;i++){
                if(tmp[i]!=-1){
                    ans[tmp[i]]+=score[me-1][0]+xx[tmp[i]];
                    board[tmp[i]][0]+=1;
                }
            }
        }
        // die 1
        else if(live==1 && die==1){
            for(int i=0;i<co;i++){
                if(tmp[i]!=-1){
                    ans[tmp[i]]+=score[me-1][1]+xx[tmp[i]];
                    board[tmp[i]][1]+=1;
                }
            }
        }
        // live 2
        else if(live==2 && die==0){
            for(int i=0;i<co;i++){
                if(tmp[i]!=-1){
                    ans[tmp[i]]+=score[me-1][2]+xx[tmp[i]];
                    board[tmp[i]][2]+=1;
                }
            }
        }
        // die 2
        else if(live==2 && die==1){
            for(int i=0;i<co;i++){
                if(tmp[i]!=-1){
                    ans[tmp[i]]+=score[me-1][3]+xx[tmp[i]];
                    board[tmp[i]][3]+=1;
                }
            }
        }

        else if(live>2 && die<2){
            live=0;die=0;co=0;z=0;memset(tmp,-1,6);memset(xx,0,6);
            for(int u=0;u<5;u++){
                if(input[i+u]==0 && die==0){xx[co]=z;tmp[co++]=(i+u);z=0;}
                if(input[i+u]==me && die==0){live++;z++;}
                else if(input[i+u]==you){die+=1;z=0;}//break???
            }

            // live 3
            if(live==3 && die==0){
                for(int i=0;i<co;i++){
                    if(tmp[i]!=-1){
                        ans[tmp[i]]+=score[me-1][4]+xx[tmp[i]];
                        board[tmp[i]][4]+=1;
                    }
                }
            }
            // die 3
            else if(live==3 && die==1){
                for(int i=0;i<co;i++){
                    if(tmp[i]!=-1){
                        ans[tmp[i]]+=score[me-1][5]+xx[tmp[i]];
                        board[tmp[i]][5]+=1;
                    }
                }
            }
            
            // live 4
            else if(live==4 && die==0){
                for(int i=0;i<co;i++){
                    if(tmp[i]!=-1){
                        ans[tmp[i]]+=score[me-1][6]+xx[tmp[i]];
                        board[tmp[i]][6]+=1;
                    }
                }
            }
            // die 4
            else if(live==4 && die==1){
                for(int i=0;i<co;i++){
                    if(tmp[i]!=-1){
                        ans[tmp[i]]+=score[me-1][7]+xx[tmp[i]];
                        board[tmp[i]][7]+=1;
                    }
                }
            }
        }
        
    }
}

void search(int chess[boardsize][boardsize],int board_score[boardsize][boardsize],int x,int y,int selfpoint,int score[2][8],int board_info[boardsize][boardsize][8]){
    int tmp[11]={0},ans[11]={0},board[11][8]={0},enemy=(selfpoint==1?white:black);

    // left_right
    for(int i=0;i<11;i++){
        if(boardsize<=(x+i)){tmp[i]=enemy;}
        else{tmp[i]=chess[x+i][y];}
    }
    Threat_window(tmp,ans,selfpoint,enemy,score,board);
    for(int i=0;i<11;i++){
        if((x+i)<boardsize){
            board_score[x+i][y]+=ans[i];
            for(int u=0;u<8;u++){
                board_info[x+i][y][u]+=board[i][u];
            }
        }
    }

    memset(ans,0,11*sizeof(int));
    // up_down
    for(int i=0;i<11;i++){
        if(boardsize<=(y+i)){tmp[i]=enemy;}
        else{tmp[i]=chess[x][y+i];}
    }
    Threat_window(tmp,ans,selfpoint,enemy,score,board);
    for(int i=0;i<11;i++){
        if((y+i)<boardsize){
            board_score[x][y+i]+=ans[i];
            for(int u=0;u<8;u++){
                board_info[x][y+i][u]+=board[i][u];
            }    
        }
    }

    memset(ans,0,11*sizeof(int));
    // leftup_rightdown
    for(int i=0;i<11;i++){
        if(boardsize<=(x+i) || boardsize<=(y+i)){tmp[i]=enemy;}
        else{tmp[i]=chess[x+i][y+i];}
    }
    Threat_window(tmp,ans,selfpoint,enemy,score,board);
    for(int i=0;i<11;i++){
        if((x+i)<boardsize && (y+i)<boardsize){
            board_score[x+i][y+i]+=ans[i];
            for(int u=0;u<8;u++){
                board_info[x+i][y+i][u]+=board[i][u];
            }
        }
    }
    
    memset(ans,0,11*sizeof(int));
    // leftdown_rightup
    for(int i=0;i<11;i++){
        if(boardsize<=(x+i) || (y-i)<0){tmp[i]=enemy;}
        else{tmp[i]=chess[x+i][y-i];}
    }
    Threat_window(tmp,ans,selfpoint,enemy,score,board);
    for(int i=0;i<11;i++){
        if((x+i)<boardsize && 0<(y-i)){
            board_score[x+i][y-i]+=ans[i];
            for(int u=0;u<8;u++){
                board_info[x+i][y-i][u]+=board[i][u];
            }
        }
    }
}
