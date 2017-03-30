	//
	//  main.c
	//  splug2
	//
	//  Created by 김찬민 on 2017. 3. 29..
	//  Copyright © 2017년 김찬민. All rights reserved.
	//
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
		playerData handPtr;
		playerData getPtr;
	};
	typedef struct player Player;

	//Player -> playerData -> card 순으로 내려감

	void Shuffle(Card deck[]);
	void Init(Player player[3],Card deck[48],playerData * ptr[3]);
	void GiveCardToPlayer(Player,Card,playerData*);

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

		playerData blank;
		blank.data.month=0;
		strcpy(blank.data.type,"blank");
		blank.next=NULL;

		Player player[3];
		
		for(int i=0;i<3;i++){
			player[i].handPtr=blank;
			player[i].getPtr=blank;
		}
		playerData * ptr[3];
		for(int i=0;i<3;i++){
			ptr[i]=(playerData*)malloc(sizeof(playerData));
			ptr[i]->next=NULL;
			ptr[i]=&(player[i].handPtr);
		}
		
		
		//Shuffle(deck);
		Init(player,deck,ptr);
/*********************************************************		
		while(ptr[i]!=NULL){
			printf("%d%s	",ptr[i]->data.month,ptr[i]->data.type);
			ptr[i]=ptr[i]->next;
		}
*********************************************************/	//this is for test
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

	//Player -> playerData -> card 순으로 내려감
	void Init(Player player[3],Card deck[48],playerData * ptr[3])
	{
		for(int i=0;i<24;i++){
			if(i>=0 && i<8){
				GiveCardToPlayer(player[0],deck[i],ptr[0]);
			}
			else if(i>=8 && i<16){
				GiveCardToPlayer(player[1],deck[i],ptr[1]);
			}
			else if(i>=16 && i<24){
				GiveCardToPlayer(player[2],deck[i],ptr[2]);
			}
		}
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

			


