#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// 駒の定義 
#define EMPTY 0 
#define LION_0 1 
#define ELEPHANT_0 2 
#define GIRAFFE_0 3 
#define CHICK_0 4
#define NIWATORI_0 5

#define LION_1 11 
#define ELEPHANT_1 12 
#define GIRAFFE_1 13 
#define CHICK_1 14
#define NIWATORI_1 15

// プレイヤーの定義 
#define PLAYER_1 0
#define PLAYER_2 1 



//駒の識別&表示
void identification(int board[4][3], int have[2][6], int i, int j,int key){
  int box;
  if(key == 0){
    box = board[i][j];
  }
  else if(key == 1){
    box = have[i][j];
  }
  
  switch (box) { 
  case EMPTY: 
    printf(". "); 
    break; 
    
  case LION_0:
    printf("\x1b[34m");
    printf("L "); 
    break;
  case LION_1:
    printf("\x1b[31m");
    printf("l "); 
    break; 	
    
  case ELEPHANT_0:
    printf("\x1b[34m");
    printf("E "); 
    break;	
  case ELEPHANT_1:
    printf("\x1b[31m");
    printf("e "); 
    break;	
    
  case GIRAFFE_0:
    printf("\x1b[34m");
    printf("G "); 
    break; 	
  case GIRAFFE_1:
    printf("\x1b[31m");
    printf("g "); 
    break; 
    
  case CHICK_0:
    printf("\x1b[34m");
    printf("C "); 
    break;
  case CHICK_1:
    printf("\x1b[31m");
    printf("c "); 
    break;
      
  case NIWATORI_0:
    printf("\x1b[34m");
    printf("N "); 
    break;
  case NIWATORI_1:
    printf("\x1b[31m");
    printf("n "); 
    break;
  }
  printf("\x1b[0m");
}

// ボードの表示
void board_display(int board[4][3],int have[2][6]){
  int key = 0;
  printf("[PLAYER_1]\n");
  printf("  1 2 3 x\n"); 
  
  for (int i = 0; i < 4; i++) { 
    printf("%d ", i+1); 
    for (int j = 0; j < 3; j++) {
    
      identification(board,have,i,j,key);
      
    } 
    printf("\n"); 
  } 
  printf("y\n");
  printf("[PLAYER_2]\n\n");
}

//持ち駒の表示
void have_display(int board[4][3], int have[2][6], int turn){
  int key = 1;
  printf("piece you have:[");
  for(int j=0;j<6;j++){
    identification(board,have,turn,j,key);
  }
  printf("]\n");
}


