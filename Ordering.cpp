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
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Ordering.h"
#include "Menu.h"
#include "Billable.h"
#include "Utils.h"

using namespace std; 
namespace seneca {
	void Ordering::printTitle(std::ostream& ostr) const {
		ostr << "Bill # "; 
		if (m_billNo < 10) {
			ostr << "00" << m_billNo + 1 << " ";
		}
		else if (m_billNo < 100) { 
			ostr << "0" << m_billNo + 1 << " ";
		}
		ostr << setw(29) << setfill('=') << "" << endl;
	}

	void Ordering::printTotal(std::ostream& ostr, double total) const {
		double tax = total * Tax;
		double taxedTotal = total + tax;
		ostr << setw(27) << "Total:" << setw(13) << total << endl;
		ostr << setw(25) << "Tax:" << setw(15) << tax << endl;
		ostr << setw(31) << "Total+Tax:" << setw(9) << taxedTotal << endl;
		for (int i = 0; i < 40; i++) {
			ostr << "=";
		}
		ostr << endl;
	}

	size_t Ordering::countRecords(const char* file) const {
		size_t noOfRecords = 0; 
		ifstream fin(file); 
		if (fin.is_open()) {
			while (!fin.fail()) {
				if (fin.get() == '\n') {
					noOfRecords++; 
				}
			}
		}
		return noOfRecords;
	}

	Ordering::Ordering(const char* drinkFileName, const char* foodFileName) {
		// intialize attributes 
		m_foodCounter = 0; 
		m_drinkCounter = 0; 
		m_billableCounter = 0; 
		m_billNo = 0; 
		// step 1: count records 
		size_t noDrinkRecords = countRecords(drinkFileName); 
		size_t noFoodRecords = countRecords(foodFileName);
		// step 2: open files to read 
		ifstream drinkFile(drinkFileName); 
		ifstream foodFile(foodFileName); 
		// step 3: dynamic array allocation 
		foodPtr = new Food[noFoodRecords]; 
		drinkPtr = new Drink[noDrinkRecords]; 
		// step 4: reading data 
		size_t drinkReads = 0; 
		size_t foodReads = 0; 
		if (drinkFile.is_open() && foodFile.is_open()) {
			for (unsigned int i = 0; i < noDrinkRecords; i++) {
				if (drinkPtr[i].read(drinkFile)) {
					drinkReads++;
				}
			}
			for (unsigned int i = 0; i < noFoodRecords; i++) {
				if (foodPtr[i].read(foodFile)) {
					foodReads++;
				}
			}
		}

		if (drinkReads == 0 
			|| foodReads == 0 
			|| drinkReads != noDrinkRecords 
			|| foodReads != noFoodRecords) {
			delete[] foodPtr;
			delete[] drinkPtr;
			foodPtr = nullptr;
			drinkPtr = nullptr;
		}
		else {
			m_foodCounter = foodReads;
			m_drinkCounter = drinkReads;
		}
	}

	Ordering::~Ordering() {
		delete[] foodPtr; 
		delete[] drinkPtr; 
		foodPtr = nullptr;
		drinkPtr = nullptr;

		for (unsigned int i = 0; i < m_billableCounter; i++) {
			delete billPtr[i]; 
		}
	}

	Ordering::operator bool() const {
		return drinkPtr != nullptr && foodPtr != nullptr ? true : false; 
	}

	unsigned int Ordering::noOfBillItems() const {
		return m_billableCounter; 
	}

	bool Ordering::hasUnsavedBill() const {
		return m_billableCounter > 0 ? true : false; 
	}
	
	void Ordering::listFoods() const {
		cout << "List Of Avaiable Meals" << endl; 
		cout << "========================================" << endl; 
		for (unsigned int i = 0; i < m_foodCounter; i++) {
			foodPtr[i].print();
			cout << endl;
		}
		cout << "========================================" << endl; 
	}

	void Ordering::ListDrinks() const {
		cout << "List Of Avaiable Drinks" << endl;
		cout << "========================================" << endl;
		for (unsigned int i = 0; i < m_drinkCounter; i++) {
		drinkPtr[i].print();
			cout << endl;
		}
		cout << "========================================" << endl;
	}

	void Ordering::orderFood() {
		Menu m("Food Menu", "Back to Order", 2);
		for (unsigned int i = 0; i < m_foodCounter; i++) {
			m << foodPtr[i]; 
		}
		size_t selection = m.select(); 
		bool ordered = 0; 
		if (selection != 0) {
			Food* f1 = new Food(foodPtr[selection - 1]); 
			billPtr[m_billableCounter] = f1;
			ordered = billPtr[m_billableCounter]->order(); 

			if (ordered) {
				m_billableCounter++; 
			}
			else {
				delete billPtr[m_billableCounter];
				billPtr[m_billableCounter] = nullptr; 
			}
		}
	}

	void Ordering::orderDrink() {
		Menu m("Drink Menu", "Back to Order", 2);
		for (unsigned int i = 0; i < m_drinkCounter; i++) {
			m << drinkPtr[i];
		}
		size_t selection = m.select();
		bool ordered = 0;
		if (selection != 0) {
			Drink* d1 = new Drink(drinkPtr[selection - 1]); 
			billPtr[m_billableCounter] = d1; 
			ordered = billPtr[m_billableCounter]->order();
			if (ordered) {
				m_billableCounter++;
			}
			else {
				delete billPtr[m_billableCounter];
				billPtr[m_billableCounter] = nullptr;
			}
		}
	}

	void Ordering::printBill(std::ostream& ostr) const {
		double total = 0;
		printTitle(ostr); 
		for (unsigned int i = 0; i < m_billableCounter; i++) {
			billPtr[i]->print(ostr); 
			total += billPtr[i]->price(); 
			ostr << endl; 
		}
		printTotal(ostr, total); 
	}

	void Ordering::resetBill() {
		char filename[100]; 
		ut.makeBillFileName(filename, m_billNo + 1);
		ofstream f(filename); 

		if (f.is_open()) {
			cout << "Saved bill number " << m_billNo + 1 << endl; 
			cout << "Starting bill number " << m_billNo + 2 << endl; 
			printBill(f); 
			f.close();
		}
		for (unsigned int i = 0; i < m_billableCounter; i++) {
			delete billPtr[i]; 
			billPtr[i] = nullptr; 
		}

		m_billNo += 1; 
		m_billableCounter = 0; 
	}
}