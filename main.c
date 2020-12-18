#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <time.h>

#include <Windows.h>

#include <conio.h>

 

#define UP 72

#define DOWN 80

#define LEFT 75

#define RIGHT 77

#define SPACEBSR 32

#define _CRT_SECURE_NO_WARNINGS

 

 

int player[15];   //플레이어 카드는 1차원 배열

int computer[15]; //컴퓨터 카드는 1차원 배열

int center;  //공개되어 있는 카드

int order; //순서정하기

int dummy[51] = { 0, }; //오픈되어있는 카드 아래에 있는 카드 배열 (40이상이면 바꾼다)

int card[4][13] =

{

   {10,11,12,13,14,15,16,17,18,19,20,21,22},  //♠

   {30,31,32,33,34,35,36,37,38,39,40,41,42},  //◆

   {50,51,52,53,54,55,56,57,58,59,60,61,62},  //♥

   {70,71,72,73,74,75,76,77,78,79,80,81,82}   //♣

}; //카드 종류 배열

 

 

 

 

void centerf(); //공개된 카드 지정해주는 함수

void plcardf(); //플레이어 카드 지정 함수

void cocardf(); //컴퓨터 카드 지정 함수

void correct(); //카드순서 올바르게 지정하는 함수

void comturn(); //컴퓨터 턴 함수

void plturn(); //플레이어 턴 함수

void dummyf(); // 더미 40이상이면 게임진행을 위해 섞어주는 함수

void prcard(); //card 출력

void keyf(); //방향키 함수

void gotoxy();

 

 

 

 

//////////////메인함수

int main()

{

	system("mode con cols=80  lines=40");

	srand((unsigned int)time(NULL)); //랜덤 모듈

 

 

	order = 1;

	centerf();

	plcardf();

	cocardf();

 

	if (order == 0) //컴퓨터 먼저 시작

	{

		while (1)

		{

			prcard();

			comturn();

			Sleep(1000);

			system("cls");

			prcard();

			dummyf();

			if (computer[0] == 0 || computer[14] != 0) 

			{

				break;

			}

		    

			plturn();

			system("cls");

			prcard();

			dummyf();

			if (player[0] == 0 || player[14] != 0)

			{

				break;

			}

		}

	}

	else if(order ==1)

	{

		while (1)

		{

			prcard();

			plturn();

			system("cls");

			prcard();

			dummyf();

			if (player[0] == 0 || player[14] != 0)

			{

				break;

			}

		

			comturn();

			Sleep(1000);

			system("cls");

			prcard();

			dummyf();

			if (computer[0] == 0 || computer[14] != 0)

			{

				break;

			}

		}

	}

	return 0;

}

 

 

 

 

 

 

/////////////사용자 정의 함수들

 

void centerf() //공개된 카드 지정해주는 함수

{

	srand((unsigned int)time(NULL)); //랜덤 모듈

	int sum1 = (rand() % 4); //카드 배열의 세로부분

	int sum2 = (rand() % 13); //카드 배열의 가로부분

	center = card[sum1][sum2];

	card[sum1][sum2] += 1000;

}

 

 

void plcardf() //플레이어 카드 지정

{

	srand((unsigned int)time(NULL)); //랜덤 모듈

	for (int i = 0; i < 7; i++)  //player1의 카드 7개 정해주기 ,정해준 숫자는 card배열에서 1000을 더해서 차별화할 수 있도록 한다.

	{

		int sum1 = (rand() % 4); //카드 배열의 세로부분

		int sum2 = (rand() % 13); //카드 배열의 가로부분

		if (card[sum1][sum2] / 1000 == 1)

		{

			i--;

			continue;

		}

		player[i] = card[sum1][sum2];

		card[sum1][sum2] = card[sum1][sum2] + 1000;

	}

}

 

 

void cocardf() //컴퓨터 카드 지정

