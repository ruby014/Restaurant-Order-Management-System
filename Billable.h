/* Citation and Sources...
Final Project Milestone 3
Module: Billable
Filename: Billable.h 
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
#ifndef BILLABLE_H
#define BILLABLE_H

namespace seneca {
	class Billable {
		char* m_name;
		double m_price;
		void init(const Billable& src); // me 
	protected:
		void price(double value);
		void name(const char* name);
		const char* name() const; // me 
	public:
		Billable();
		Billable(const Billable& src);
		Billable& operator=(const Billable& src);
		virtual ~Billable(); 
		// virtual methods 
		virtual double price() const; 
		// pure virtual methods 
		virtual std::ostream& print(std::ostream& ostr = std::cout) const = 0;
		virtual bool order() = 0;
		virtual bool ordered() const = 0;
		virtual std::ifstream& read(std::ifstream& file) = 0;
		// conversion operator 
		operator const char* () const; 
	};
	// operator overloads 
	double operator+(double money, const Billable& B);
	double& operator+=(double& money, const Billable& B);
}
#endif 