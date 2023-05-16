#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*game 2 ���w�q*/
#define BUF_SIZE 5
// �ϥιL���P�]�� -1
#define USED -1 
//�P��
#define N 52  
// 4�Ӫ�� 
char flower[4] = {'C','D','H','S'}; 
// �Ʀr
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


// �D�禡
int main()
{   
    int wallet;
    printf("�а���a�h�ֿ��i�J���C��?(����10000���H�W)\n");
    scanf("%d",&wallet); 
    while(wallet<10000){
		printf("\n�а���a�h�ֿ��i�J���C��?(����10000���H�W)\n");
		scanf("%d",&wallet);
	} 
    /*game 1*/
	printf("\n\n~~~~~GOING TO GAME 1 ~~~~~\n\n");
	
	printf("�w��Ө�q�q���]��\n");
	printf("\n�C���W�h����:\n");
	printf("-------------------------------\n");
	printf("�o�̦��Ӥ��t100����10000�������]\n");
	printf("���a�q�����]�������B(100������)\n");
	printf("�Y���a�q�������B > ���]������ڪ��B�A�|���<�A�p�@�I>�������a\n");
	printf("�Y���a�q�������B < ���]������ڪ��B�A�|���<�A�j�@�I>�������a\n");
	printf("�Y���a�q������<=3���A�i�HĹ�o���]�����Ҧ���\n");
	printf("�Y���a�q������<=5���A�i�HĹ�o���]���������B x 70%%����\n");
	printf("�Y���a�q�����Ʀh��6���A���a�ݤ�I���]�����Ҧ����B x 70%%����\n");
	printf("-------------------------------\n");
	
	unsigned seed;
	int count=0;//���a�q������ 
	int guess;//���a�q�������B
	int amount;//���]������ڪ��B
	
    printf("���ߵo�]~\n"); 
	printf("�q�q���]�U�����h�ֿ�?((100������)�̧C100���̰�10000��)\n");
	scanf("%d",&guess);
	seed=(unsigned)time(NULL);
	srand(seed);
	amount=(1+rand()%100)*100;
	while(guess!=amount&&wallet>=0){
		while(guess!=amount&&10000>=guess&&guess>0){
			if(10000>guess&&guess>amount){
				printf("�A�p�@�I\n");
				count++;
			}
			if(guess<amount&&guess>0){
				printf("�Ӥp�F��!\n");
				count++;
			}
			printf("�q�q���]�U�����h�ֿ�?((100������)�̧C100���̰�10000��)\n");
			scanf("%d",&guess);
		}//end while//
		if(10000<guess||0>guess){
			printf("wrong enter\n");
			printf("���s��J\n");
			scanf("%d",&guess);
		} 
	}//end while//
	if(guess==amount){
		printf("�q��F!\n");
		printf("�`�@�i��: %d ��\n",count);
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
	printf("�z�ثe�Ҿ֦������: %d",wallet);
	
	/*�C������B�����ɫh�ݥ[��*/ 
	if(wallet<1000){	
		printf("�l�B����1000�L�k�ѥ[�U�ӹC�� \n�Х[�ȫ�A�~��C��\n");			
		
        int add, addvalue;
		printf("�O�_�[��?(�Y���[�ȹC���Y����)\n");
		printf("(��J: 1-->�[�� 2-->�����C��)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("�[�h��?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("�z�ثe�Ҿ֦������:%d��\n",wallet);
		}
		else{
			system("pause");	
		}
	}
	
	
	
	/*game 2*/ 
    printf("\n\n~~~~~GOING TO GAME 2 ~~~~~\n\n"); 
    printf("�w��Ө켳�J��j�p\n");		
	
		start:
	printf("\n�C���W�h����:\n");
	printf("-------------------------------\n");
	printf("�@��26���A�C�����a�D�����X�P�դ����Ǭ��ĴX���P�A�q���]�H���q�P�դ�����@�i�P\n");
	printf("�u�P��ܩ�P���G�ä�j�p\n");
	printf("�C�������ɡA���a�C�h�ӹL�q���@���A�i�HĹ�o�U�`���B x 30%%����\n");
	printf("�C�������ɡA���a�C�鵹�F�q���@���A�|�Q�����U�`���B x 20%%����\n");
	printf("�U�`���B�Цܤ֬��@�d��\n");
	printf("-------------------------------\n");
	printf("�z�ثe�Ҿ֦������:%d��\n",wallet);
	printf("�ФU�`(�@�d���H�W):");
	int bet;
	scanf("%d",&bet);
	
	while(bet<1000||wallet-bet<0){
		printf("\n�Э��s�U�`(�@�d���H�W):");
		scanf("%d",&bet);
	}
	
    int i, round=1, poker[N];
    int card_remain=N; // �ѤU�P��
    int draw_pos=0; // ����ĴX�i�P
    int draw_number=0; // ��X���I��
    int win=0,lose=0; // �Կn
    int pc_pos, pc_number;
    for(i=0; i!=N; ++i) poker[i] = i;
    shuffle(poker, N);    
    
    while(card_remain!=0){
       DRAW_LINE();
       printf("Round %d:\n",round);   
       printf("\n[%2d cards remain]\n", card_remain); // ��ܳѾl�d�q
       
       // ���ܱ�����i�P
       do{       
          printf("please input nth card to draw(1~%2d): ", card_remain);
          scanf("%d", &draw_pos);
          if(draw_pos>card_remain || draw_pos<=0) 
		  puts("��J���~!! �Э��s��J");
         }while(draw_pos>card_remain || draw_pos<=0);
       
       
       // ���a��X���I��
       draw_number = cal_n_pos(poker, N, draw_pos);
       printf("You draw:"), display_card(draw_number);
       card_remain--;
       

       // �q����X���I��
       pc_pos = RANDOM(card_remain);      
       pc_number = cal_n_pos(poker, N, pc_pos);
       printf("\nPC draw:"), display_card(pc_number);
       card_remain--, putchar('\n');
       if(compare_single(draw_number, pc_number)) {
          win++;
          puts("���^�X���a���!!");
       }
       else {
          lose++;
          puts("���^�X�q�����!!");
       }
       round++;
    }
    DRAW_LINE();
    printf("�AĹ�F %d �^�X\n", win);
    printf("�A��F %d �^�X\n", lose);
    
	if(win>lose){
	   int profit=bet*0.3*(win-lose);
       printf("���ߧAĹ�F%d��!!\n",profit);
       wallet=wallet+bet*0.3*(win-lose);
      
       }
    else if(win<lose){
       printf("���~�A���A�F!!...\n");
       wallet=wallet-bet*0.2*(lose-win);
       }
    else {
       printf("�����A���Ȥ]����\n");
       }

    printf("�z�ثe�Ҿ֦������:%d��\n",wallet);
    
	/*�߰ݬO�_�A��*/
	if(wallet>=1000){
		int choice;
		printf("�O�_�A���@��? 1-->�A�Ӥ@�� 2-->�i�J�U�@�ӹC��\n");
		scanf("%d",&choice);
		if(choice==1){
			goto start;
		}
		else{
			goto end;
		}
	}
	/*�C������B�����ɫh�ݥ[��*/ 
	else {
		if(wallet<0){
			printf("\n�S���l�B�F��A�ثe�@�@���%d��\n",wallet*-1);
			printf("�Х[�ȫ�A�i�J�C��\n");
		}
		else{
			printf("\n�l�B����1000�A�L�k�ѥ[�U�ӹC�� \n�Х[�ȫ�A�~��C��\n");			
		} 
		
        int add, addvalue;
		printf("�O�_�[��?(�Y���[�ȹC���Y����)\n");
		printf("(��J: 1-->�[�� 2-->�����C��)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("�[�h��?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("�z�ثe�Ҿ֦������:%d��\n",wallet);
			/*�߰ݥ[�ȫ�O�_�A��*/
			if(wallet>=1000){
				int choice2;
				printf("�O�_�A���@��?�άO�i�J�U�@�ӹC�� 1-->�A�Ӥ@�� 2-->�i�J�U�@�ӹC��\n");
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
	printf("�w��Ө�Ѫ�����C����\n");
	printf("�C���W�h����:\n");
	printf("-------------------------------\n");
	printf("���@��X�{7 --> �����ܨ⭿\n");
	printf("������X�{7 --> �����ܤQ��\n");
	printf("�T�泣�X�{7 --> �����ܤ@�ʭ�\n");
	printf("���@���@�d��\n");
	printf("-------------------------------\n");
	printf("�Ч���@�d��: \n");
	scanf("%d",&money);
	while(money!=1000){
		printf("�ݧ�J1000����\n");
		printf("�Ч���@�d��: \n");
		scanf("%d",&money);
	}
	printf("�z�ثe�Ҿ֦������: %d��\n",wallet-1000);
	 start3:
	srand(time(NULL));
	a=rand()%10;
	b=rand()%10;
	c=rand()%10;
	printf("������....\n");
	printf("-----------------------\n");
	printf("%d%d%d\n",a,b,c);
	printf("----------------------\n");
	if(a==7 && b==7 && c==7)
	{
		printf("���ߤ��F3��7!!\n");
		printf("��o: %d��\n",money*100);
		wallet=wallet+100*money;	
	}	
	else if((a==7 && b==7 && c!=7)||(a==7 && b!=7 && c==7)||(a!=7 && b==7 && c==7))
	{
		printf("������2��7!!\n");
		printf("��o: %d��\n",money*10);
		wallet=wallet+10*money;
	}
	else if((a==7 && b!=7 && c!=7)||(a!=7 && b==7 && c!=7)||(a!=7 && b!=7 && c==7))
	{
		printf("������o�@��7!!\n");
		printf("��o: %d��\n",money*2);
		wallet=wallet+2*money;
	}
	else
	{ 
		printf("�S������~�A���A�F!!\n");
		wallet=wallet-1000;
			
	}
	printf("�z�ثe�Ҿ֦������: %d��\n",wallet);
	
	/*�߰ݬO�_�A��*/
	if(wallet>=1000){
		int choice3;
		printf("�O�_�A���@��? 1-->�A�Ӥ@�� 2-->���n�N���A������B\n");
		scanf("%d",&choice3);
		if(choice3==1){
			goto start3;
		}
		else{
			goto end3;
		}
	}
	/*���B�����ɫh�ݥ[��*/ 
	else {
		if(wallet<0){
			printf("�S���l�B�F��A�ثe�@�@���%d��\n",wallet*-1);
			printf("�Х[�ȫ�A�i�J�C��\n");
		}
		else{
			printf("�l�B����1000�A�L�k�ѥ[�U�ӹC�� \n�Х[�ȫ�A�~��C��\n");			
		} 
		
        int add, addvalue;
		printf("�O�_�[��?(�Y���[�ȹC���Y����)\n");
		printf("(��J: 1-->�[�� 2-->�����C��)\n");
		scanf("%d",&add);
		if(add==1){    
			printf("�[�h��?\n");
			scanf("%d",&addvalue);
			wallet=wallet+addvalue;	
			printf("�z�ثe�Ҿ֦������:%d��\n",wallet);
			/*�[�ȫ�߰ݬO�_�A��*/
			if(wallet>=1000){
				int choice3;
				printf("�O�_�A���@��? 1-->�A�Ӥ@�� 2-->���n�N���A������B\n");
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
		printf("\n\n�P�±z�������C�� :)\n");
		printf("\n����%d�����z\n",wallet);
		printf("�w��A�׻Y�{ :)\n",wallet);
    
    system("pause");
    return 0;
}




//�H�U��game 2�ϥΨ禡�w�q
 
// SWAP
void SWAP(int *a,int *b){ 
	int t; t=*a; *a=*b; *b=t; 
}
// shuffle
void shuffle(int *array, int Size){
	
	int i, pos;
	
    for(i=0; i!=Size; ++i){
       // ���X�� pos �i�P
       srand(time(NULL));
	   pos = rand()%Size; 
       //pos = RANDOM(0, N-1);
       // �N�� i �i�P�P�� pos �i�P�洫
       SWAP(&array[i], &array[pos]); 
    }
}
// �q���H����X��k�i�P
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
// �����i�j�p, a>b �Ǧ^ 1, a<b �Ǧ^ 0
int compare_single(int a, int b)
{
    a+= (a<4)*N,b+= (b<4)*N;
    return a>b;
}
// �p��{���P�Ƥ��� n �i�P���ƭ�
int cal_n_pos(int *array, int Size, int n)
{
    int i=0,counter=0; 
    int number=0; // �I��
    // ��X�Ĺs�i�S�ϥιL���P
    while(array[i]==USED) 
		 i++;

    // ���o�� n �i�S�ϥιL���P
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