{

	srand((unsigned int)time(NULL)); //랜덤 모듈

	for (int i = 0; i < 7; i++)    //player2의 카드 7개 정해주기 ,정해준 숫자는 card배열에서 1000을 더해서 차별화할 수 있도록 한다.

	{

		int sum1 = (rand() % 4); //카드 배열의 세로부분

		int sum2 = (rand() % 13); //카드 배열의 가로부분

		if (card[sum1][sum2] / 1000 == 1)

		{

			i--;

			continue;

		}

		computer[i] = card[sum1][sum2];

		card[sum1][sum2] = card[sum1][sum2] + 1000;

	}

 

}

 

 

void correct()

{

	for (int i = 0; i <= 14; i++)

	{

		if (computer[i] == 0 && computer[i + 1]!=0)

		{

			computer[i] = computer[i + 1];

			computer[i + 1] = 0;

		}

	}

 

	for (int i = 0; i <= 14; i++)

	{

		if (player[i] == 0 && player[i + 1] != 0)

		{

			player[i] = player[i + 1];

			player[i + 1] = 0;

		}

	}

}

 

 

void comturn() //컴퓨터 턴

{

	

	int use = 0;

	srand((unsigned int)time(NULL)); //랜덤 모듈

 

	for (int i = 0; i < 4; i++) 

	{

		if (use == 1)

		{

			break;

		}

		for (int n = 0; n < 13; n++)

		{

			if (use == 1)

			{

				break;

			}

			for (int r = 0; r <= 14; r++)

			{

				if (computer[r] == card[i][n]-1000 ) //컴퓨터의 카드에서 카드 배열에서 -1000한 값과 같은 카드찾기

				{

					if ((((center / 10) % 2 == 1) && (((center / 10) == (computer[r] / 10)) || ((center / 10) == (computer[r] / 10 - 1)))) || ((((center / 10) % 2 == 0) && (((center / 10) == (computer[r] / 10)))) || ((center / 10) == (computer[r] / 10 + 1))) || ((center % 10) == (computer[r] % 10)))  //그 카드를 10으로 나눈값이 같거나 나머지가 같으면

					{

						for (int j = 0; j <= 51; j++) // 더미 채우기

						{

							if (dummy[j] == 0)

							{

								dummy[j] = center;

								break;

							}

						}

						center = computer[r];     //새로운 center를 지정해준다.

						computer[r] = 0;    // 컴퓨터 카드의 하나를 없앤다.

						correct();

						use++;

						if (use == 1)

						{

							break;

						}

					}

				}

			}

		}

	}

 

	if(use == 0)

	{

		for (int i = 0; i < 16; i++) //새로운 카드 넣어주기

		{

			int sum1 = (rand() % 4);

			int sum2 = (rand() % 13);

			if (card[sum1][sum2] / 1000 == 1)

			{

				i--;

				continue;

			}

			else

			{

				if (computer[i] != 0)

				{

					continue;

				}

				else

				{

					computer[i] = card[sum1][sum2];

					card[sum1][sum2] = card[sum1][sum2] + 1000;

					break;

				}

			}

		}

	}

}

 

 

void plturn() //플레이어 턴

