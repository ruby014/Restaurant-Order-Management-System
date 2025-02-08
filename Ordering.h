/* Citation and Sources...
Final Project Milestone 4
Module: Ordering
Filename: Ordering.h
Version 1.0
Date Nov 26/24
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
#ifndef ORDERING_H
#define ORDERING_h 
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"

namespace seneca {
	class Ordering {
		unsigned int m_foodCounter; 
		unsigned int m_drinkCounter; 
		unsigned int m_billableCounter; 
		unsigned int m_billNo; 
		Food* foodPtr; 
		Drink* drinkPtr; 
		Billable* billPtr[MaximumNumberOfMenuItems]; 
		// private methods 
		void printTitle(std::ostream& ostr) const; 
		void printTotal(std::ostream& ostr, double total) const; 
		size_t countRecords(const char* file) const; 
	public: 
		// Constructors and Destructors 
		Ordering(const char* drinkFileName, const char* FoodFileName); 
		~Ordering(); 
		// queries 
		operator bool() const; 
		unsigned int noOfBillItems() const;
		bool hasUnsavedBill() const;
		// methods to be called in the main application's menu 
		void listFoods() const; 
		void ListDrinks() const; 
		void orderFood(); 
		void orderDrink();
		void printBill(std::ostream& ostr) const; 
		void resetBill(); 
	};
}

#endif 