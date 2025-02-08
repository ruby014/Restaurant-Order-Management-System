/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.cpp
Version 1.0
Date Nov 14/24
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip> 
#include "Menu.h"
#include "constants.h"
#include "Utils.h"

using namespace std;
namespace seneca {
	MenuItem::MenuItem(const char* content, unsigned int noOfIndents, unsigned int indentSize, int rownum) {
		m_content = nullptr;
		m_noOfIndents = 0;
		m_indentSize = 0;
		m_rownum = -2;

		if (content != nullptr
			&& content[0] != '\0'
			&& !ut.isspace(content)
			&& noOfIndents <= 4
			&& noOfIndents >= 0
			&& indentSize <= 4
			&& indentSize >= 0
			&& rownum <= (int)MaximumNumberOfMenuItems) { //changed
			ut.alocpy(m_content, content);
			m_noOfIndents = noOfIndents;
			m_indentSize = indentSize;
			m_rownum = rownum;
		}
	}

	MenuItem::~MenuItem() {
		delete[] m_content; 
		m_content = nullptr; 
	}

	MenuItem::operator bool() const {
		return m_content; 
	}

	std::ostream& MenuItem::display(std::ostream& ostr) const {
		if (m_content) {
			ostr.setf(ios::left);
			int totalIndents = m_noOfIndents * m_indentSize;
			for (int i = 0; i < totalIndents; i++) {
				ostr << " ";
			}
			if (m_rownum >= 0) {
				ostr << right << setw(2) << m_rownum << "- ";
			}
			const char* contentWithNoSpace = m_content;
			while (contentWithNoSpace && isspace(*contentWithNoSpace)) {
				contentWithNoSpace++;
			}
			ostr << contentWithNoSpace; 
			if (m_rownum != -1) cout << endl; 
			ostr.unsetf(ios::left);
		}
		return ostr;
	}

	// MS2 funcs added 
	Menu& Menu::operator<<(const char* newContent) {
		if (m_noOfMenuItems < (int)MaximumNumberOfMenuItems) {
			MenuItem* newMenuItem = new MenuItem(newContent, m_indentNo, m_indentSz, m_noOfMenuItems + 1);
			menuItemPtrs[m_noOfMenuItems] = newMenuItem; 
			m_noOfMenuItems += 1;
		}
		return *this; 
	}

	Menu::~Menu() {
		for (int i = 0; i < m_noOfMenuItems; i++) {
			if (menuItemPtrs[i] != nullptr) {
				delete menuItemPtrs[i];
				menuItemPtrs[i] = nullptr; 
			}
		}
	}

	size_t Menu::select() const {
		size_t selectedNo; 
		if (m_title) { 
			m_title.display() << endl;
		}
		for (int i = 0; i < m_noOfMenuItems; i++) {
			menuItemPtrs[i]->display();
		}
		m_exit.display(); 
		m_prompt.display(); 
		selectedNo = ut.getInt(m_exit.m_rownum, m_noOfMenuItems);
		return selectedNo; 
	}

	size_t operator<<(std::ostream& ostr, const Menu& m) {
		size_t userSelection; 
		if (&ostr == &cout) {
			userSelection = m.select(); 
			return userSelection; 
		}
		else {
			return 0; 
		}
	}
}