{

 

    int number;

	while (1)

	{

		system("cls");

		prcard();

		gotoxy(40, 25);

		printf("낼 카드의 숫자를 입력해주세요 ==>>");

 

		gotoxy(75, 25);

		scanf("%d", &number);

		

		if (number == 99)

		{

			for (int i = 0; i < 16; i++) //새로운 카드 넣어주기

			{

				int sum1 = (rand() % 4);

				int sum2 = (rand() % 13);

				if (card[sum1][sum2] / 1000 == 1)

				{

					i--;

					continue;

				}

				else

				{

					if (player[i] != 0)

					{

						continue;

					}

					else

					{

						player[i] = card[sum1][sum2];

						card[sum1][sum2] = card[sum1][sum2] + 1000;

						break;

					}

				}

			}

			break;

 

		}

		else if ((((center / 10) % 2 == 1) && (((center / 10) == (player[number] / 10)) || ((center / 10) == (player[number] / 10 - 1)))) || ((((center / 10) % 2 == 0) && (((center / 10) == (player[number] / 10)))) || ((center / 10) == (player[number] / 10 + 1))) || ((center % 10) == (player[number] % 10)))  //그 카드를 10으로 나눈값이 같거나 나머지가 같으면

		{

			for (int j = 0; j <= 51; j++) // 더미 채우기

			{

				if (dummy[j] == 0)

				{

					dummy[j] = center;

					break;

				}

			}

			center = player[number];

			player[number] = 0;    // 플레이어 카드의 하나를 없앤다.

			break;

		}

		else if (player[number] == 0)

		{

			printf("다시선택해라");

			Sleep(1000);

			continue;

		}

		else

		{

			printf("다시선택해라");

			Sleep(1000);

			continue;

		}

	}

}

 

 

void prcard()

