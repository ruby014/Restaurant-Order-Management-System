/* Citation and Sources...
Final Project Milestone 3
Module: Food
Filename: Food.cpp
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
#include <iomanip>
#include <cstring> 
#include "Food.h"
#include "Utils.h"
#include "Menu.h"
using namespace std; 

namespace seneca {
	Food::Food() {
		m_ordered = false; 
		m_child = false; 
		m_customize = nullptr; 
	}

	void Food::init(const Food& src) {
		// init of Billable attributes 
		Billable::name(src.name());
		Billable::price(src.Billable::price());
		// init of Food attributes 
		m_ordered = src.m_ordered;
		m_child = src.m_child;
		m_customize = nullptr; 
		if (src.m_customize != nullptr) {
			ut.alocpy(m_customize, src.m_customize);
		}
	}

	Food::Food(const Food& src) {
		init(src); 
	}

	Food& Food::operator=(const Food& src) {
		if (this != &src) {
			delete[] m_customize; 
			init(src); 
		}
		return *this; 
	}
	
	Food::~Food() {
		delete[] m_customize; 
		m_customize = nullptr; 
	}

	std::ostream& Food::print(std::ostream& ostr) const {
		// name 
		const char* nameToPrint = name(); 
		int nameLength = strlen(nameToPrint); 
		ostr.fill('.');
		if (nameLength < 25) {
			ostr << left << setw(28) << name(); 
		}
		// portion type 
		if (ordered() && m_child) {
			ostr << "Child";
		}
		else if (ordered() && !m_child){
			ostr << "Adult"; 
		}
		else {
			ostr << "....."; 
		}
		// price 
		ostr.fill(' '); 
		ostr.setf(ios::fixed); 
		ostr.precision(2); 
		ostr << right << setw(7) << price(); 

		if (m_customize != nullptr && &ostr == &cout) {
			ostr << " >> " << m_customize; 
		}
		return ostr; 
	}

	bool Food::order() {
		char customInstructions[30 + 1]; 
		Menu m("Food Size Selection", "Back", 3);
		m << "Adult"; 
		m << "Child"; 
		size_t selectedOption = m.select(); 
		switch (selectedOption) {
		case 1: 
			m_child = false; 
			break; 
		case 2: 
			m_child = true; 
			break; 
		default: // user hit enter or 0 
			m_ordered = false; 
			delete[] m_customize;
			m_customize = nullptr;
			return false; 
		}
		// 1 or 2 selected 
		cout << "Special instructions" << endl;
		cout << "> ";
		if (cin.peek() != '\n') {
			cin.getline(customInstructions, 31, '\n');
			cin.clear(); 
			ut.alocpy(m_customize, customInstructions);
		}
		else {
			delete[] m_customize; 
			m_customize = nullptr;
			cin.ignore();
		}
		m_ordered = true;
		return true;
	}

	bool Food::ordered() const {
		return  m_ordered; 
	}

	std::ifstream& Food::read(std::ifstream& file) {
		char name[1024]; 
		double price; 
		if (file) {
			file.getline(name, 1024, ',');
			file >> price;
			file.ignore();
			Billable::name(name); 
			Billable::price(price);
			m_child = false; 
			m_ordered = false;
			delete[] m_customize; 
			m_customize = nullptr; 
		}
		return file;
	}

	double Food::price() const {
		double price;
		price = Billable::price();
		if (ordered() && m_child) {
			return price *= 0.5; 
		}
		else {
			return price; 
		}
	}
}