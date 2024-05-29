#pragma once
#include "classes_base.h"


template<typename T>
void show(std::vector<T> v) {
    for (auto e : v)
        std::cout << e << "; ";
    std::cout << "\n";
};

std::vector<std::string> explode(char sep, std::string const& s) {
    std::vector<std::string> result;
    std::stringstream iss(s);
    for (std::string token; getline(iss, token, sep); ) {
        result.push_back(token);
    }
    return result;
};

std::string implode(std::string sep, std::vector<std::string> v) {
    std::string result = "";
    for (auto e : v) {
        result += e;
        result += sep; 
    }
    return result;
};

void Frame_IO_Buffer::Update_OutputBuffer() {
	O_Fbuffer = implode("\n",W_Fbuffer);
};

Base_Game_Handler::Base_Game_Handler(unsigned int input_rounds) {
	p1score = new unsigned int;
	p2score = new unsigned int;
	rounds = new unsigned int;
	*rounds = input_rounds;
	game_running = true;
};

Base_Game_Handler::~Base_Game_Handler(){
	delete p1score;
	delete p2score;
};

void PlayerList::inputPlayersFromCSV(){
	std::string inputData;
    std::vector<std::string> vInput;
    while (std::getline(PLfh.strmFH, inputData)) {
    if (inputData.size()) {
    	vInput = explode(';', inputData);
        //show(vInput);
        playerlist.push_back(new Player(std::stoi(vInput[0]), vInput[1], std::stoi(vInput[2])));
    	}
    }
};

void Timer::Tick() {
	// Maintain designated frequency of 5 Hz (200 ms per frame) 
    // 1 sekunda to 5 klatek
    // 16.7 ms to będzie około 60 klatek na sekunde 
	a = std::chrono::system_clock::now();
    work_time = a - b;
		
   if (work_time.count() < 33.3)
   {
		std::chrono::duration<double, std::milli> delta_ms(33.3 - work_time.count());
        auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
        std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
   }
   
   b = std::chrono::system_clock::now();
   sleep_time = b - a;
   #ifdef __linux__ 
    	std::system("clear");
   #elif _WIN32
    	std::system("cls");

   #endif
};


