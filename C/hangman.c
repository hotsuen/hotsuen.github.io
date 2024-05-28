#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termio.h>


void display();
char change(char);
char getChar();

int main()
{
  //wordsを開き、行数を数える
  FILE * fp = NULL;
  char buf[50];
  fp = fopen("words","r");
  int line = 0;
  while(fgets(buf,sizeof(buf),fp) != NULL){
    line++;
  }
  
  char answer[50];
  char answer_verification[50] = "programming";
  int length;  
  char word[50]; 
  char used[50];
  int master = 0;
  char reply; 
  int count;
  int num;
  int check;
  int error;
  int judge;
  
  int random;
  int b;
  
  
  while(master == 0){
    //0~最大行数のランダムな整数を生成
    srand((unsigned)time(NULL));
    random = rand() % line;
    
    //ファイルポインタを先頭に戻す
    rewind(fp);
    
    //ランダムに1行の文字列を抽出する
    b = 0;
    while(fgets(buf,sizeof(buf),fp) != NULL){
      if(random == b){
	strcpy(answer,buf);
	length = strlen(answer)-1;
	
	//printf("%s\n",answer);
      } 
      b++;
    }
    //検証
    //strcpy(answer,answer_verification);
    //length = strlen(answer);
    
    //printf("%d\n",length);
    
    //答えへの進捗を表す文字列の初期化
    for(int x=0; x < 50; x++){
      if(x < length){
	word[x] = '-';
      }else{
	word[x] = ' ';
      }
    }
    
    //使われた文字列の初期化
    for(int y=0; y < 50; y++){
      used[y] = ' ';
    }
    
    //間違いカウントの初期化
    count = 7;
    
    
    //1ゲームの処理
    num = 0;
    while(count > 0){
      error = 0;
      check = 0;
      judge = 0;
      
      //データの表示。英子文字の入力を求める
      do{
	display(word,used,count);
	used[num] = getChar();
	if('a' <= used[num] && used[num] <= 'z'){
	  printf("%c\n\n",used[num]);
	}else{
	  used[num] = ' ';
	  printf("\n\n");
	}
      }while(used[num] < 'a' ||  used[num] > 'z');
      
      //すでに使われたかチェック
      for(int y=0; y < num; y++){
	if(used[y] == used[num]){
	  used[num] = ' ';
	  error++;
	}
      }
      
      
      if(error == 0){
	//入力された文字が答えに含まれているかチェック
	for(int x=0;x < length; x++){
	  if(answer[x] == used[num] || answer[x] == change(used[num])){
	    word[x] = answer[x];
	    check++;
	  }
	}
	
	//文字が一つも当てはまらなかった場合
	if(check == 0){
	  count--;
	}
	num++;
	
      }
      //すでに入力した文字を入れた時
      else{
	printf("すでに使われてます\n\n");
	used[num] = ' ';
      }
      
      //正解したか確認
      for(int y=0; y < length; y++){
	if(word[y] == '-'){
	  judge++;
	}
      }
      
      //ゲーム判定
      if(judge == 0){
	count = 0;
	printf("答え:%s\n",answer);
	printf("ゲームクリア！\n");
      }
      else if(count == 0){
	printf("答え:%s\n",answer);
	printf("ゲームオーバー\n");
      }
      
    }
    
    //ゲーム継続
    do{
      printf("ゲームを続けますか?(y/n):");
      reply = getChar();
      printf("\n\n");
    }while(reply != 'y' && reply != 'n');
    
    if(reply != 'y'){
      master++;
      fclose(fp);
    }
  } 
  return 0;
}


//表示を担う関数
void display(char word[50], char used[50], int count)
{
  int i = 0;
  
  printf("単語:");
  while(word[i] != ' '){
    printf("%c",word[i]);
    i++;
  }
  printf("\n使われた文字:");
  i = 0;
  while(used[i] != ' '){
    printf("%c",used[i]);
    i++;
  }
  printf("\n残り回数:%d\n",count);
  printf("文字を入力して下さい:");
}


//小文字を大文字に変換
char change(char letter)
{
  char after;
  if('a' <= letter && letter <= 'z'){
    letter -= 32;
  }
  else if('A' <= letter && letter <= 'Z'){
    letter += 32;
  }
  return letter;
}

char getChar(void)
{
  struct termio old_term, new_term;
  
  char	c;
  
  /* 現在の設定を得る */
  ioctl(0, TCGETA, &old_term);
  
  /* 設定のコピーをつくる */
  new_term = old_term;
  
  /* 入力文字のエコーを抑止する場合 */
  new_term.c_lflag &= ~(ICANON | ECHO);
  
  /* エコーは止めない場合 */
  //new_term.c_lflag &= ~(ICANON);
  
  /* 新しい設定を反映する */
  ioctl(0, TCSETAW, &new_term);
  
  /* 1 文字入力 */
  c = getchar();
  
  /* 古い設定に戻す */
  ioctl(0, TCSETAW, &old_term);
  
  return (c);
}	
