#include <iostream>
#include <ncurses.h>
#include <string>
using namespace std;

int StartTypingTest(void);
int Restart(void);

struct user{
	float score = 0;
	char name[20];
} currentUser;

int main(){

	//kieli
	int lang = 0;

	//inittaa ncurses ikkunan
	initscr();
	//inittaa värien käytön
	start_color();
	//päivittää ikkunan
	refresh();
	//liikuttaa kursorin kohtaan x = 5, y = 5
	move(5,5); 

	printw("Select your language:\n 1 = English(default), 2 = Finnish: ");
	lang = getch();
	if(lang == 1) {
		//lataa eng-wordlist
	} else if (lang == 2) {
		//lataa fin-wordlist
	} else {
		lang = 1;
		//lataa eng-wordlist
	}
	//kysyy nimeä
	clear();
	move(5,5);
	printw("\nInput your username: ");
	//kirjoita nimi currentUser structiin
	getstr(currentUser.name);
	//aloita StartTypingTest aliohjelma
	StartTypingTest();
	Restart();
	return 0;
}

int StartTypingTest(void){
	
	clear();
	move(5,5);
	printw("\nPress any key to start typest");
	getch();
	//testin aloitus
	//testin lopetus
	printw("\nYour score was ");
	return 0;
}

int Restart(void){
	char temp[1];
	printw("Would you like to retry?(y/n)");
	temp[1]=getch();
	if(temp[1] == "y") {
		StartTypingTest();
	}
	else{
		return 0;
	}
}