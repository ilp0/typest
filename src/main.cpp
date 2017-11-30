#include <iostream>
#include <ncurses.h>
#include <string>
#include "string.h"
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int StartTypingTest(int lang);
int Restart(void);
int Wordlist(int lang);
int Menu(void);
int Highscores(void);

static const int wordcount_fi = 1281, wordcount_en = 5421;
string wordlistEng[wordcount_en];
string wordlistFin[wordcount_fi];

struct user{
	double wpm = 0;
	char name[20];
} currentUser;

int main(){
	//aseta random seed
	srand (time(NULL));
	//settaa locale että ääkköset toimii normaalisti
	setlocale(LC_ALL, "fi_FI.UTF-8");
	//inittaa ncurses ikkunan
	initscr();
	//inittaa värien käytön
	start_color();
	//päivittää ikkunan
	refresh();
	//liikuttaa kursorin kohtaan x = 0, y = 0
	move(0,0); 
	printw("Select your word list language:\n 1 = English(default), 2 = Finnish: ");
	int lang = getch();
	Wordlist(lang);
	Menu();
	clear(); 
	move(0,0);
	printw("\nInput your username: ");
	getstr(currentUser.name);
	StartTypingTest(lang);
	Restart();
	return 0;
}

int StartTypingTest(int lang){

	clear();
	move(5,5);
	printw("You have 60 seconds to type as many words as possible. \nPress any key to start typest");
	getch();
	clear();
	move(5,5);
	refresh();

	int currentX = 0;
	char tempCh;
	string tempWrittenWord, tempword, tempNextWord;
	int score = 0;
	int wrongLetters = 0;
	int fullScore = 0;
	int totalChars = 0;
	int time = 0;
	int correctedLetters = 0;
	//aloita ajastin
	auto start = high_resolution_clock::now();
	
//SANOJEN PRINTTAUS JA SYÖTTÖ
	for (int i = 0; i < 50; i++){


		//HAE RANDOM SANA WORDLISTISTÄ
		if(i == 0){
			tempword =  wordlistEng[rand()%wordcount_en] + " ";
		} else {
			tempword = tempNextWord;
		}
		tempNextWord = wordlistEng[rand()%wordcount_en] + " ";
		fullScore += tempword.length();
		clear();
		move(1,1);
		move(0,0);
		refresh();
		printw(tempword.c_str());
		printw(" ");
		printw(tempNextWord.c_str());
		move(0,0);
		//HAE CHAREJA KUNNES KÄYTTÄJÄ PAINAA SPACEA
		 for (int a = 0; tempCh != ' ';a++) {
            tempCh = '\0';
            tempCh = getch();
			totalChars++;
            currentX++;
            tempWrittenWord = tempWrittenWord + tempCh;
			if (tempCh == 127 || tempCh	== 8){
				tempWrittenWord[a] == '\0';
				if (currentX > 1) currentX -= 2;
				move(0, currentX);
				if (a > 1) a -= 2;
				totalChars--;
				correctedLetters++;
			}
		}
		for (int c = 0; c < tempword.size(); c++){
			if (tempword[c] == tempWrittenWord[c]) {
				score++;
			} else {
				wrongLetters++;
            }
        }
		currentX = 0;
		tempCh = '\0';
		tempword = "";
		tempWrittenWord = "";
	}
	wrongLetters -= correctedLetters;
	//lopeta ajastin
    auto end = high_resolution_clock::now();
    time = duration_cast<seconds>(end - start).count();
	double grossWPM = (totalChars/5) / (time / 60);
	double netWPM = grossWPM - ((wrongLetters/5)/(time/60));
	double accuracy = (netWPM/grossWPM) * 100;
	currentUser.wpm = grossWPM;
	clear();
	refresh();
	getch();
	move(1,0);
	printw("it took you ");
	printw("%i", time);
	printw(" seconds");
	printw("\ntotal letters typed: ");
	printw("%i", totalChars);
	printw("\ncorrect letters: ");
	printw("%i", score);
	printw("\nincorrect letters: ");
	printw("%i", wrongLetters);
	printw("\nWPM: ");
	printw("%f", grossWPM);
	printw("\nAccuracy: ");
	printw("%f", accuracy);
	getch();
	return 0;
}

int Restart(void){
	char temp;
	printw("Would you like to retry?(y/n)");
	temp = getch();
	if(temp == 'y' || temp == 'Y') StartTypingTest(1);
	else{return 0;}
}

int Wordlist(int lang){
	
	if(lang != 2) {	
		ifstream file("wordlist_en.txt");
		if(file.is_open())
		{
			for(int i = 0; i < wordcount_en; ++i)
			{
				file >> wordlistEng[i];
			}
		}

	} else {
		
		ifstream file("wordlist_fi.txt");
		if(file.is_open())
		{
			for(int i = 0; i < wordcount_fi; ++i)
			{
				file >> wordlistFin[i];
		}
	}
}	
}

int Menu(){
	clear();
	move(0,0);
	printw("MENU\n");
	printw("1. PLAY TYPEST\n");
	printw("2. VIEW LOCAL HIGHSCORES");
	int menu = getch();
	switch (menu){
		case 1: return 0;
		case 2: Highscores();
	}

}
int Highscores(){
	
	foreach (){

	}
}

