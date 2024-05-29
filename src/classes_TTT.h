#pragma once
#include "functions_base.h"

class TTT_Handler: private Base_Game_Handler {
//public:
	
private:
	std::vector<std::string> board = {"-", "-", "-", "-", "-", "-", "-", "-", "-"};
	std::string b_sep = "|";
	unsigned int position;
	TTT_Handler(unsigned int input_rounds) : Base_Game_Handler(input_rounds) {
	
	};
	void ScoreHandler() override { //define the virtual class overwrite here
		*p1score += 1;
	};
};
