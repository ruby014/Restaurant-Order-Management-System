/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
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

#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"

namespace seneca {
	class Menu; 

	class MenuItem {
		char* m_content; 
		unsigned int m_noOfIndents; 
		unsigned int m_indentSize; 
		int m_rownum; 
		MenuItem(const char* content, unsigned int noOfIndents, unsigned int indentSize, int rownum); 
		MenuItem(const MenuItem& src) = delete; 
		MenuItem& operator=(const MenuItem& src) = delete; 
		~MenuItem(); 
		operator bool() const; 
		std::ostream& display(std::ostream& ostr = std::cout) const;  
		friend class Menu; 
	};

	class Menu {
		// MenuItems
		MenuItem m_title;
		MenuItem m_exit;
		MenuItem m_prompt;
		// attributes 
		int m_indentNo; // changed back to int vs unsigned dt compilation warnings
		int m_indentSz; 
		int m_noOfMenuItems;
		MenuItem* menuItemPtrs[MaximumNumberOfMenuItems];
		// methods 
	public:
		Menu(const char* title, const char* exit = "Exit", int indentNo = 0, int indentSz = 3)
			: m_title(title, indentNo, indentSz, -1),
			m_exit(exit, indentNo, indentSz, 0),
			m_prompt("> ", indentNo, indentSz, -1),
			m_indentNo(indentNo),
			m_indentSz(indentSz),
			m_noOfMenuItems(0) { 
			for (int i = 0; i < (int)MaximumNumberOfMenuItems; i++) {
				menuItemPtrs[i] = nullptr; 
			}
		}; 
		Menu& operator<<(const char* newContent); 
		Menu(const Menu& src) = delete; 
		Menu& operator=(const Menu& src) = delete; 
		~Menu();
		size_t select() const; 
	};

	size_t operator<<(std::ostream& ostr, const Menu& m); 
}

#endif // !SENECA_MENU_H