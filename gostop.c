#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

char *card[12][4] = {"1광", "1오", "1피", "1피", "2십", "2오", "2피", "2피", "3광", "3오", "3피", "3피", "4십", "4오", "4피", "4피", "5십", "5오", "5피", "5피", "6십", "6오", "6피", "6피", "7십", "7오", "7피", "7피", "8광", "8십", "8피", "8피", "9쌍피", "9오", "9피", "9피", "10십", "10오", "10피", "10피", "11광", "11쌍피", "11피", "11피", "12광", "12십", "12오", "12쌍피"};
int type[12][4] = { { 0, 2, 3, 3 }, { 1, 2, 3, 3 }, { 0, 2, 3, 3 }, { 1, 2, 3, 3 }, { 1, 2, 3, 3 }, { 1, 2, 3, 3 }, { 1, 2, 3, 3 }, { 0, 1, 3, 3 }, { 4, 2, 3, 3 }, { 1, 2, 3, 3 }, { 0, 4, 3, 3 }, { 0, 1, 2, 4 } };
int Turn;
int tcount;
int scorea, scoreb, scorec;
int go[3];
int shake[3];
int money[3] = { 100000, 100000, 100000 };

typedef struct Info
{
   int Mem;
   struct Info * Next;
}info;
info *plahh, *plagh, *plbhh, *plbgh, *plchh, *plcgh, *boh, *deh, *temh;

void sethead();
void Shuffle();
info* insertNode(info * Target, info * newNode);
void switchNode(info * Target1, info * Target2);
void giveCard();
void giveBlood();
void printBoard();
void printNode(info* plahh);
int setTurn(char T);
int countList(info * head);
int findCard(int a, info * Head);
int shootCard(int a, info * plahh, info * plagh);
int countScore(info * Head);
void sortNode(info * Head);
void swapNode(info * Head);
bool delNode(info * Target);


