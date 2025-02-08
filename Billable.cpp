/* Citation and Sources...
Final Project Milestone 3
Module: Billable
Filename: Billable.cpp 
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
#include "Utils.h"
#include "Billable.h"

namespace seneca {
	Billable::~Billable() {
		delete[] m_name; 
		m_name = nullptr; 
	}

	void Billable::price(double value) {
		m_price = value;
	}

	void Billable::name(const char* name) { 
		ut.alocpy(m_name, name);
	}

	Billable::Billable() {
		m_name = nullptr;
		m_price = 0;
	}

	void Billable::init(const Billable& src) { // mine 
		m_price = src.m_price;
		m_name = nullptr; 
		if (src.m_name != nullptr) {
			ut.alocpy(m_name, src.m_name);
		}
	}

	Billable::Billable(const Billable& src) {
		init(src); 
	}

	Billable& Billable::operator=(const Billable& src) {
		if (this != &src) {
			name(src.m_name); 
			price(src.m_price); 
		}
		return *this;
	}

	double Billable::price() const {
		return m_price; 
	}

	Billable::operator const char* () const {
		return m_name; 
	}

	double operator+(double money, const Billable& B) {
		return money + B.price();  
	}

	double& operator+=(double& money, const Billable& B) {
		return money += B.price(); 
	}

	const char* Billable::name() const{ // me 
		return m_name; 
	}
}