{

	int card[4][13] =

	{

	   {10,11,12,13,14,15,16,17,18,19,20,21,22},  //♠

	   {30,31,32,33,34,35,36,37,38,39,40,41,42},  //◆

	   {50,51,52,53,54,55,56,57,58,59,60,61,62},  //♥

	   {70,71,72,73,74,75,76,77,78,79,80,81,82}   //♣

	}; //카드 종류 배열

	

	char symbol[4][4] = { "♤", "◇" , "♡", "♧" };

	

	int position[14] = {0,10,20,30,40,50,60,70,0,10,20,30,40,50};

 

 

 

	for (int i = 0; i < 4; i++) //컴퓨터 카드

	{

		for (int n = 0; n < 13; n++)

		{

			for (int r = 0; r < 15; r++)

			{

				if (computer[r] == card[i][n])

				{

					if (r<=7)

					{

						gotoxy(position[r], 0);

						printf("┏━━━┓\n");

						gotoxy(position[r], 1);

						printf("┃%s    ┃\n", symbol[i]);

						gotoxy(position[r], 2);

						printf("┃      ┃\n");

						gotoxy(position[r], 3);

						switch (n + 1)

						{

						case 13:

							printf("┃   K  ┃\n");

							break;

						case 12:

							printf("┃   Q  ┃\n");

							break;;

						case 11:

							printf("┃   J  ┃\n");

							break;

						case 1:

							printf("┃   A  ┃\n");

							break;

						case 10:

							printf("┃  %d  ┃\n", n + 1);

							break;

						default:

							printf("┃   %d  ┃\n", n + 1);

							break;

						}

 

						gotoxy(position[r], 4);

						printf("┃      ┃\n");

						gotoxy(position[r], 5);

						printf("┃    %s┃\n", symbol[i]);

						gotoxy(position[r], 6);

						printf("┗━━━┛\n");

					}

					else

					{

						gotoxy(position[r], 8);

						printf("┏━━━┓\n");

						gotoxy(position[r], 9);

						printf("┃%s    ┃\n", symbol[i]);

						gotoxy(position[r], 10);

						printf("┃      ┃\n");

						gotoxy(position[r], 11);

						switch (n + 1)

						{

						case 13:

							printf("┃   K  ┃\n");

							break;

						case 12:

							printf("┃   Q  ┃\n");

							break;;

						case 11:

							printf("┃   J  ┃\n");

							break;

						case 1:

							printf("┃   A  ┃\n");

							break;

						case 10:

							printf("┃  %d  ┃\n", n + 1);

							break;

						default:

							printf("┃   %d  ┃\n", n + 1);

							break;

						}

 

						gotoxy(position[r], 12);

						printf("┃      ┃\n");

						gotoxy(position[r], 13);

						printf("┃    %s┃\n", symbol[i]);

						gotoxy(position[r], 14);

						printf("┗━━━┛\n");

					}

				}

 

			}

 

		}

	}

 

 

	for (int i = 0; i < 4; i++)//플레이어 카드

	{

		for (int n = 0; n < 13; n++)

		{

			for (int r = 0; r < 15; r++)

			{

				if (player[r] == card[i][n])

				{

					if (r <= 7)

					{

						gotoxy(position[r], 30);

						printf("┏━━━┓\n");

						gotoxy(position[r], 31);

						printf("┃%s    ┃\n", symbol[i]);

						gotoxy(position[r], 32);

						printf("┃      ┃\n");

						gotoxy(position[r], 33);

						switch (n + 1)

						{

						case 13:

							printf("┃   K  ┃\n");

							break;

						case 12:

							printf("┃   Q  ┃\n");

							break;;

						case 11:

							printf("┃   J  ┃\n");

							break;

						case 1:

							printf("┃   A  ┃\n");

							break;

						case 10:

							printf("┃  %d  ┃\n", n + 1);

							break;

						default:

							printf("┃   %d  ┃\n", n + 1);

							break;

						}

 

						gotoxy(position[r], 34);

						printf("┃      ┃\n");

						gotoxy(position[r], 35);

						printf("┃    %s┃\n", symbol[i]);

						gotoxy(position[r], 36);

						printf("┗━━━┛\n");

					}

					else

					{

						gotoxy(position[r], 38);

						printf("┏━━━┓\n");

						gotoxy(position[r], 39);

						printf("┃%s    ┃\n", symbol[i]);

						gotoxy(position[r], 40);

						printf("┃      ┃\n");

						gotoxy(position[r], 41);

						switch (n + 1)

						{

						case 13:

							printf("┃   K  ┃\n");

							break;

						case 12:

							printf("┃   Q  ┃\n");

							break;;

						case 11:

							printf("┃   J  ┃\n");

							break;

						case 1:

							printf("┃   A  ┃\n");

							break;

						case 10:

							printf("┃  %d  ┃\n", n + 1);

							break;

						default:

							printf("┃   %d  ┃\n", n + 1);

							break;

						}

 

						gotoxy(position[r], 42);

						printf("┃      ┃\n");

						gotoxy(position[r], 43);

						printf("┃    %s┃\n", symbol[i]);

						gotoxy(position[r], 44);

						printf("┗━━━┛\n");

					}

				}

			}

 

		}

	}

 

	for (int i = 0; i < 4; i++)  //center

	{

		for (int n = 0; n < 13; n++)

		{

			if (center == card[i][n])

			{

				gotoxy(45, 13);

				printf("┏━━━┓\n");

				gotoxy(45, 14);

				printf("┃%s    ┃\n", symbol[i]);

				gotoxy(45, 15);

				printf("┃      ┃\n");

				gotoxy(45, 16);

				switch (n + 1)

				{

				case 13:

					printf("┃   K  ┃\n");

					break;

				case 12:

					printf("┃   Q  ┃\n");

					break;

				case 11:

					printf("┃   J  ┃\n");

					break;

				case 1:

					printf("┃   A  ┃\n");

					break;

				case 10:

					printf("┃  %d  ┃\n", n + 1);

					break;

				default:

					printf("┃   %d  ┃\n", n + 1);

					break;

				}

 

			    gotoxy(45, 17);

			    printf("┃      ┃\n");

				gotoxy(45, 18);

				printf("┃    %s┃\n", symbol[i]);

				gotoxy(45, 19);

				printf("┗━━━┛\n");

		    }

		}

	}

 

}

 

 

void dummyf()

{

	if (dummy[39] == 0)

	{

		for (int i = 0; i < 4; i++)

		{

			for (int n = 0; n < 13; n++)

			{

				for (int r = 0; r <= 52; r++)

				{

					if (dummy[r] == card[i][n] - 1000)

					{

						card[i][n] = dummy[r];

					}

 

				}

 

			}

		}

	}

	correct();

}

 

 

 

void gotoxy(int x, int y)

{

	COORD XY = { x,y };

	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hHandle, XY);

}