#include <iostream>
#include <ncurses.h>
#include <string>
#include "string.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#include "TypestNetworking.h"

using namespace std;
using namespace chrono;

int GetWebHighscores(){
	clear();
	string line;
	//hakee servulta highscoret
	system("wget http://34.241.121.194/typest/typest_get.php");
	//printtaa
	printw("                   -------------------------------\n");
	printw("                   |     TOP 10 ONLINE SCORES    |\n");
	printw("------------------------------------------------------------------------------------\n");
	printw("| #   |  Language  |   Name   | WPM |  Accuracy  |  Score  |   Timestamp           |\n");
	printw("------------------------------------------------------------------------------------\n");
	ifstream scoreFile ("typest_get.php");
	for (int i = 0; !scoreFile.eof() && i < 10; i++) {
		printw("| ");
		printw("%i", i+1);
		if(i == 9){
		printw(". |");
		}else {
		printw(".  |");	
		}

		getline(scoreFile,line);
		printw(line.c_str());
		printw(" |\n");
	}
	printw("------------------------------------------------------------------------------------");
	printw("\nPress any key to get back to menu.\n");
	//sulkee tiedoston
	scoreFile.close();
	//poistaa haetun tiedoston.
	system("rm typest_get.php");
	refresh();
	getch();
	//takaisin menuun
	Menu();
}

int SendWebHighscores(string language, string name, string wpm, string acc, string score) {
    //tee url scoreista yms.
		//php puolella $_GET
		string command = "wget \"http://34.241.121.194/typest/typest_send.php?language=";
		command += language;
		command += "&name=";
		command += name;
		command += "&wpm=";
		command += wpm;
		command += "&accuracy=";
		command += acc;
		command += "&score=";
		command += score;
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
        return 0;
}
