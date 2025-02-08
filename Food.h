/* Citation and Sources...
Final Project Milestone 3
Module: Food
Filename: Food.h
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
#ifndef FOOD_H
#define FOOD_H
#include "Billable.h"
namespace seneca {
	class Food : public Billable {
		bool m_ordered; 
		bool m_child; 
		char* m_customize; 
		void init(const Food& src); // mine 
	public: 
		Food(); 
		Food(const Food& src);
		Food& operator=(const Food& src);
		~Food(); 
		std::ostream& print(std::ostream& ostr = std::cout) const;
		bool order(); 
		bool ordered() const;
		std::ifstream& read(std::ifstream& file);
		double price() const; 
	};
}

#endif 