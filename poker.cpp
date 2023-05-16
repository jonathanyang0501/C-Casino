#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*game 2 的定義*/
#define BUF_SIZE 5
// 使用過之牌設成 -1
#define USED -1 
//牌數
#define N 52  
// 4個花色 
char flower[4] = {'C','D','H','S'}; 
// 數字
const char number[13][BUF_SIZE] = {
    " A", " 2", " 3", " 4", " 5", " 6",
    " 7", " 8", " 9", "10", " J", " Q", " K"};

//game 2 Functions
void DRAW_LINE(){
	puts("-------------------------");
}
void SWAP(int *a,int *b); 
void shuffle(int *array, int Size);
int RANDOM(int k);
void display(int* array, int Size);
void display_card(int card);
int compare_single(int a, int b);
int cal_n_pos(int *array, int Size, int n);


// 主函式
int main()
{   
    int wallet;
    printf("請問攜帶多少錢進入本遊戲?(必須10000元以上)\n");
    scanf("%d",&wallet); 
    while(wallet<10000){
		printf("\n請問攜帶多少錢進入本遊戲?(必須10000元以上)\n");
		scanf("%d",&wallet);
	} 
    /*game 1*/
	printf("\n\n~~~~~GOING TO GAME 1 ~~~~~\n\n");
	
	printf("歡迎來到猜猜紅包錢\n");
	printf("\n遊戲規則說明:\n");
	printf("-------------------------------\n");
	printf("這裡有個內含100元至10000元的紅包\n");
	printf("玩家猜測紅包內的金額(100的倍數)\n");
	printf("若玩家猜測的金額 > 紅包內的實際金額，會顯示<再小一點>提醒玩家\n");
	printf("若玩家猜測的金額 < 紅包內的實際金額，會顯示<再大一點>提醒玩家\n");
	printf("若玩家猜測次數<=3次，可以贏得紅包內的所有錢\n");
	printf("若玩家猜測次數<=5次，可以贏得紅包內的錢金額 x 70%%的錢\n");
	printf("若玩家猜測次數多於6次，玩家需支付紅包內的所有金額 x 70%%的錢\n");
	printf("-------------------------------\n");
	
	unsigned seed;
	int count=0;//玩家猜測次數 
	int guess;//玩家猜測的金額
	int amount;//紅包內的實際金額
	
    printf("恭喜發財~\n"); 
	printf("猜猜紅包袋內有多少錢?((100的倍數)最低100元最高10000元)\n");
	scanf("%d",&guess);
	seed=(unsigned)time(NULL);
	srand(seed);
	amount=(1+rand()%100)*100;
	while(guess!=amount&&wallet>=0){
		while(guess!=amount&&10000>=guess&&guess>0){
			if(10000>guess&&guess>amount){
				printf("再小一點\n");
				count++;
			}
			if(guess<amount&&guess>0){
				printf("太小了喔!\n");
				count++;
			}
			printf("猜猜紅包袋內有多少錢?((100的倍數)最低100元最高10000元)\n");
			scanf("%d",&guess);
		}//end while//
		if(10000<guess||0>guess){
			printf("wrong enter\n");
			printf("重新輸入\n");
			scanf("%d",&guess);
		} 
	}//end while//
	if(guess==amount){
		printf("猜對了!\n");
		printf("總共進行: %d 次\n",count);
		if(count<=3){
		  wallet=wallet+amount;
		}
		else if(count<=5){
		  wallet=wallet+amount*0.7;
		}
		else{
		  wallet=wallet-amount;	
		}
	}
	printf("您目前所擁有的賭金: %d",wallet);
	
	/*遊玩後金額不足時則需加值*/ 
	if(wallet<1000){	
		printf("餘額不足1000無法參加下個遊戲 \n請加值後再繼續遊戲\n");			
		
        int add, addvalue;
		printf("是否加值?(若不加值遊戲即結束)\n");
		printf("(輸入: 1-->加值 2-->結束遊戲)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("加多少?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("您目前所擁有的賭金:%d元\n",wallet);
		}
		else{
			system("pause");	
		}
	}
	
	
	
	/*game 2*/ 
    printf("\n\n~~~~~GOING TO GAME 2 ~~~~~\n\n"); 
    printf("歡迎來到撲克比大小\n");		
	
		start:
	printf("\n遊戲規則說明:\n");
	printf("-------------------------------\n");
	printf("共有26局，每局玩家挑選欲抽出牌組中順序為第幾的牌，電腦也隨機從牌組中抽取一張牌\n");
	printf("攤牌顯示抽牌結果並比大小\n");
	printf("遊戲結束時，玩家每多勝過電腦一局，可以贏得下注金額 x 30%%的錢\n");
	printf("遊戲結束時，玩家每輸給了電腦一局，會被收取下注金額 x 20%%的錢\n");
	printf("下注金額請至少為一千元\n");
	printf("-------------------------------\n");
	printf("您目前所擁有的賭金:%d元\n",wallet);
	printf("請下注(一千元以上):");
	int bet;
	scanf("%d",&bet);
	
	while(bet<1000||wallet-bet<0){
		printf("\n請重新下注(一千元以上):");
		scanf("%d",&bet);
	}
	
    int i, round=1, poker[N];
    int card_remain=N; // 剩下牌數
    int draw_pos=0; // 欲抽第幾張牌
    int draw_number=0; // 抽出之點數
    int win=0,lose=0; // 戰積
    int pc_pos, pc_number;
    for(i=0; i!=N; ++i) poker[i] = i;
    shuffle(poker, N);    
    
    while(card_remain!=0){
       DRAW_LINE();
       printf("Round %d:\n",round);   
       printf("\n[%2d cards remain]\n", card_remain); // 顯示剩餘卡量
       
       // 提示欲抽哪張牌
       do{       
          printf("please input nth card to draw(1~%2d): ", card_remain);
          scanf("%d", &draw_pos);
          if(draw_pos>card_remain || draw_pos<=0) 
		  puts("輸入錯誤!! 請重新輸入");
         }while(draw_pos>card_remain || draw_pos<=0);
       
       
       // 玩家抽出之點數
       draw_number = cal_n_pos(poker, N, draw_pos);
       printf("You draw:"), display_card(draw_number);
       card_remain--;
       

       // 電腦抽出之點數
       pc_pos = RANDOM(card_remain);      
       pc_number = cal_n_pos(poker, N, pc_pos);
       printf("\nPC draw:"), display_card(pc_number);
       card_remain--, putchar('\n');
       if(compare_single(draw_number, pc_number)) {
          win++;
          puts("此回合玩家獲勝!!");
       }
       else {
          lose++;
          puts("此回合電腦獲勝!!");
       }
       round++;
    }
    DRAW_LINE();
    printf("你贏了 %d 回合\n", win);
    printf("你輸了 %d 回合\n", lose);
    
	if(win>lose){
	   int profit=bet*0.3*(win-lose);
       printf("恭喜你贏了%d元!!\n",profit);
       wallet=wallet+bet*0.3*(win-lose);
      
       }
    else if(win<lose){
       printf("遺憾~再接再厲!!...\n");
       wallet=wallet-bet*0.2*(lose-win);
       }
    else {
       printf("平局，不賺也不賠\n");
       }

    printf("您目前所擁有的賭金:%d元\n",wallet);
    
	/*詢問是否再玩*/
	if(wallet>=1000){
		int choice;
		printf("是否再玩一把? 1-->再來一把 2-->進入下一個遊戲\n");
		scanf("%d",&choice);
		if(choice==1){
			goto start;
		}
		else{
			goto end;
		}
	}
	/*遊玩後金額不足時則需加值*/ 
	else {
		if(wallet<0){
			printf("\n沒有餘額了喔，目前一共欠款%d元\n",wallet*-1);
			printf("請加值後再進入遊戲\n");
		}
		else{
			printf("\n餘額不足1000，無法參加下個遊戲 \n請加值後再繼續遊戲\n");			
		} 
		
        int add, addvalue;
		printf("是否加值?(若不加值遊戲即結束)\n");
		printf("(輸入: 1-->加值 2-->結束遊戲)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("加多少?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("您目前所擁有的賭金:%d元\n",wallet);
			/*詢問加值後是否再玩*/
			if(wallet>=1000){
				int choice2;
				printf("是否再玩一把?或是進入下一個遊戲 1-->再來一把 2-->進入下一個遊戲\n");
				scanf("%d",&choice2);
				if(choice2==1){
					goto start;
				}
				else{
					goto end;
				}
			}
		}
		else{
			system("pause");	
		}	
	} 
  		
	          end: 
	printf("\n\n~~~~~GOING TO GAME 3 ~~~~~\n\n");
	int a,b,c;
	int money;
	printf("歡迎來到老虎虛擬遊戲機\n");
	printf("遊戲規則說明:\n");
	printf("-------------------------------\n");
	printf("任一欄出現7 --> 獎金變兩倍\n");
	printf("任兩欄出現7 --> 獎金變十倍\n");
	printf("三欄都出現7 --> 獎金變一百倍\n");
	printf("玩一次一千元\n");
	printf("-------------------------------\n");
	printf("請投幣一千元: \n");
	scanf("%d",&money);
	while(money!=1000){
		printf("需投入1000元喔\n");
		printf("請投幣一千元: \n");
		scanf("%d",&money);
	}
	printf("您目前所擁有的賭金: %d元\n",wallet-1000);
	 start3:
	srand(time(NULL));
	a=rand()%10;
	b=rand()%10;
	c=rand()%10;
	printf("轉轉轉....\n");
	printf("-----------------------\n");
	printf("%d%d%d\n",a,b,c);
	printf("----------------------\n");
	if(a==7 && b==7 && c==7)
	{
		printf("恭喜中了3個7!!\n");
		printf("獲得: %d元\n",money*100);
		wallet=wallet+100*money;	
	}	
	else if((a==7 && b==7 && c!=7)||(a==7 && b!=7 && c==7)||(a!=7 && b==7 && c==7))
	{
		printf("恭喜獲2個7!!\n");
		printf("獲得: %d元\n",money*10);
		wallet=wallet+10*money;
	}
	else if((a==7 && b!=7 && c!=7)||(a!=7 && b==7 && c!=7)||(a!=7 && b!=7 && c==7))
	{
		printf("恭喜獲得一個7!!\n");
		printf("獲得: %d元\n",money*2);
		wallet=wallet+2*money;
	}
	else
	{ 
		printf("沒有中獎~再接再厲!!\n");
		wallet=wallet-1000;
			
	}
	printf("您目前所擁有的賭金: %d元\n",wallet);
	
	/*詢問是否再玩*/
	if(wallet>=1000){
		int choice3;
		printf("是否再玩一把? 1-->再來一把 2-->見好就收，結算金額\n");
		scanf("%d",&choice3);
		if(choice3==1){
			goto start3;
		}
		else{
			goto end3;
		}
	}
	/*金額不足時則需加值*/ 
	else {
		if(wallet<0){
			printf("沒有餘額了喔，目前一共欠款%d元\n",wallet*-1);
			printf("請加值後再進入遊戲\n");
		}
		else{
			printf("餘額不足1000，無法參加下個遊戲 \n請加值後再繼續遊戲\n");			
		} 
		
        int add, addvalue;
		printf("是否加值?(若不加值遊戲即結束)\n");
		printf("(輸入: 1-->加值 2-->結束遊戲)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("加多少?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("您目前所擁有的賭金:%d元\n",wallet);
			/*加值後詢問是否再玩*/
			if(wallet>=1000){
				int choice3;
				printf("是否再玩一把? 1-->再來一把 2-->見好就收，結算金額\n");
				scanf("%d",&choice3);
				if(choice3==1){
					goto start3;
				}
				else{
					goto end3;
				}
			}	
		}
		else{
			system("pause");	
		}	
	}
	end3:
		printf("\n\n感謝您此次的遊玩 :)\n");
		printf("\n返還%d元給您\n",wallet);
		printf("歡迎再度蒞臨 :)\n",wallet);
    
    system("pause");
    return 0;
}