void main()
{
   sethead();
   info * Now;
   int i, j, x, y, z;
   char command[8];
   int count = 0;
   Shuffle();
   giveCard();
   while (1)
   {
      printBoard();
      printf("명령 "); scanf("%s", command);
      if (command[0]=='e'||strcmp("exit", command) == 0)
      {
         return;
      }
      if (command[0] == '9')
      {
         card[8][0] = "9십";
         type[8][0] = 1;
      }
      if ('1' <= command[0] && command[0] <= '7')
      {
         command[0] -= 48;
         count++;
         if (Turn == 0)
         {
            tcount = 0;
            shootCard(command[0], plahh, plagh);
            tcount = 1;
            shootCard(1, deh, plagh);
            setTurn('N');
            continue;
         }
         if (Turn == 1)
         {
            tcount = 0;
            shootCard(command[0], plbhh, plbgh);
            tcount = 1;
            shootCard(1, deh, plbgh);
            setTurn('N');
            continue;
         }
         if (Turn == 2)
         {
            tcount = 0;
            shootCard(command[0], plchh, plcgh);
            tcount = 1;
            shootCard(1, deh, plcgh);
            setTurn('N');
            continue;
         }
         
      }
   }
      
}
void sortNode(info * Head)
{
   int num = countList(Head);
   int i, j;
   info *Now;

   for (i = 0; i < num-1; i++)
   {
      for (j = 0, Now = Head; j < num - i-1; j++)
      {
         if (Now->Next->Mem > Now->Next->Next->Mem)
         {
            swapNode(Now);
         }
         Now = Now->Next;
      }
   }
} 
void swapNode(info * front)
{
   info * center, *lear, *tmp;
   center = front->Next;
   tmp = center;
   lear = center->Next;
   
   front->Next = center->Next;
   center->Next = lear->Next;
   lear->Next = tmp;
}
int countScore(info * head)
{
   info * Now;
   int score=0, kwang=0, bkwang=0, ddi=0, animal=0, blood=0;
   int chung=0, hong=0, kusa=0, godori=0;
   for (Now = head->Next; Now != NULL; Now = Now->Next)
   {
      if (type[(Now->Mem) / 4][(Now->Mem) % 4] == 0)
      {
         kwang++;
         if (Now->Mem == 44)
            bkwang++;
      }
      if (type[(Now->Mem) / 4][(Now->Mem) % 4] == 1)
         animal++;
      if (type[(Now->Mem) / 4][(Now->Mem) % 4] == 2)
         ddi++;
      if (type[(Now->Mem) / 4][(Now->Mem) % 4] == 3)
         blood++;
      if (type[(Now->Mem) / 4][(Now->Mem) % 4] == 4)
         blood += 2;
      if (Now->Mem == 21 || Now->Mem == 33 || Now->Mem == 37)
         chung++;
      if (Now->Mem == 1 || Now->Mem == 5 || Now->Mem == 9)
         hong++;
      if (Now->Mem == 13 || Now->Mem == 17 || Now->Mem == 25)
         kusa++;
      if (Now->Mem == 4 || Now->Mem == 12 || Now->Mem == 29)
         godori++;
   }
   if (chung == 3)
      score += 3;
   if (hong == 3)
      score += 3;
   if (kusa == 3)
      score += 3;
   if (godori == 3)
      score += 5;
   if (blood > 9)
      score += (blood - 9);
   if (kwang == 3)
   {
      if (bkwang == 1)
         score += 2;
      else
         score += 3;
   }
   if (kwang > 3)
      score += kwang;
   if (ddi > 4)
      score += ddi - 4;
   if (animal > 4)
      score += animal - 4;
   printf("점수)%2d, 광)%d, 십)%d, 오)%d, 피)%2d\n", score, kwang, animal, ddi, blood);
   printf("         청)%d, 홍)%d, 초)%d, 고)%d", chung, hong, kusa, godori);

   return score;
}
int shootCard(int a, info * plahh, info * plagh)
{
   int ccount = 0;
   int x, i;
   info * Now;
   if (a > countList(plahh))
   {
      printf("%d번째 카드를 가지고 있지 않습니다.\n", a);
      setTurn('N'); setTurn('N');
      return;
   }
   else
   {
      ccount = 0;
      x = 0;
      int num[3];
      for (Now = boh->Next; Now != NULL; Now = Now->Next)
      {
         x++;
         if ((Now->Mem / 4) == findCard(a, plahh) / 4)
         {
            ccount++;
            num[ccount - 1] = x;
         }
      }
      if (countList(temh) == 2)
      {
         if ((temh->Next->Mem) / 4 == findCard(a, plahh) / 4)
         {
            switchNode(temh, boh);
            switchNode(temh, boh);
            for (Now = plahh; a != 1; a--)
               Now = Now->Next;
            switchNode(Now, boh);
            return;
         }
         else
         {
            switchNode(temh, plagh);
            switchNode(temh, plagh);
         }
      }
      if (ccount == 0)
      {
         for (Now = plahh; a != 1; a--)
            Now = Now->Next;
         switchNode(Now, boh);
      }
      if (ccount == 1)
      {
         if (tcount == 0)
         {
            for (Now = boh; num[0] != 1; num[0]--)
               Now = Now->Next;
            switchNode(Now, temh);
            for (Now = plahh; a != 1; a--)
               Now = Now->Next;
            switchNode(Now, temh);
         }
         if (tcount == 1)
         {
            for (Now = boh; num[0] != 1; num[0]--)
               Now = Now->Next;
            switchNode(Now, plagh);
            for (Now = plahh; a != 1; a--)
               Now = Now->Next;
            switchNode(Now, plagh);
         }
      }
      if (ccount == 2)
      {
         while (1)
         {
            printf("먹을 카드를 선택하시오(입력 1 or 2):");
            scanf("%d", &i);
            if (i == 1 || i == 2)
               break;
         }
         for (Now = boh; num[i - 1] != 1; num[i - 1]--)
            Now = Now->Next;
         switchNode(Now, plagh);
         for (Now = plahh; a != 1; a--)
            Now = Now->Next;
         switchNode(Now, plagh);
      }
      if (ccount == 3)
      {
         for (Now = boh; num[0] != 1; num[0]--)
            Now = Now->Next;
         switchNode(Now, plagh);
         num[1]--;
         for (Now = boh; num[1] != 1; num[1]--)
            Now = Now->Next;
         switchNode(Now, plagh);
         num[2] -= 2;
         for (Now = boh; num[2] != 1; num[2]--)
            Now = Now->Next;
         switchNode(Now, plagh);
         for (Now = plahh; a != 1; a--)
            Now = Now->Next;
         switchNode(Now, plagh);
      }
   }
}
int findCard(int a, info * Head)
{
   info * Now = Head;
   int i;
   for (i = 0; i < a; i++)
   {
      Now = Now->Next;
   }
   return Now->Mem;
}
void sethead()
{
   plahh = (info*)malloc(sizeof(info));
   plahh->Next = NULL;
   plagh = (info*)malloc(sizeof(info));
   plagh->Next = NULL;
   plbhh = (info*)malloc(sizeof(info));
   plbhh->Next = NULL;
   plbgh = (info*)malloc(sizeof(info));
   plbgh->Next = NULL;
   plchh = (info*)malloc(sizeof(info));
   plchh->Next = NULL;
   plcgh = (info*)malloc(sizeof(info));
   plcgh->Next = NULL;
   boh = (info*)malloc(sizeof(info));
   boh->Next = NULL;
   deh = (info*)malloc(sizeof(info));
   deh->Next = NULL;
   temh = (info*)malloc(sizeof(info));
   temh->Next = NULL;
}
void Shuffle()
{
   int num[48] = { 0 };
   srand(time(NULL));
   int i, j, a, count = 1;
   for (i = 1; i < 48; i++)
   {
      for (j = i - 1; j >= 0; j--)
      {
         if (j == i - 1)
            num[i] = rand() % 48;
         if (num[i] == num[j])
            j = i;
      }
   }
   info * Now;
   info Board;
   Now = deh;
   for (i = 0; i < 48; i++)
   {
      Board.Mem = num[i];
      Now = insertNode(Now, &Board);
   }
}
void giveCard()
{
   int i,j;
   int num[3][12] = { 0 };
   for (i = 0; i < 7; i++)
   {
      num[0][(deh->Next->Mem) / 4]++;
      switchNode(deh, plahh);
      num[1][(deh->Next->Mem) / 4]++;
      switchNode(deh, plbhh);
      num[2][(deh->Next->Mem) / 4]++;
      switchNode(deh, plchh);
   }
   for (i = 0; i < 6; i++)
      switchNode(deh, boh);
   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 12; j++)
      {
         if (num[i][j] == 3)
         {
            printf("player '%c'가 흔들었습니다.\n", i + 65);
            shake[i]++;
         }
         if (num[i][j] == 4)
            printf("총통");
      }
   }

   
}
int countList(info * Head)
{
   int a = 0;
   info * Now;
   for (Now = Head; Now->Next != NULL; Now = Now->Next)
      a += 1;
   return a;
}
void printNode(info* plahh)
{
   int i;
   info * Now;
   for (i = 0; i < countList(plahh); i++)printf("       ");
   for (i = 0; i < countList(plahh); i++)printf("\b\b\b\b\b\b\b");
   for (Now = plahh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]);
   putchar('\n');
}
void printBoard()
{
   int ah, ag, bh, bg, ch, cg, d, bo;
   int i;
   info * Now;
   sortNode(plahh);
   sortNode(plagh);
   sortNode(plbhh);
   sortNode(plbgh);
   sortNode(plchh);
   sortNode(plcgh);
   sortNode(boh);
   printf("%c의 턴\n", Turn + 65);
   printf("A        : 패) "); for (i = 0; i < countList(plahh); i++)printf("       "); for (i = 0; i < countList(plahh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plahh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]); putchar('\n');
   printf("딴 화투) "); for (i = 0; i < countList(plagh); i++)printf("       "); for (i = 0; i < countList(plagh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plagh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]);
   putchar('\n'); scorea=countScore(plagh); putchar('\n');  putchar('\n');
   printf("B        : 패) "); for (i = 0; i < countList(plbhh); i++)printf("       "); for (i = 0; i < countList(plbhh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plbhh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]); putchar('\n');
   printf("딴 화투) "); for (i = 0; i < countList(plbgh); i++)printf("       "); for (i = 0; i < countList(plbgh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plbgh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]);
   putchar('\n'); scoreb=countScore(plbgh); putchar('\n');  putchar('\n');
   printf("C        : 패) "); for (i = 0; i < countList(plchh); i++)printf("       "); for (i = 0; i < countList(plchh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plchh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]); putchar('\n');
   printf("딴 화투) "); for (i = 0; i < countList(plcgh); i++)printf("       "); for (i = 0; i < countList(plcgh); i++)printf("\b\b\b\b\b\b\b"); for (Now = plcgh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]);   
   putchar('\n'); scorec=countScore(plcgh); putchar('\n'); putchar('\n');
   printf("깔린 패) "); for (i = 0; i < countList(boh); i++)printf("       "); for (i = 0; i < countList(boh); i++)printf("\b\b\b\b\b\b\b"); for (Now = boh->Next; Now != NULL; Now = Now->Next)printf("%s ", card[Now->Mem / 4][Now->Mem % 4]); putchar('\n');
   putchar('\n'); putchar('\n');
   if (deh->Next != NULL)
   {
      printf("다음 패) "); printf("%s\n", card[(deh->Next->Mem) / 4][(deh->Next->Mem) % 4]);
   }
}
int setTurn(char T)
{
   if (T == 'A')
      Turn = 0;
   if (T == 'B')
      Turn = 1;
   if (T == 'C')
      Turn = 2;
   if (T == 'N')
   {
      Turn += 1;
      Turn %= 3;
   }
   return Turn;
}
info* insertNode(info * Target, info * newNode)
{
   info * New;

   New = (info*)malloc(sizeof(info));
   *New = *newNode;

   New->Next = Target->Next;
   Target->Next = New;
   return New;
}
void switchNode(info * Target1, info * Target2) 
{
   info * Now;
   Now = Target1->Next;
   Target1->Next = Now->Next;
   Now->Next = Target2->Next;
   Target2->Next = Now;
}
bool delNode(info * Target)
{
   info * Del;

   Del = Target->Next;
   if (Del = NULL)
   {
      return false;
   }
   Target->Next = Del->Next;
   free(Del);
   return true;
}
