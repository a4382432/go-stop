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

//Player -> playerData -> card ¼øÀ¸·Î ³»·Á°¨

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
		1,"±¤",1,"¶ì",1,"ÇÇ",1,"ÇÇ",//»ê
		2,"²ý",2,"¶ì",2,"ÇÇ",2,"ÇÇ",//¸ÅÁ¶
		3,"±¤",3,"¶ì",3,"ÇÇ",3,"ÇÇ",//»çÄí¶ó
		4,"²ý",4,"¶ì",4,"ÇÇ",4,"ÇÇ",//Èæ½Î¸®
		5,"²ý",5,"¶ì",5,"ÇÇ",5,"ÇÇ",//³­
		6,"²ý",6,"¶ì",6,"ÇÇ",6,"ÇÇ",//¸ð¶õ(Àå¹Ì)
		7,"²ý",7,"¶ì",7,"ÇÇ",7,"ÇÇ",//È«½Î¸®
		8,"±¤",8,"²ý",8,"ÇÇ",8,"ÇÇ",//»ê
		9,"½ÖÇÇ",9,"¶ì",9,"ÇÇ",9,"ÇÇ",//±¹È­(+±¹Áø)
		10,"²ý",10,"¶ì",10,"ÇÇ",10,"½ÖÇÇ",//´ÜÇ³
		11,"±¤",11,"ÇÇ",11,"ÇÇ",11,"½ÖÇÇ",//¶Ë
		12,"±¤",12,"²ý",12,"ÇÇ",12,"½ÖÇÇ"//ºñ
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
//Player -> playerData -> card ¼øÀ¸·Î ³»·Á°¨
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
	initGetPtr = &(player.get);//getÀÇ ³ëµå¸¦ °¡¸®Å°±â À§ÇÑ ¿ëµµÀÌ°í, °ø°£ ÇÒ´çÀº main()¿¡¼­ ÇØ³õÀº »óÅÂÀÓ
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