//　駒の移動判定&移動
int move(int turn, int board[4][3], int have[2][6], int befy, int befx, int afy, int afx){
  int check = 0;
  
  //boardの範囲外ではないか?
  if(afy < 0 || afy  > 3){
    check++;
    }else if(afx < 0 || afx > 2){
    check++;
    }
  if(check != 0){   
    printf("▲ boardの範囲外です\n");
    return 0;
  }
  
  //移動先に自分の駒がないか?
  if(turn == 0){
    if(board[afy][afx] > 0 && board[afy][afx] < 5){
      check++;
    }
  }else if(turn == 1){
    if(board[afy][afx] > 10 && board[afy][afx] <15){
      check++;
    }
  }
  if(check != 0){   
    printf("▲ 移動先に自分の駒があります\n");
    return 0;
  }
  
  //x座標とy座標のそれぞれの差を求める
  int dy, dx;
  if(afy > befy){
    dy = afy - befy;
  }else{
    dy = befy - afy;
  }
  if(afx > befx){
    dx = afx - befx;
  }else{
    dx = befx - afx;
  }
  
  
  //各駒が移動できる座標を指定しているか?
  switch (board[befy][befx]) { 
  case LION_0:
    if(dy >= 2 || dx >= 2){
      check++;
    }else if(dy + dx >= 3){
      check++;
    }  
    break;
  case LION_1:
    if(dy >= 2 || dx >= 2){
      check++;     
    }else if(dy + dx >= 3){
      check++;      
    } 
    break; 	
    
    
  case ELEPHANT_0:
    if(dy==1 && dx==1){
    }else{
      check++;    
    }
    break;	
  case ELEPHANT_1:
    if(dy==1 && dx==1){
    }else{
      check++;    
    } 
    break;	
    
    
  case GIRAFFE_0:
    if(dy==1 && dx==0){
    }
    else if(dy==0 && dx==1){
    }else{
      check++; 
    }
    break; 	
  case GIRAFFE_1:
    if(dy==1 && dx==0){
    }
    else if(dy==0 && dx==1){
    }else{
      check++;      
    } 
    break; 
    
    
  case CHICK_0:
    if(turn==0){
      if(dy+dx == 1 && afy > befy){
      }else{
	check++;	
      }
    }else if(turn==1){
      if(dy+dx == 1 && befy > afy){
      }else{
	check++;	
      }
    }
    break;
  case CHICK_1:
    if(turn==0){
      if(dy+dx == 1 && afy > befy){
      }else{
	check++;	
      }
    }else if(turn==1){
      if(dy+dx == 1 && befy > afy){
      }else{
	check++;
      }
    }
    break;
    
  case NIWATORI_0:
      if(dy >= 2 || dx >= 2){
	check++;	
      }else if(dy + dx >= 3){
	check++;      
      }else if(dy == befy - 1 && dx == 1){
	check++;      
      }
      break;
  case NIWATORI_1:
    if(dy >= 2 || dx >= 2){
      check++;     
    }else if(dy + dx >= 3){
      check++;    
    }else if(dy == befy + 1 && dx == 1){
      check++;    
    }
    break;   
  }
  if(check != 0){
    printf("▲ その位置には移動できません\n");
   
    return 0;
  }
  
  //相手の駒の判定
  if(board[afy][afx] != EMPTY){
    for(int z=0;z<6;z++){
      if(have[turn][z]==EMPTY){
	have[turn][z] = board[afy][afx];

	//もしニワトリだったらヒヨコに戻す
	if(have[turn][z] == NIWATORI_0){
	  have[turn][z] = CHICK_0;
	}else if(have[turn][z] == NIWATORI_1){
	  have[turn][z] = CHICK_1;
	}
	z=6;
      }
    }
  }
  //駒の移動
  board[afy][afx] = board[befy][befx];
  board[befy][befx] = EMPTY;

  //にわとりに変身!
  if(board[afy][afx] == CHICK_0 && afy == 3){
    board[afy][afx]=NIWATORI_0;
  }
  else if(board[afy][afx] == CHICK_1 && afy == 0){
    board[afy][afx]=NIWATORI_1;
  }
  
  return 1;
}


