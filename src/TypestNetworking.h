//kaikki definet
#ifndef TypestNetworking
#include <iostream>
#include <ncurses.h>
#include <string>
#include "string.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>
#define TypestNetworking
#include <iostream>
#include <string>
#include "string.h"
int GetWebHighscores();
int StartTypingTest();
int Restart(void);
int Wordlist(char lang);
int Menu(void);
int Highscores(void);
int writeHighscore(char lang);
int SendWebHighscores(std::string language, std::string name, std::string wpm, std::string acc, std::string score);
#endif