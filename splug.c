#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct card {
	int month;
	char type[8];
};
typedef struct card Card;

struct player_data {
	Card data;
	struct player_data *next;
};
typedef struct player_data playerData;

struct player {
	playerData hand;
	playerData get;
};
typedef struct player Player;

//Player -> playerData -> card ������ ������

void Shuffle(Card deck[]);
void Init(Player player[3], Card deck[48], playerData * ptr[3], playerData *floorPtr, playerData * dummyPtr);
void GiveCardToPlayer(Player, Card, playerData*);
void GiveCardToDummy(playerData * dummyPtr, Card deck);
void GiveCardToFloor(playerData * floorPtr, Card deck);
void ShowCard(playerData * ptr[3]);
void FromHandToGet(Player player, int choice);

int main(int argc, const char * argv[])
{
	Card deck[48] = {
		1,"��",1,"��",1,"��",1,"��",//��
		2,"��",2,"��",2,"��",2,"��",//����
		3,"��",3,"��",3,"��",3,"��",//�����
		4,"��",4,"��",4,"��",4,"��",//��θ�
		5,"��",5,"��",5,"��",5,"��",//��
		6,"��",6,"��",6,"��",6,"��",//���(���)
		7,"��",7,"��",7,"��",7,"��",//ȫ�θ�
		8,"��",8,"��",8,"��",8,"��",//��
		9,"����",9,"��",9,"��",9,"��",//��ȭ(+����)
		10,"��",10,"��",10,"��",10,"����",//��ǳ
		11,"��",11,"��",11,"��",11,"����",//��
		12,"��",12,"��",12,"��",12,"����"//��
	};
	//////////////////////////////////initialize pointer information/////////////////////////////////
	playerData blank;
	blank.data.month = 0;
	strcpy(blank.data.type, "Player");
	blank.next = NULL;

	Player player[3];
	for (int i = 0; i<3; i++) {
		player[i].hand = blank;
		player[i].get = blank;
	}
	playerData * initHandPtr[3];//these ptr are to point player's hand information only
	for (int i = 0; i<3; i++) {
		initHandPtr[i] = (playerData*)malloc(sizeof(playerData));
		initHandPtr[i]->next = NULL;
	}
	playerData * initGetPtr[3];
	for (int i = 0; i < 3; i++) {
		initGetPtr[i] = (playerData*)malloc(sizeof(playerData));
		initGetPtr[i]->next = NULL;
	}
	playerData * floorPtr = (playerData*)malloc(sizeof(playerData));
	floorPtr->next = NULL;

	playerData * dummyPtr = (playerData*)malloc(sizeof(playerData));
	dummyPtr->next = NULL;
	/////////////////////////////////////////////////////////////////////////////////////////////

	//Shuffle(deck);
	Init(player, deck, initHandPtr, floorPtr, dummyPtr);
	ShowCard(initHandPtr);
	//printf("%d%s	",player[0].hand.next->next->data.month,player[0].hand.next->next->data.type);
	FromHandToGet(player[0],initGetPtr[0], 3);

	return 0;
}
void Shuffle(Card deck[48])
{
	Card tmp;
	int j = 0;

	srand(time(NULL));
	for (int i = 0; i<48; i++)
	{
		j = rand() % 48;
		tmp = deck[i];
		deck[i] = deck[j];
		deck[j] = tmp;
	}
}
void ShowCard(playerData * ptr[3])
{

	for (int i = 0; i<3; i++) {
		while (ptr[i] != NULL) {
			printf("%d%s	", ptr[i]->data.month, ptr[i]->data.type);
			ptr[i] = ptr[i]->next;
		}
		printf("\n");
	}
}
//Player -> playerData -> card ������ ������
void Init(Player player[3], Card deck[48], playerData * playerPtr[3], playerData * floorPtr, playerData *dummyPtr)
{
	for (int i = 0; i<24; i++) {
		if (i >= 0 && i<8) {
			playerPtr[0] = &(player[0].hand);
			GiveCardToPlayer(player[0], deck[i], playerPtr[0]);
		}
		else if (i >= 8 && i<16) {
			playerPtr[1] = &(player[1].hand);
			GiveCardToPlayer(player[1], deck[i], playerPtr[1]);
		}
		else if (i >= 16 && i<24) {
			playerPtr[2] = &(player[2].hand);
			GiveCardToPlayer(player[2], deck[i], playerPtr[2]);
		}
	}
	for (int i = 24; i<30; i++)
		GiveCardToFloor(floorPtr, deck[i]);
	for (int i = 30; i<48; i++)
		GiveCardToDummy(dummyPtr, deck[i]);
}
void GiveCardToPlayer(Player player, Card deck, playerData * handPtr)
{
	playerData * new = (playerData*)malloc(sizeof(playerData));
	new->data = deck;
	new->next = NULL;
	while (handPtr->next != NULL)
		handPtr = handPtr->next;
	handPtr->next = new;
}
void GiveCardToFloor(playerData * floorPtr, Card deck)
{
	playerData * tmp = floorPtr;
	playerData * new = (playerData*)malloc(sizeof(playerData));
	new->data = deck;
	new->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
void GiveCardToDummy(playerData * dummyPtr, Card deck)
{
	playerData * tmp = dummyPtr;
	playerData * new = (playerData*)malloc(sizeof(playerData));
	new->data = deck;
	new->next = NULL;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
void FromHandToGet(Player player, playerData * initGetPtr, int choice)
{
	playerData * handPtr = &(player.hand);
	playerData * handPrev = NULL;
	initGetPtr = &(player.get);//get�� ��带 ����Ű�� ���� �뵵�̰�, ���� �Ҵ��� main()���� �س��� ������
	for (int i = 0; i < choice + 1; i++) {
		handPrev = handPtr;
		handPtr = handPtr->next;
	}
	while (initGetPtr->next != NULL)
		initGetPtr = initGetPtr->next;
	handPrev->next = handPtr->next;
	initGetPtr->next = handPtr;
	handPtr = NULL;
}