int put(int turn, int board[4][3], int have[2][6], int num, int afy, int afx){
    int check=0;
    
    //指定された座標に駒はないか
    if(board[afy][afx] != EMPTY){
      check++;
      printf("▲ すでに駒が置かれています\n");
      return 0;
    }
    
    //それぞれの処理
    switch (have[turn][num]) { 
    case ELEPHANT_0:
      board[afy][afx] = ELEPHANT_1;
      break;	
    case ELEPHANT_1:
      board[afy][afx] = ELEPHANT_0;
      break;	
      
      
    case GIRAFFE_0:
      board[afy][afx] = GIRAFFE_1;
      break; 	
    case GIRAFFE_1:
      board[afy][afx] = GIRAFFE_0;
      break; 
      
      
    case CHICK_0:
      if(turn == 0 && afy == 3){
	check++;
      }
      else if(turn == 1 && afy == 0){
	check++;
      }else{
	board[afy][afx] = CHICK_1;
      }
      break;
    case CHICK_1:
      if(turn == 0 && afy == 3){
	check++;
      }
      else if(turn == 1 && afy == 0){
	check++;
      }else{
	board[afy][afx] = CHICK_0;
      }
      break;
    }
    if(check != 0){
      printf("▲ そこには置けません\n");
      return 0;
    }
    for(int x=num;x<5;x++){
      have[turn][x]=have[turn][x+1];
    }
    have[turn][5]=EMPTY;

    return 1;
  }
  
  
  int main()
  {
  // ボードの初期化 
  int board[4][3] = { 
		     {GIRAFFE_0, LION_0, ELEPHANT_0}, 
		     {EMPTY, CHICK_0, EMPTY}, 
		     {EMPTY, CHICK_1, EMPTY}, 
		     {ELEPHANT_1, LION_1, GIRAFFE_1},
  }; 
  
  srand((unsigned)time(NULL));
  int turn = rand() % 2;


  int have[2][6];

  //　持ち駒の初期化
  for(int y=0;y<2;y++){
    for(int x=0;x<6;x++){
      have[y][x] = EMPTY;
    }
  }


  int mode;
  int befy, befx, afy, afx;
  int num;
  int che;
  int check;
  int judgement;
  
  
 
  
  while(turn < 2){
    printf("L,l = lion.  G,g = giraffe.  E.e = elephant.  C,c = chick. N,n = niwatori\n");
    printf("L,G,E,C,N = PLAYER_1's piece. l,g,e,c,n = PLAYER_2's piece.\n\n");

    board_display(board,have);

    check = 0;
    judgement = 0;
    
    if(turn==0){
      printf("{ PLAYER_1's turn }\n");
    }else{
      printf("{ PLAYER_2's turn }\n");
    }
    
    have_display(board,have,turn);
    
    while(check==0){
      che = 0;
      printf("\n選択してください(1:自分の駒を動かす　2:持ち駒を出す):");
      scanf("%d", &mode);

      if(mode==1){
	printf("動かす駒の座標を入力してください(before_x,before_y):");
	scanf("%d %d", &befx, &befy);
	printf("\n");
	befx--;
	befy--;
	//指定した座標に自分の駒があるか?
	if(turn == 0){
	  if(board[befy][befx] > 0 && board[befy][befx] < 6){
	  }else{
	    che++;
	    printf("▲ 指定した座標に自分の駒がありません\n");
	  }
	}else if(turn == 1){
	  if(board[befy][befx] > 10 && board[befy][befx] <16){
	  }else{
	    che++;
	    printf("▲ 指定した座標に自分の駒がありません\n");
	  }
	}

	if(che == 0){
	  printf("[ ");
	  identification(board,have,befy,befx,0);
	  printf("]");
	  
	  printf("どこに動かしますか?(after_x,after_y):");
	  scanf("%d %d", &afx, &afy);
	  printf("\n");
	  
	  check = move(turn,board,have,befy,befx,afy-1,afx-1);
	}
      }
      else if(mode==2){
	num = 0;
	if(have[turn][1] != EMPTY){
	  printf("出す駒を入力してください(左から何番目?):");
	  scanf("%d",&num);
	  num--;
	  printf("\n");
	}
	if(have[turn][num] != EMPTY){
	  printf("駒を置く座標を入力してください(after_x,after_y):");
	  scanf("%d %d", &afx, &afy);
	  printf("\n");
	  
	  check = put(turn,board,have,num,afy-1,afx-1);
	}else{
	  printf("▲ 駒がありません\n");
	}
      

      }else{
	printf("1,2のどちらかを入力してください\n");
      }
    }
    
    //board上にライオンが存在しているか
    for(int y=0;y<4;y++){
      for(int x=0;x<3;x++){
	if(board[y][x] == LION_0 || board[y][x] == LION_1){
	  judgement++;
	}
      }
    }

    //相手の陣地にライオンをトライできたか
    for(int x=0;x<3;x++){
      if(board[0][x] == LION_1 || board[3][x] == LION_0){
	judgement = 1;
      }
    }
	

    if(judgement == 1){
      board_display(board,have);
      printf("PLAYER_%d Win!\n",turn+1);
      turn = 2;
    }
    else if(turn == PLAYER_1){
      turn = PLAYER_2;
    }
    else if(turn == PLAYER_2){
      turn = PLAYER_1;
    }
    
  }
  return 0;  
}
