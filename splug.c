#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct card{
	int month;
	char type[8];
};
typedef struct card Card;

struct player_data{
	Card data;
	struct player_data *next;
};
typedef struct player_data playerData;

struct player{
	playerData hand;
	playerData get;
};
typedef struct player Player;

//Player -> playerData -> card 순으로 내려감

void Shuffle(Card deck[]);
void Init(Player player[3],Card deck[48],playerData * ptr[3],playerData *floorPtr,playerData * dummyPtr);
void GiveCardToPlayer(Player,Card,playerData*);
void GiveCardToDummy(playerData * dummyPtr,Card deck);
void GiveCardToFloor(playerData * floorPtr,Card deck);
void ShowCard(playerData * ptr[3]);

int main(int argc, const char * argv[])
{
	Card deck[48]={
		1,"광",1,"띠",1,"피",1,"피",//산
		2,"끗",2,"띠",2,"피",2,"피",//매조
		3,"광",3,"띠",3,"피",3,"피",//사쿠라
		4,"끗",4,"띠",4,"피",4,"피",//흑싸리
		5,"끗",5,"띠",5,"피",5,"피",//난
		6,"끗",6,"띠",6,"피",6,"피",//모란(장미)
		7,"끗",7,"띠",7,"피",7,"피",//홍싸리
		8,"광",8,"끗",8,"피",8,"피",//산
		9,"쌍피",9,"띠",9,"피",9,"피",//국화(+국진)
		10,"끗",10,"띠",10,"피",10,"쌍피",//단풍
		11,"광",11,"피",11,"피",11,"쌍피",//똥
		12,"광",12,"끗",12,"피",12,"쌍피"//비
	};
//////////////////////////////////initialize pointer information/////////////////////////////////
	playerData blank;
	blank.data.month=0;
	strcpy(blank.data.type,"Player");
	blank.next=NULL;

	Player player[3];
	for(int i=0;i<3;i++){
		player[i].hand=blank;
		player[i].get=blank;
	}
	playerData * playerPtr[3];//these ptr are to point player's information only
	for(int i=0;i<3;i++){
		playerPtr[i]=(playerData*)malloc(sizeof(playerData));
		playerPtr[i]->next=NULL;
	}

	playerData * floorPtr=(playerData*)malloc(sizeof(playerData));
	floorPtr->next=NULL;

	playerData * dummyPtr=(playerData*)malloc(sizeof(playerData));
	dummyPtr->next=NULL;
/////////////////////////////////////////////////////////////////////////////////////////////

	//Shuffle(deck);
	Init(player,deck,playerPtr,floorPtr,dummyPtr);
	ShowCard(playerPtr);
	return 0;
}
void Shuffle(Card deck[48])
{
	Card tmp;
	int j=0;

	srand(time(NULL));
	for(int i=0;i<48;i++)
	{
		j=rand()%48;
		tmp=deck[i];
		deck[i]=deck[j];
		deck[j]=tmp;
	}
}
void ShowCard(playerData * ptr[3])
{

	for(int i=0;i<3;i++){
		while(ptr[i]!=NULL){
			printf("%d%s	",ptr[i]->data.month,ptr[i]->data.type);
			ptr[i]=ptr[i]->next;
		}
		printf("\n");
	}
}
//Player -> playerData -> card 순으로 내려감
void Init(Player player[3],Card deck[48],playerData * ptr[3],playerData * floorPtr,playerData *dummyPtr)
{
	for(int i=0;i<24;i++){
		if(i>=0 && i<8){
			ptr[0]=&(player[0].hand);
			GiveCardToPlayer(player[0],deck[i],ptr[0]);
		}
		else if(i>=8 && i<16){
			ptr[1]=&(player[1].hand);
			GiveCardToPlayer(player[1],deck[i],ptr[1]);
		}
		else if(i>=16 && i<24){
			ptr[2]=&(player[2].hand);
			GiveCardToPlayer(player[2],deck[i],ptr[2]);
		}
	}
	for(int i=24;i<30;i++)
		GiveCardToFloor(floorPtr,deck[i]);
	for(int i=30;i<48;i++)
		GiveCardToDummy(dummyPtr,deck[i]);
}
void GiveCardToPlayer(Player player,Card deck,playerData * ptr)
{
	playerData * new=(playerData*)malloc(sizeof(playerData));
	new->data=deck;
	new->next=NULL;
	while(ptr->next !=NULL)
		ptr=ptr->next;
	ptr->next=new;
}
void GiveCardToFloor(playerData * floorPtr,Card deck)
{
	playerData * tmp=floorPtr;
	playerData * new=(playerData*)malloc(sizeof(playerData));
	new->data=deck;
	new->next=NULL;
	while(tmp->next !=NULL)
		tmp=tmp->next;
	tmp->next=new;
}
void GiveCardToDummy(playerData * dummyPtr,Card deck)
{
	playerData * tmp=dummyPtr;
	playerData * new=(playerData*)malloc(sizeof(playerData));
	new->data=deck;
	new->next=NULL;
	while(tmp->next !=NULL)
		tmp=tmp->next;
	tmp->next=new;
}
