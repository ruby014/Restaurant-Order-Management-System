/* Citation and Sources...
Final Project Milestone 5
Module: main
Filename: main.cpp
Version 1.0
Date Nov 27/24
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
#include "Menu.h" 
#include "Ordering.h"

using namespace std; 
using namespace seneca; 

    int main() {
        size_t appSel{}, ordSel{};
        Menu appMenu("Seneca Restaurant ", "End Program");
        appMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
        Menu orderMenu("Order Menu", "Back to main menu", 1);
        orderMenu << "Food" << "Drink";
        Menu confirmation("You have bills that are not saved, are you sue you want to exit?", "No"); 
        confirmation << "Yes";

        size_t end = -2; // flag to end program 

        // Loading Data Files 
        Ordering order("drinks.csv", "foods.csv"); 
        if (!order) {
            cout << "Failed to open data files or the data files are corrupted!" << endl; 
        }
        else {
            do {
                switch (appSel = appMenu.select()) {
                case 1:
                    do {
                        switch (ordSel = orderMenu.select()) {
                        case 1:
                            order.orderFood(); 
                            break; 
                        case 2:
                            order.orderDrink(); 
                            break;
                        }
                    } while (ordSel);
                    break;
                case 2:
                    order.printBill(cout);
                    break;
                case 3:
                    order.resetBill(); 
                    break;
                case 4:
                    order.listFoods(); 
                    break; 
                case 5:
                    order.ListDrinks(); 
                    break;
                case 0: 
                    if (order.hasUnsavedBill()) {
                        appSel = confirmation.select(); 
                        if (appSel == 1) {
                            appSel = -2; // will be flag to end program 
                        }
                    }
                    else {
                        appSel = end; 
                    }
                    break; 
                }
            } while (appSel != end);
        }
        return 0; 
    }

