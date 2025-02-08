/* Citation and Sources...
Final Project Milestone 3
Module: Drink
Filename: Drink.cpp
Version 1.0
Date Nov 19/24
Author	Ruchelle Baybayan
Revision History
-----------------------------------------------------------
Date      Reason
2024/?/?  Preliminary release
2024/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <fstream> 
#include <iomanip> // for setw
#include <cstring> // for valgrind w strlen 
#include "Drink.h"
#include "Utils.h"
#include "Menu.h"
using namespace std; 

namespace seneca {
	std::ostream& Drink::print(std::ostream& ostr) const {
		// name  
		const char* nameToPrint = name(); 
		int nameLength = strlen(nameToPrint); 
		ostr.fill('.'); 
		if (nameLength < 25) { // up to 25 chars only 
			ostr << left << setw(28) << nameToPrint; 
		}
		// size 
		switch (m_size) {
		case 'S':
			ostr << "SML..";
			break;
		case 'M':
			ostr << "MID..";
			break;
		case 'L':
			ostr << "LRG..";
			break;
		case 'X':
			ostr << "XLR..";
			break;
		default: 
			ostr << ".....";
		}
		// price 
		ostr.fill(' '); 
		ostr.setf(ios::fixed); 
		ostr.precision(2); 
		ostr << right << setw(7) << Drink::price();
		return ostr;
	}

	bool Drink::order() {
		Menu m("Drink Size Selection", "Back", 3);
		m << "Small"; 
		m << "Medium"; 
		m << "Larg"; 
		m << "Extra Large"; 
		size_t selectedDrink; 
		selectedDrink = m.select(); 
		switch (selectedDrink) {
		case 1: 
			m_size = 'S';
			break;
		case 2: 
			m_size = 'M'; 
			break;
		case 3: 
			m_size = 'L'; 
			break; 
		case 4: 
			m_size = 'X'; 
			break; 
		default: 
			m_size = 'O'; 
			break; 
		}

		if (m_size != 'O') { // user selected a valid option 
			return true;
		}
		else {
			return false;
		}
	}

	bool Drink::ordered() const {
		return m_size != 'O' ? true : false;
	}

	std::ifstream& Drink::read(std::ifstream& file) {
		char name[1024]; 
		double price = 0; 
		if (file) {
			file.getline(name, 1024, ','); 
			file >> price;
			file.ignore();
			Billable::name(name);
			Billable::price(price); 
			m_size = 'O'; 
		}
		return file; 
	}

	double Drink::price() const{
		double price; 
		price = Billable::price(); 
		if (m_size == 'S') {
			price /= 2; 
		}
		else if (m_size == 'M') {
			price *= 0.75; 
		}
		else if (m_size == 'X') {
			price *= 1.5; 
		}
		// if its L or not ordered aka empty state, it will just be price 
		return price; 
	}
}