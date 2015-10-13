/**********************************
 * Author: Robyn Lin
 * Date created: 11/28/14
 * Date last modified: 11/30/14
 * File name: carLot2.cpp
 *
 * Overview:
 * 	This program allows the user to choose from 4 options: 1) add a car entry, 2) display current
 * 	inventory, calculate profit for a specified month and year, or quit. This program uses 3
 * 	different classes instead of structs.
 *
 * Input:
 * 	If the user chooses 1, they enter all the information included in the Car class. If they choose
 * 	3, they enter a month and year they want to see the profit for.
 *
 * Output:
 * 	If the user chooses 2, the output should be information for all cars that have been purchased
 * 	but not sold, and a count of how many of these cars there are. The user chooses 3, the output
 * 	should be the profit for the month and year they entered.
***********************************/

#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <stdexcept>
using namespace std;

class Date
{
   private: //member variables
      int month;
      int day;
      int year;

   public:
      Date(int, int, int); //prototype
      Date()
      { month = 0; day = 0; year = 0; } //default constructor
      //accessor functions
      int getMonth()
      { return month; }
      int getDay()
      { return day; }
      int getYear()
      { return year; }
};
/****************************
 * 	Date::Date	    *
 * This is the constructor. It initializes the member variables *
****************************/
Date::Date(int monthInput, int dayInput, int yearInput)
{
   month = monthInput;
   day = dayInput;
   year = yearInput;

   if(cin.fail() || month < 1 || month > 12) //month input validation
   {
      throw invalid_argument("ERROR: The given month and day are not a valid date.");
   }
 
   if(month == 1|| month == 3 || month== 5 || month == 7 || month == 8 || month == 10 || month == 12) //day input validation
   {
      if(day < 1 || day > 31) //if day is less than 1 or greater than 31 days
	   throw invalid_argument("ERROR: The given month and day are not a valid date.");
   }

   else if(month == 4 || month == 6 || month == 9 || month == 11) 
   {
      if(day < 1 || day > 30) //if day is less than 1 or greater than 30
	   throw invalid_argument("ERROR: The given month and day are not a valid date.");
   }

   else if(month == 2)
   {
      if(day < 1 || day > 28) //if dayPurch is less than 1 or greater than 28
	   throw invalid_argument("ERROR: The given month and day are not a valid date.");
   }

}

class Car
{
   private: //member variables
      string make;
      string model;
      int year;
      Date datePurchased;
      double purchasePrice;
      bool isSold;
      Date dateSold;
      double salesPrice;

   public: //prototypes
      Car(string, string, int, Date, double, bool, Date, double);
      Car(string, string, int, Date, double, bool);
      Car(){}; //default constructor

      double getProfit();
      //accessor functions
      string getMake()
      { return make; }
      string getModel()
      { return model; }
      int getYear()
      { return year; }
      int getMonthPurch()
      { return datePurchased.getMonth(); }
      int getDayPurch()
      { return datePurchased.getDay(); }
      int getYearPurch()
      { return datePurchased.getYear(); }
      double getPurchPrice()
      { return purchasePrice; }
      bool getIsSold()
      { return isSold; }
      int getMonthSold()
      { return dateSold.getMonth(); }
      int getYearSold()
      { return dateSold.getYear(); }
      double getSalesPrice()
      { return salesPrice; }
};
/***************************
 * 	Car:Car		   *
 * This is the constructor. It initializes all member variables *
****************************/
Car::Car(string makeInput, string modelInput, int yearInput, Date datePurchInput, double purchPriceInput, bool isSoldInput, Date dateSoldInput, double salesPriceInput)
{
   make = makeInput;
   model = modelInput;
   year = yearInput;
   datePurchased = datePurchInput;
   purchasePrice = purchPriceInput;
   isSold = isSoldInput;
   dateSold = dateSoldInput;
   salesPrice = salesPriceInput;
}
/***************************
 * 	Car:Car		   *
 * This is the constructor. It initializes all member variables except the last 2 *
****************************/
Car::Car(string makeInput, string modelInput, int yearInput, Date datePurchInput, double purchPriceInput, bool isSoldInput)
{
   make = makeInput;
   model = modelInput;
   year = yearInput;
   datePurchased = datePurchInput;
   purchasePrice = purchPriceInput;
   isSold = isSoldInput;
}
/*****************************
 * 	getProfit	     *
 * This function returns the profit if isSold is true, otherwise it returns NAN *
******************************/
double Car::getProfit()
{
   double profit;
   if(getIsSold() == true)
   {
      profit=getSalesPrice()-getPurchPrice();
      return profit;
   }

   else
      return NAN;
}

class CarLot
{
   private:
      vector<Car> vehicle; //member data