//以下為game 2使用函式定義
 
// SWAP
void SWAP(int *a,int *b){ 
	int t; t=*a; *a=*b; *b=t; 
}
// shuffle
void shuffle(int *array, int Size){
	
	int i, pos;
	
    for(i=0; i!=Size; ++i){
       // 取出第 pos 張牌
       srand(time(NULL));
	   pos = rand()%Size; 
       //pos = RANDOM(0, N-1);
       // 將第 i 張牌與第 pos 張牌交換
       SWAP(&array[i], &array[pos]); 
    }
}
// 電腦隨機抽出第k張牌
int RANDOM(int k){
	int pos;
	srand(time(NULL));
	pos = rand()%k;
	return pos;
}
// display_card
void display_card(int card){
   switch(flower[card%4]){
   	case 'C':
   		printf("Club");
   		break;
   	case 'D':
   		printf("Diamond");
   		break;
	case 'H':
		printf("Heart");
   		break;
	case 'S':
		printf("Spade");
   		break;
   }
   printf("%s", number[ card >> 2 ]); // faster
}
// 比較單張大小, a>b 傳回 1, a<b 傳回 0
int compare_single(int a, int b)
{
    a+= (a<4)*N,b+= (b<4)*N;
    return a>b;
}
// 計算現有牌數之第 n 張牌之數值
int cal_n_pos(int *array, int Size, int n)
{
    int i=0,counter=0; 
    int number=0; // 點數
    // 找出第零張沒使用過的牌
    while(array[i]==USED) 
		 i++;

    // 取得第 n 張沒使用過的牌
    for(; i!=Size && counter!=n; i++){
       if(array[i]!=USED) 
	   	 counter++;
       if(counter==n) 
	     break;
    }
    number = array[i];
    array[i]=USED;
    return number;
}
