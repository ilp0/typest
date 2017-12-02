#include <iostream>
#include <ncurses.h>
#include <string>
#include "string.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

int StartTypingTest(char lang);
int Restart(void);
int Wordlist(char lang);
int Menu(void);
int Highscores(void);
int writeHighscore(char lang);
int GetWebHighscores(void);

static const int wordcount_fi = 1113, wordcount_en = 5421;
string wordlistEng[wordcount_en];
string wordlistFin[wordcount_fi];

struct user{
	string name = "";
	double wpm = 0;
	double accuracy = 0;
	double score = 0;
	double time = 0;
} currentUser;

int main(){
	//aseta random seed
	srand (time(NULL));
	//settaa locale että ääkköset toimii normaalisti
	setlocale(LC_ALL, "");
	//inittaa ncurses ikkunan
	initscr();
	//inittaa värien käytön
	start_color();
	//päivittää ikkunan
	refresh();
	//liikuttaa kursorin kohtaan x = 0, y = 0
	move(0,0); 
	Menu();
	clear(); 
	printw("Select your wordlist language:\n 1 = English(default), 2 = Finnish: ");
	char lang = getch();
	Wordlist(lang);
	StartTypingTest(lang);
	Restart();
	return 0;
}

int StartTypingTest(char lang){

	clear();
	move(0,0);
	printw("Type 30 words as fast as possible. \nPress any key to start typest");
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
	float time = 0;
	int correctedLetters = 0;
	//aloita ajastin
	auto start = high_resolution_clock::now();
	
//SANOJEN PRINTTAUS JA SYÖTTÖ
	for (int i = 0; i < 30; i++){


		//HAE RANDOM SANA WORDLISTISTÄ
		if(lang == '2'){
			if(i == 0){
			tempword =  wordlistFin[rand()%wordcount_fi] + " ";
			} else {
			tempword = tempNextWord;
			}
			tempNextWord = wordlistFin[rand()%wordcount_fi] + " ";
		} else {
			if(i == 0){
			tempword =  wordlistEng[rand()%wordcount_en] + " ";
			} else {
			tempword = tempNextWord;
			}
			tempNextWord = wordlistEng[rand()%wordcount_en] + " ";
		}
		fullScore += tempword.length();
		clear();
		move(0,0);
		refresh();
		printw(tempword.c_str());
		printw(" ");
		if(i < 29) printw(tempNextWord.c_str());
		move (1,0);
		printw("%i", i);
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
	currentUser.accuracy = accuracy;
	currentUser.score = (totalChars - wrongLetters) / (time / 60) * accuracy;
	currentUser.time = time;
	getch();
	//kerro pelaajalle score ja kirjoitetaan tulos tiedostoon:
	clear();
	refresh();
	printw("       -------------\n");
	printw("       |  RESULTS  |\n");
	printw("       -------------\n");
	printw("\nIt took you............");
	printw("%.0f", time);
	printw(" seconds");
	printw("\nTotal letters typed....");
	printw("%i", totalChars);
	printw("\nCorrect letters........");
	printw("%i", score);
	printw("\nIncorrect letters......");
	printw("%i", wrongLetters);
	printw("\nWPM....................");
	printw("%.2f", grossWPM);
	printw("\nAccuracy...............");
	printw("%.2f", accuracy);
	printw("percent\n");
	printw("\nTYPEST SCORE: ");
	printw("%.0f", currentUser.score);
	printw("\nPress any key to continue");
	getch();
	clear();
	printw("Would you like to save the score?(y/n)\n");
	char save = getch();
	clear();
	if(save == 'y' || save == 'Y'){ 
	writeHighscore(lang);
	clear();
	printw("Score saved!\n");
	}

	getch();
	clear();
	return 0;
}

int Restart(void){
	char temp;
	printw("Go back to menu?(y/n)\n");
	temp = getch();
	if(temp == 'y' || temp == 'Y') Menu();
	else{return 0;}
}

int Wordlist(char lang){
	if(lang == '2') {	
		ifstream file(".wordlist_fi.txt");
		if(file.is_open())
		{
			for(int i = 0; i < wordcount_fi; ++i)
			{
				file >> wordlistFin[i];
			}
		}
	} else {
		ifstream file(".wordlist_en.txt");
		if(file.is_open())
		{
			for(int i = 0; i < wordcount_en; ++i)
			{
				file >> wordlistEng[i];
			}
		}
	}	
}

int Menu(){
	move(0,0);
	
	for (int i = 15; i != 0; i--){
	clear();
	move(i,i);	
	printw("  dP                                         dP   \n");
	move(i+1,i);	
	printw("  88                                         88   \n");
	move(i+2,i);	
	printw("d8888P dP    dP 88d888b. .d8888b. .d8888b. d8888P \n");
	move(i+3,i);	
	printw("  88   88    88 88'  `88 88ooood8 Y8ooooo.   88   \n");
	move(i+4,i);	
	printw("  88   88.  .88 88.  .88 88.  ...       88   88   \n");
	move(i+5,i);	
	printw("  dP   `8888P88 88Y888P' `88888P' `88888P'   dP   \n");
	move(i+6,i);	
	printw("            .88 88                                \n");
	move(i+7,i);	
	printw("        d8888P  dP                                \n");
	refresh();
	napms(100);
	
	}
	if (currentUser.name == ""){
		printw("\n         Please enter your username(max. 8 characters):\n");
		move(11,9);
		char name[100];
		getstr(name);
		currentUser.name = name;
		move (10,0);
		printw("                                              \n                               ");
		move(10,0);
	}
	printw("              ----------------\n");
	printw("              |     MENU     |\n");
	printw("              ----------------\n");
	printw("              1. PLAY TYPEST\n");
	printw("              2. VIEW LOCAL HIGHSCORE\n");
	printw("              3. VIEW ONLINE HIGHSCORES");
	char menu = getch();
	switch (menu){
		case '1': return 0;
		case '2': Highscores();
		case '3': GetWebHighscores();
	}
}

int Highscores(){
	clear();
	ifstream file;
	file.open(".highscores.txt");
	string highscore;
	printw("               TOP 10 LOCAL SCORES\n");
	printw("Language -  WPM  -  Time  -  Accuracy  -  Score\n");
	printw("-----------------------------------------------\n");
	printw("\n");

	for (int i = 0; !file.eof() || i == 10; i++){
		getline(file,highscore);
		printw(highscore.c_str());
		printw("\n");
	}
	printw("-----------------------------------------------");
	printw("\n  Press any key to get back to menu.\n");
	getch();
	Menu();
}

int GetWebHighscores(){
	clear();
	string line;
	//hakee servulta highscoret
	system("wget http://34.241.121.194/typest/typest_get.php");
	//printtaa
	printw("              TOP 10 ONLINE SCORES\n");
	printw("Language  -  Name -  WPM  -  Accuracy  -  Score  -  Timestamp      \n");
	printw("--------------------------------------------------------------\n");
	ifstream scoreFile ("typest_get.php");
	while (!scoreFile.eof()){
		getline(scoreFile,line);
		printw(line.c_str());
		printw("\n");
	}
	printw("--------------------------------------------------------------\n");
	//sulkee tiedoston
	scoreFile.close();
	//poistaa haetun tiedoston.
	system("rm typest_get.php");
	refresh();
	getch();
	//takaisin menuun
	Menu();
}

int writeHighscore(char lang) {
	//avaa highscoretiedosto
	ofstream highscoreFile;
	string hsString;
	highscoreFile.open(".highscores.txt", ios::app);
	//muuta numerot stringiksi
	auto accStr = to_string(currentUser.accuracy);
	auto wpmStr = to_string(currentUser.wpm);
	auto scoreStr = to_string(currentUser.score);
	auto timeStr = to_string(currentUser.time);
	string language;
	if (lang == '2'){
		language = "Finnish";
	} else{
		language = "English";
	}
	//formatointia
	hsString = language + " " + wpmStr + " " + timeStr + " " + accStr + " " + scoreStr;
	//kirjoittaa tiedostoon formatoidun stringin
	highscoreFile << hsString <<endl;
	//sulkee tiedoston
	highscoreFile.close();
	//lataamalla tiedoston näillä parametreillä lähettää servulle highscoren.

	clear();
	//haluatko lähettää scoret servulle?
	printw("Would you like to upload score to the online scoreboard? (y/n(default))");
	char temp = getch();
	if (temp == 'y' || temp == 'Y'){

		//tee url scoreista yms.
		//php puolella $_GET
		string command = "wget \"http://34.241.121.194/typest/typest_send.php?language=";
		command += language;
		command += "&name=";
		command += currentUser.name;
		command += "&wpm=";
		command += wpmStr;
		command += "&accuracy=";
		command += accStr;
		command += "&score=";
		command += scoreStr;
		command += "&curTime=";
		//hae nykyinen aika avainta varten
		system_clock::time_point p = system_clock::now();
		time_t t = system_clock::to_time_t(p);
		string curTime = ctime(&t);
		curTime.erase(0,14);
		command += curTime;
		command += "\"";
		//lähetä wgetti
		system(command.c_str());
		//poista ladattu tiedosto
		command = "rm typest_send.php?*";
		system(command.c_str());
		refresh();
	}
	
	return 0;
}