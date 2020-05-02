#include <iostream>
#include <time.h>

/*
Spell Lethal Odds Calculator

This program works for any random repeating single target damage spell that can go face:
	Imprisoned Antaen
	Priestess of Fury
	Arcane Missiles
	Avenging Wrath
With the popularity of demon hunter the calculator is useful despite there only being a few standard cards this is applicable for.
	

Follow me @ https://www.twitch.tv/betoasths
			https://twitter.com/BeToastHS

If you want Hearthstone Coaching add me on discord: BeToast#4878
*/

struct minion 
{
	int health;
	bool alive;
};

struct hero
{
	int health;
	bool alive = 1;
};

void getInfo(), condenseMinions(), resetVariables();
int fireShots(int), genRandom(int);
bool shootSingleMinion(int);

struct hero Zalae, backupZalae;
struct minion minions[7], backupMinions[7];
int numShots, minionsLeft, backupMinionsLeft;
float lethalOdds;

int main()
{
	srand(time(0));
	getInfo();
	for (int i = 0; i < 10000; i++)
	{
		if (fireShots(numShots) == 0)
			lethalOdds++;
		resetVariables();
	}
	lethalOdds /= 100;
	printf("\n Your odds of lethal are %0.2f%%\n", lethalOdds);
}

void getInfo()
{
	printf("\n Enter hero health: "); scanf("%d", &Zalae.health);
	printf("\n How many minions?: "); scanf("%d", &minionsLeft);
	for (int i = 0; i < minionsLeft; i++)
	{	
		if (i == 0)
		{
			printf("\n 1st minion health: "); scanf("%d", &minions[i].health);
		}
		else if (i == 1)
		{
			printf("\n 2nd minion health: "); scanf("%d", &minions[i].health);
		}
		else if (i == 2)
		{
			printf("\n 3rd minion health: "); scanf("%d", &minions[i].health);
		}
		else
		{
			printf("\n %dth minion health: ", i); scanf("%d", &minions[i].health);
		}
		minions[i].alive = 1;
	}
	printf("\n (Priestess of Fury is 6, Avenging Wrath is 8) Enter number of randomly split damage: "); scanf("%d", &numShots);

	//this just declares the values of the backups.
	for (int i = 0; i < minionsLeft; i++)
		backupMinions[i] = minions[i];
	backupZalae = Zalae;
	backupMinionsLeft = minionsLeft;
}

int fireShots(int numShots) //This function will return 0 if Zalae dies and return 1 if he lives
{
	for (int i = 0; i < numShots; i++)
		if (shootSingleMinion(genRandom(minionsLeft)) == 0)
			return 0;
	return 1;
}

bool shootSingleMinion(int targetHit) //this will subtract a health from a minion and if the minion dies it will condense the array.
{
	switch (targetHit)
	{
	case 0:
		Zalae.health--;
		if (Zalae.health == 0) Zalae.alive = 0;
		break;
	default:
		minions[targetHit].health--;
		if (minions[targetHit].health == 0)
		{
			minions[targetHit].alive = 0;
			condenseMinions();
			minionsLeft--;
		}
	}
	return Zalae.alive;
}

void condenseMinions() //this will get rid of a dead minion from the array.
{
	for (int i = 0; i < minionsLeft; i++)
	{
		if (minions[i].alive == 0)
		{
			for (i < minionsLeft; i++;)
			{
				if (i == 6)
					break;
				minions[i] = minions[i + 1];
			}
			minionsLeft = minionsLeft--;
			break;
		}
	}
}

int genRandom(int minionsLeft)
{
	int i;
	//the range is just like the number of possible things to hit (if you input 4 it will gen a thinger between 0 and 4, 0 for the hero)
	int num = (rand() % (minionsLeft+1));
	return num;
}

void resetVariables()
{
	for (int i = 0; i < minionsLeft; i++)
		minions[i] = backupMinions[i];
	Zalae = backupZalae;
	minionsLeft = backupMinionsLeft;
}