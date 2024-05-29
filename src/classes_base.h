#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <algorithm>

#ifdef __linux__
#include "linux_kbhit.h"
#elif _WIN32
#include <windows.h>
#endif

/*
#ifdef __linux__ 
    //linux code goes here
#elif _WIN32
    // windows code goes here
#else

#endif
// Okay I will need this to support both Windows and Linux
*/

// Implement a leaderboard and a player profile system

class Key_IO_Buffer {
private:
    char IBuffer; //The input buffer
    bool IStatus; //Check if the user is inputing any
    unsigned int IDelay;
public:
	char getKey();
};

class Frame_IO_Buffer {
private:
    std::string O_Fbuffer; // The output buffer, it gets written to by overwriting the data in it with the data from the work frame buffer.
    std::vector<std::string> W_Fbuffer; // Work buffer for the output buffer
public:
	void Update_WorkBuffer(unsigned int position, std::string input_string) { W_Fbuffer[position] = input_string; };
	void Push_WorkBuffer(std::string input_string) { W_Fbuffer.push_back(input_string); };
	void Clear_WorkBuffer() { W_Fbuffer.clear(); };
	void Update_OutputBuffer();
	std::string Return_OutputBuffer() { return O_Fbuffer; };
};

// gonna use printf for faster output, but I will need to convert c++ strings to c strings. c strings being "char *, also known as a table of char, with a null terminator at the end."
// Area of 80 characters horizontally by 30 vertically in my personal terminal

class Timer {
public:
	std::chrono::system_clock::time_point a, b = std::chrono::system_clock::now();
	std::chrono::duration<double, std::milli> work_time;
	std::chrono::duration<double, std::milli> sleep_time;
	void Tick();
};


class Player {
public:
	static size_t amount;
	Player() { amount++; id = amount; };
	/*
	Player(std::string i_username) {
		amount++;
		id = amount;
		username = i_username;
	};
	*/
	Player(std::size_t i_id,std::string i_username, unsigned int i_score) : username(i_username), my_score(i_score) {
		amount++;
		if (i_id == 0) {
			id = amount;
		}
		else {
			id = i_id;
		}
	};
	std::string getUsername() { return username; };
	std::size_t getId() { return id; } 
	std::string getData() {
        return std::to_string(id) + ";" + username + ";" + std::to_string(my_score);
    }
    bool compareIDs(const Player & l, const Player & r)
	{
    	return l.id < r.id;
	};

	bool compareScoress(const Player & l, const Player & r)
	{
    	return l.my_score < r.my_score;
	};
	bool operator ==( const Player & p )
	{
    	if(( this->id == p.id ) && ( this->username == p.username ) && ( this->my_score == p.my_score ) )
    	     return true;
    	else
    	     return false;
	}
	Player & operator +=(unsigned int added_score)
	{
		this->my_score += added_score;
		return * this;
	}
	Player & operator -=(unsigned int subtracted_score)
	{
		this->my_score -= subtracted_score;
		return * this;
	}
private:
	std::size_t id;
	std::string username;
	unsigned int my_score;
};

size_t Player::amount = 0;

class FileHandler {
public:
    void openFHStream(std::string filename, std::ios::openmode current_mode) {
        strmFH.open(filename, current_mode);
    }

    void closeFHStream() {
        strmFH.close();
    }
    
    std::fstream strmFH;
};

class PlayerList {
private:
	std::vector<Player*> playerlist;
	FileHandler PLfh;
public:
	void addPlayer(Player* p) {
        playerlist.push_back(p);
    }
    void clearPList() {
        playerlist.clear();
    }
    std::vector<Player* > returnPList() {
        return playerlist;
    }
    void outputPlayersCSV() {
        for (auto p : playerlist) {
            PLfh.strmFH << p->getData() << std::endl;
        }
    }

    void inputPlayersFromCSV();
};

class Base_Game_Handler {
public:
	unsigned int * p1score;
	unsigned int * p2score;
	unsigned int * rounds;
	bool game_running;
	virtual void ScoreHandler() = 0; 
	Base_Game_Handler(unsigned int input_rounds);
	~Base_Game_Handler();
};



class Program_Controller {
public:
	bool running = true; //If true then the program is running.
	std::string p_status = "menu";
	Timer p_timer;
	Frame_IO_Buffer p_fbuffer;
	Key_IO_Buffer p_ibuffer;
};