   public: //prototypes
      void addCar(Car);
      void listCurrentInv(int);
      double getMonthProfit(int, int, int);
};
/*********************************
 * 	addCar			 *
 * This function adds a car's info to the vector *
*********************************/
void CarLot::addCar(Car carObj)
{
   vehicle.push_back(carObj);
}
/**********************************
 * 	listCurrentInv		  *
 * This function lists cars in current inventory *
**********************************/
void CarLot::listCurrentInv(int numEntries)
{
   int i;
   int count = 0;
  
   for(i = 0; i < numEntries; i++)
   {
	if(vehicle[i].getIsSold() == false) {
	cout << fixed << showpoint << setprecision(2);
	cout << "Make: "<< vehicle[i].getMake()<<endl;
	cout << "Model: "<< vehicle[i].getModel()<<endl;
	cout << "Year: "<< vehicle[i].getYear()<<endl;
	cout << "Month purchased: "<<vehicle[i].getMonthPurch()<<endl;
	cout << "Day purchased: "<<vehicle[i].getDayPurch()<<endl;
	cout << "Year purchased: "<<vehicle[i].getYearPurch()<<endl;
	cout << "Purchase price: "<<vehicle[i].getPurchPrice()<<endl;

	count++;
	}
   }

   cout << "The number of cars in current inventory is: "<<count<<endl;
}
/***********************************
 * 	getMonthProfit		   *
 * This function calculates the profit for a given month/year *
***********************************/
double CarLot::getMonthProfit(int monthInput, int yearInput, int numEntries)
{
   int i;
   double profit = 0;

   for(i = 0; i < numEntries; i++)
   {
	if(monthInput == vehicle[i].getMonthSold() && yearInput == vehicle[i].getYearSold())
	   profit = profit + (vehicle[i].getSalesPrice() - vehicle[i].getPurchPrice());
   }
}

int main()
{
   int choice; //stores user choice
   int numEntries = 0; //stores count of cars
   int monthProfit, yearProfit; //stores user input for option 3
   string make, model, sold; //stores user input
   int year, monthPurch, dayPurch, yearPurch, monthSold, daySold, yearSold; //stores user input
   double purchPrice, salesPrice;
   bool isSold;
   double profit; //stores result of getMonthProfit member function

   CarLot carLotObj;
   
   while(choice != 4) {
   cout << "Choose from the following 4 options: 1) Add entry, 2) List current inventory, 3) Display profit for a\n";
   cout << "month or year, 4) quit."<<endl;
   cin >> choice; //stores user input

   if(choice == 1)
   {
     //tells user what to do and stores input
     cout << "Enter the car make."<<endl;
     cin >> make;
     cout << "Enter the car model."<<endl;
     cin >> model;
     cout << "Enter the car year (4 digits)."<<endl;
     cin >> year;
     cout << "Enter the date purchased: month, day, year (year as 4 digits) on separate lines."<<endl;
     cin >> monthPurch;
     cin >> dayPurch;
     cin >> yearPurch;
        Date datePurch(monthPurch, dayPurch, yearPurch); //create Date object and pass these arguments to constructor
     cout << "Enter the purchase price."<<endl;
     cin >> purchPrice;
     cout << "Was the car sold (yes/no)?"<<endl;
     cin >> sold;
     if(sold == "yes")
        isSold = true; //car was sold
     else
        isSold = false; //car was not sold
     if(isSold == true) {
        cout << "Enter the date sold: month, day, year (year as 4 digits) on separate lines."<<endl;
        cin >> monthSold;
        cin >> daySold;
        cin >> yearSold;
        Date dateSold(monthSold, daySold, yearSold); //create another Date object and pass these arguments to constructor

        cout << "Enter the sales price."<<endl;
        cin >> salesPrice;

        Car carObj1(make, model, year, datePurch, purchPrice, isSold, dateSold, salesPrice); //call constructor obj1 
        
        carLotObj.addCar(carObj1); //call addCar member function and pass Car object as argument
     }

     else //isSold is false, means car was not sold
     {
        Car carObj2(make, model, year, datePurch, purchPrice, isSold); //call constructor obj2 to fill all member variables except last 2
        
        carLotObj.addCar(carObj2); //call addCar member function and pass Car object as argument
     }

     numEntries++; //increment number of car entries
   }

   else if(choice == 2)
   {
      carLotObj.listCurrentInv(numEntries); //call listCurrentInv member function and pass this argument
   }

   else if(choice == 3)
   {
      cout << "Enter a month."<<endl;
      cin >> monthProfit; //stores user input
      cout << "Enter a year (4 digits)."<<endl;
      cin >> yearProfit; //stores user input

      profit = carLotObj.getMonthProfit(monthProfit, yearProfit, numEntries); //call getMonthProfit member function and pass these arguments
      cout << fixed << showpoint << setprecision(2);
      cout << "The profit for this month and year is:\n";
      cout << "$" << profit <<endl; //display output
   }

   else if(choice == 4)
      break;
   }

   return 0;
}

