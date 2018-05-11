#include <iostream>
#include<fstream>
#include <string>
#include <Windows.h>
using namespace std;

void display_menu();
void add_income();
void add_expense();
void display_recurring_costs();
void add_recurring_expense();
void display_income();
void display_expenses_history();
void edit();
void delete_value();
void add_recurring_category();
void quick_review();
void detailed_review();
void date_range_report();
void remaining_days();

int main()
{
	system("title Budget tracker project");

	display_menu();

	int DisplayChoice;
	cin >> DisplayChoice;

	switch (DisplayChoice)
	{
	case 1:
		add_income();

	case 2:
		add_expense();

	case 3:
		display_income();

	case 4:
		display_recurring_costs();

	case 5:
		add_recurring_expense();

	case 6:
		edit();
		break;

	case 7:
		delete_value();
		break;

	case 8:
		quick_review();
		system("pause");
		system("cls");
		main();
		break;

	case 9:
		detailed_review();
		break;

	case 10:
		date_range_report();
		break;

	case 11:
		display_expenses_history();

	case 12:
		add_recurring_category();

	case 99:
		remaining_days();
		break;

	}


	system("pause");
	return 0;
}

void display_menu()
{
	cout << "Welcome to budget tracker project beta version (choose the a number to proceed)" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "1.Add income." << endl;
	cout << "2.Add expense." << endl;
	cout << "3.Display income history." << endl;
	cout << "4.Display recurring costs." << endl;
	cout << "5.Add recurring costs." << endl;
	cout << "6.Edit value" << endl;
	cout << "7.Delete value." << endl;
	cout << "8.Quick review." << endl;
	cout << "9.Detailed review" << endl;
	cout << "10.Date range report." << endl;
	cout << "11.Display expenses history." << endl;
	cout << "12.Add recurring category" << endl;
}

void add_expense()
{
	system("cls");

	SYSTEMTIME time;
	GetLocalTime(&time);
	string date = to_string(time.wDay) + ' ' + to_string(time.wMonth) + ' ' + to_string(time.wYear);

	double expense, oldValue, currentValue, totalExpense = 0;
	char choice = 'y';
	string note;

	ofstream writeExpense("expense history.txt", ios::app);

	while (choice == 'y' || choice == 'Y')
	{
		cout << "Enter your expense: ";
		cin >> expense;
		cout << "Enter note: ";
		cin >> note;

		totalExpense += expense;

		writeExpense << date << endl << expense << endl << note << endl;

		cout << "Do you want to add new expense? (y/n): ";
		cin >> choice;
		system("cls");
	}

	writeExpense.close();

	cout << "Total expenses added: " << totalExpense << endl;

	ifstream readIncome("income value.txt");
	readIncome >> oldValue;
	readIncome.close();

	currentValue = oldValue - totalExpense;

	ofstream writeIncome("income value.txt");
	writeIncome << currentValue;
	writeIncome.close();

	cout << "Income value: " << currentValue << endl;
	main();

}

void display_recurring_costs()
{
	system("cls");
	int cateNumber;
	string Cate, subCate;

	ifstream Dispaly_Categories;
	Dispaly_Categories.open("MainCategories.txt");
	while (Dispaly_Categories >> cateNumber >>  Cate)
	{
		cout << cateNumber << '-' <<  Cate << endl;
	}
	cout << endl << "-----------------------" << endl;
	Dispaly_Categories.close();

	string choice;
	cout << "Please choose main category: ";
	cin >> choice;

	system("cls");
	string fileName = choice.append(".txt");

	cout << endl << "This is the Sub Categoreis:" << endl;
	cout << "-------------------------------" << endl;
	Dispaly_Categories.open(fileName);
	int index;
	while (Dispaly_Categories >> index >> subCate)
	{
		cout << index << '-' << subCate << endl;
	}
	cout << endl << "---------------------------------" << endl;
	Dispaly_Categories.close();

	system("pause");
	system("cls");
	main();
}

void add_income()
{
	system("cls");

	SYSTEMTIME time;
	GetLocalTime(&time);
	string date = to_string(time.wDay) + ' ' + to_string(time.wMonth) + ' ' + to_string(time.wYear);

	//Enter the value
	double income_value, old, the_new;
	char answer = 'y';
	string source;
	while (answer == 'y' || answer == 'Y') {

		cout << "Enter Income value: ";
		cin >> income_value;
		cout << "Enter Income Source: ";
		cin >> source;
		ofstream history("income history.txt", ios::app);
		history << date << '\n' << income_value << '\n' << source << endl;
		history.close();
		ifstream current_value("income value.txt");
		if (current_value.is_open())
		{
			current_value >> old;
			current_value.close();
			the_new = old + income_value;
			ofstream new_current_value("income value.txt");
			new_current_value << the_new;
			new_current_value.close();
			cout << "Your current money is: " << the_new << endl;
		}
		else
		{
			cout << "Your current money is: " << income_value << endl;
			ofstream intial("income value.txt");
			intial << income_value;
		}
		cout << "...................................................\nDO you want to continue (y or n )";
		cin >> answer;
		system("cls");
	}
	main();
}

void add_recurring_expense()
{
	system("cls");

	SYSTEMTIME time;
	GetLocalTime(&time);
	string date = to_string(time.wDay) + ' ' + to_string(time.wMonth) + ' ' + to_string(time.wYear);

	string Cate, subCate;
	int index1;
	ifstream Dispaly_Categories;
	Dispaly_Categories.open("MainCategories.txt");
	while (Dispaly_Categories >> index1 >> Cate)
	{
		cout << index1 << '-' << Cate << endl;
	}
	cout << endl << "-----------------------" << endl;
	Dispaly_Categories.close();
	string choice;
	cout << "Please choose main category: ";
	cin >> choice;
	system("cls");
	string fileName = choice.append(".txt");

	cout << endl << "This is the Sub Categoreis:" << endl;
	cout << "-------------------------------" << endl;
	Dispaly_Categories.open(fileName);
	int index;
	while (Dispaly_Categories >> index >> subCate)
	{
		cout << index << '-' << subCate << endl;
	}
	cout << endl << "---------------------------------" << endl;
	Dispaly_Categories.close();

	cout << "Choose what you want to add to recurring cost: ";
	int recurringChoice;
	cin >> recurringChoice;

	Dispaly_Categories.open(fileName);

	string catchLine, readLine;
	int catchIndex;

	while (Dispaly_Categories >> catchIndex >> readLine)
	{
		if (catchIndex == recurringChoice)
		{
			catchLine = readLine;
			break;
		}
	}

	cout << "Enter your cost: ";
	double recCost;
	cin >> recCost;

	ofstream recurringHistory("recurring history.txt", ios::app);
	recurringHistory << date << endl << recCost << endl << catchLine << endl;
	recurringHistory.close();

	char again;
	cout << "Want to add new recurring cost? (y/n): ";
	cin >> again;
	if (again == 'y')
	{
		add_recurring_expense();
	}
	else
	{
		system("cls");
		main();
	}



}

void display_expenses_history()
{
	system("cls");
	int days, months, years , index = 1;
	double cost;
	string note;

	ifstream expensesReader("expense history.txt");

	while (expensesReader >> days >> months >> years >> cost >> note)
	{
		cout << index++ << '.' << cost << '\t' << note << endl;
	}

	expensesReader.close();

	system("pause");
	system("cls");
	main();
}

void edit()
{
	system("cls");

	cout << "Choose what you want to edit:" << endl;
	cout << "-----------------------------" << endl;
	cout << "1.Edit expenses." << endl;
	cout << "2.Edit recurring cost." << endl;
	cout << "3.Edit income value." << endl;

	int choice;
	cout << "Your choice is: ";
	cin >> choice;

	int days, months, years, index = 1;
	double cost;
	string note;

	if (choice == 1)
	{
		system("cls");
		ifstream expensesReader("expense history.txt");

		while (expensesReader >> days >> months >> years >> cost >> note)
		{
			cout << index++ << '.' << cost << '\t' << note << endl;
		}

		expensesReader.close();

		cout << "Enter the index you want to edit: " << endl;
		int editIndex;
		cin >> editIndex;

		ifstream reader("expense history.txt");
		ofstream writer("dataHolder.txt");
		int whileIndex = 1;
		double newCost;
		string newNote;
		while (reader >> days >> months >> years >> cost >> note)
		{
			if (whileIndex != editIndex)
			{
				writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			else
			{
				cout << "Enter your New Cost: " << endl;
				cin >> newCost;
				cout << "Enter The Note: " << endl;
				cin >> newNote;

				writer << days << ' ' << months << ' ' << years << endl << newCost << endl << newNote << endl;

			}
			whileIndex++;
		}
		writer.close();
		reader.close();

		ifstream copy("dataHolder.txt");
		ofstream paste("expense history.txt");
		while (copy >> days >> months >> years >> cost >> note)
		{
			paste << days << ' ' << months << ' ' << years << endl << cost << ' ' << note << endl;
		}
		copy.close();
		paste.close();
		cout << "Your value is Edited successfully" << endl;
		system("pause");
		system("cls");
		display_expenses_history();
	}
	else if (choice == 2)
	{
		system("cls");
		ifstream expensesReader("recurring history.txt");

		while (expensesReader >> days >> months >> years >> cost >> note)
		{
			cout << index++ << '.' << cost << '\t' << note << endl;
		}

		expensesReader.close();

		cout << "Enter the index you want to edit: " << endl;
		int editIndex;
		cin >> editIndex;

		ifstream reader("recurring history.txt");
		ofstream writer("dataHolder.txt");
		int whileIndex = 1;
		double newCost;
		string newNote;
		while (reader >> days >> months >> years >> cost >> note)
		{
			if (whileIndex != editIndex)
			{
				writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			else
			{
				cout << "Enter your New Cost: " << endl;
				cin >> newCost;
				writer << days << ' ' << months << ' ' << years << endl << newCost << endl << note << endl;

			}
			whileIndex++;
		}
		writer.close();
		reader.close();

		ifstream copy("dataHolder.txt");
		ofstream paste("recurring history.txt");
		while (copy >> days >> months >> years >> cost >> note)
		{
			paste << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
		}
		copy.close();
		paste.close();
		cout << "Your value is Edited successfully" << endl;
	}
	else if (choice == 3)
	{
		system("cls");
		cout << "choose" << endl;
		cout << "1.Edit Incomr history" << endl;
		cout << "2.Edit Income value." << endl;

		int incomeChoice;
		cin >> incomeChoice;

		if (incomeChoice == 1)
		{
			system("cls");
			ifstream expensesReader("income history.txt");

			while (expensesReader >> days >> months >> years >> cost >> note)
			{
				cout << index++ << '.' << cost << '\t' << note << endl;
			}

			expensesReader.close();

			cout << "Enter the index you want to edit: " << endl;
			int editIndex;
			cin >> editIndex;

			ifstream reader("income history.txt");
			ofstream writer("dataHolder.txt");
			int whileIndex = 1;
			double newCost;
			string newNote;
			while (reader >> days >> months >> years >> cost >> note)
			{
				if (whileIndex != editIndex)
				{
					writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
				}
				else
				{
					cout << "Enter your New income: " << endl;
					cin >> newCost;
					cout << "Enter The source: " << endl;
					cin >> newNote;

					writer << days << ' ' << months << ' ' << years << endl << newCost << endl << newNote << endl;

				}
				whileIndex++;
			}
			writer.close();
			reader.close();

			ifstream copy("dataHolder.txt");
			ofstream paste("income history.txt");
			while (copy >> days >> months >> years >> cost >> note)
			{
				paste << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			copy.close();
			paste.close();
			cout << "Your income is Edited successfully" << endl;
		}
		else if (incomeChoice == 2)
		{
			system("cls");
			double oldValue, newValue;
			ifstream incomeReader("income value.txt");
			incomeReader >> oldValue;
			incomeReader.close();
			cout << "Your current income is: ";
			cout << oldValue << endl;
			cout << "----------" << endl;
			cout << "Enter your new income value: ";
			cin >> newValue;
			ofstream incomeWriter("income value.txt");
			incomeWriter << newValue;
			incomeWriter.close();

			ofstream incomeClear("income history.txt");
			incomeClear.clear();
			incomeClear.close();
		}
	}
	system("pause");
	system("cls");
	main();
}

void delete_value()
{
	system("cls");

	cout << "Choose what you want to edit:" << endl;
	cout << "-----------------------------" << endl;
	cout << "1.Delete expenses." << endl;
	cout << "2.Delete recurring cost." << endl;
	cout << "3.Delete income value." << endl;

	int choice;
	cout << "Your choice is: ";
	cin >> choice;

	int days, months, years, index = 1;
	double cost;
	string note;

	if (choice == 1)
	{
		system("cls");
		ifstream expensesReader("expense history.txt");

		while (expensesReader >> days >> months >> years >> cost >> note)
		{
			cout << index++ << '.' << cost << '\t' << note << endl;
		}

		expensesReader.close();

		cout << "Enter the index you want to delete: " << endl;
		int editIndex;
		cin >> editIndex;

		ifstream reader("expense history.txt");
		ofstream writer("dataHolder.txt");
		int whileIndex = 1;
		double newCost;
		string newNote;
		while (reader >> days >> months >> years >> cost >> note)
		{
			if (whileIndex != editIndex)
			{
				writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			whileIndex++;
		}
		writer.close();
		reader.close();

		ifstream copy("dataHolder.txt");
		ofstream paste("expense history.txt");
		while (copy >> days >> months >> years >> cost >> note)
		{
			paste << days << ' ' << months << ' ' << years << endl << cost << ' ' << note << endl;
		}
		copy.close();
		paste.close();
		cout << "Your value is deleted successfully" << endl;
		system("pause");
		system("cls");
		display_expenses_history();
	}
	else if (choice == 2)
	{
		system("cls");
		ifstream expensesReader("recurring history.txt");

		while (expensesReader >> days >> months >> years >> cost >> note)
		{
			cout << index++ << '.' << cost << '\t' << note << endl;
		}

		expensesReader.close();

		cout << "Enter the index you want to delete: " << endl;
		int editIndex;
		cin >> editIndex;

		ifstream reader("recurring history.txt");
		ofstream writer("dataHolder.txt");
		int whileIndex = 1;
		double newCost;
		string newNote;
		while (reader >> days >> months >> years >> cost >> note)
		{
			if (whileIndex != editIndex)
			{
				writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			whileIndex++;
		}
		writer.close();
		reader.close();

		ifstream copy("dataHolder.txt");
		ofstream paste("recurring history.txt");
		while (copy >> days >> months >> years >> cost >> note)
		{
			paste << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
		}
		copy.close();
		paste.close();
		cout << "Your value is deleted successfully" << endl;
	}
	else if (choice == 3)
	{
		system("cls");
		cout << "choose" << endl;
		cout << "1.Delete Incomr history" << endl;
		cout << "2.Delete Income value." << endl;

		int incomeChoice;
		cin >> incomeChoice;

		if (incomeChoice == 1)
		{
			system("cls");
			ifstream expensesReader("income history.txt");

			while (expensesReader >> days >> months >> years >> cost >> note)
			{
				cout << index++ << '.' << cost << '\t' << note << endl;
			}

			expensesReader.close();

			cout << "Enter the index you want to delete: " << endl;
			int editIndex;
			cin >> editIndex;

			ifstream reader("income history.txt");
			ofstream writer("dataHolder.txt");
			int whileIndex = 1;
			double newCost;
			string newNote;
			while (reader >> days >> months >> years >> cost >> note)
			{
				if (whileIndex != editIndex)
				{
					writer << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
				}
				whileIndex++;
			}
			writer.close();
			reader.close();

			ifstream copy("dataHolder.txt");
			ofstream paste("income history.txt");
			while (copy >> days >> months >> years >> cost >> note)
			{
				paste << days << ' ' << months << ' ' << years << endl << cost << endl << note << endl;
			}
			copy.close();
			paste.close();
			cout << "Your income is deleted successfully" << endl;
		}
		else if (incomeChoice == 2)
		{
			system("cls");
			double oldValue, newValue;
			ifstream incomeReader("income value.txt");
			incomeReader >> oldValue;
			incomeReader.close();
			cout << "Your current income is: ";
			cout << oldValue << endl;
			cout << "----------" << endl;
			ofstream incomeWriter("income value.txt");
			incomeWriter << 0;
			incomeWriter.close();
			

			ofstream incomeClear("income history.txt");
			incomeClear.clear();
			incomeClear.close();
		}
	}
	system("pause");
	system("cls");
	main();
}

void display_income()
{
	system("cls");

	int days, months, years;
	double cost;
	string note;

	ifstream reader("income history.txt");

	int index = 1;

	while (reader >> days >> months >> years >> cost >> note)
	{
		cout << index++ << '.' << note << '\t' << cost << endl;
	}

	cout << endl;
	reader.close();


	ifstream reader1("income value.txt");

	double incomeValue;

	reader1 >> incomeValue;

	cout << "Your current income value is: $" << incomeValue << endl;

	reader1.close();

	system("pause");
	system("cls");
	main();
	
}

void add_recurring_category()
{
	system("cls");

	string MainCategoryName, fileCategories, subCategoryName, fileName, fileIndexString;
	int fileIndex, whileIndex = 1;
	char choice;

	cout << "Enter the name of the new category: ";
	cin >> MainCategoryName;

	ifstream readIndex("MainCategories.txt");
	while (readIndex >> fileIndex >> fileCategories)
	{
		continue;
	}
	readIndex.close();

	fileIndexString = to_string(++fileIndex);
	fileName = fileIndexString.append(".txt");

	ofstream writeCategory("MainCategories.txt", ios::app);
	writeCategory << fileIndex << ' ' << MainCategoryName << endl;
	writeCategory.close();

	ofstream writeSubCategory(fileName);
	do
	{
		cout << "Enter subcategory no" << whileIndex << ':' << '\t';
		cin >> subCategoryName;
		writeSubCategory << whileIndex++ << ' ' << subCategoryName << endl;
		cout << "Do you want to add new subcategory? (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice =='Y');
	writeSubCategory.close();

	system("pause");
	system("cls");
	main();
}

void quick_review()
{
	system("cls");
	double expense = 0, recurring = 0, totalOutcome, income, currentIncome;

	ifstream readIncome("income value.txt");
	readIncome >> income;
	cout << "Your total income value: $" << income << endl;
	readIncome.close();

	int days, months, years;
	double cost;
	string note;

	ifstream readExpense("expense history.txt");
	while (readExpense >> days >> months >> years >> cost >> note)
	{
		expense += cost;
	}
	readExpense.close();
	cout << "Your total expense: $"  << expense << endl;
	
	ifstream readRecurring("recurring history.txt");
	while (readRecurring >> days >> months >> years >> cost >> note)
	{
		recurring += cost;
	}
	readRecurring.close();
	cout << "Your total recurring costs: $" << recurring << endl;

	totalOutcome = expense + recurring;
	cout << "Your total outcome: $" << totalOutcome << endl;
	currentIncome = income - totalOutcome;
	//cout << "Your total income: $" << currentIncome << endl;
	remaining_days();
	
	//system("pause");
	//system("cls");
	//main();
}

void remaining_days()
{
	int months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	SYSTEMTIME time;
	GetLocalTime(&time);
	int days = time.wDay;
	int month = time.wMonth;
	int remaining = months[month + 1] - days;
	cout << "There is " << remaining << " days to the end of the month" << endl;
}

void detailed_review()
{
	system("cls");
	quick_review();
	cout << "----------------------------------------" << endl;

	cout << "View the history of:" << endl;
	cout << "--------------------" << endl;
	cout << "1.Income history." << endl;
	cout << "2.Expenses history." << endl;
	cout << "3.Recurring costs history." << endl;

	int choice;
	cout << "Your choice is: ";
	cin >> choice;

	ifstream reader;
	int day, month, year;
	double value;
	string note;

	if (choice == 1)
	{
		system("cls");
		cout << "Income history" << endl;
		cout << "--------------" << endl;
		reader.open("income history.txt");
		while (reader >> day >> month >> year >> value >> note)
		{
			cout << "Date: " << day << '/' << month << '/' << year << endl;
			cout << "Income source: " << note << endl;
			cout << "Income value: $" << value << endl;
			cout << "--------------------------------------" << endl;
		}
	}

	else if (choice == 2)
	{
		system("cls");
		cout << "Expense history" << endl;
		cout << "---------------" << endl;
		reader.open("expense history.txt");
		while (reader >> day >> month >> year >> value >> note)
		{
			cout << "Date: " << day << '/' << month << '/' << year << endl;
			cout << "Expense note: " << note << endl;
			cout << "Expense value: $" << value << endl;
			cout << "--------------------------------------" << endl;
		}
	}

	else if (choice == 3)
	{
		system("cls");
		cout << "Recurring history" << endl;
		cout << "-----------------" << endl;
		reader.open("recurring history.txt");
		while (reader >> day >> month >> year >> value >> note)
		{
			cout << "Date: " << day << '/' << month << '/' << year << endl;
			cout << "Recurring note: " << note << endl;
			cout << "Recurring value: $" << value << endl;
			cout << "--------------------------------------" << endl;
		}
	}

	reader.close();
	system("pause");
	system("cls");
	main();
}

void date_range_report()
{
	system("cls");

	cout << "Enter the date range:" << endl;
	cout << "---------------------" << endl;

	int day1, day2, month1, month2, year1, year2;

	cout << "from day: ";
	cin >> day1;
	cout << "from month: ";
	cin >> month1;
	cout << "from year: ";
	cin >> year1;

	cout << endl;

	cout << "to day: ";
	cin >> day2;
	cout << "to month: ";
	cin >> month2;
	cout << "to year: ";
	cin >> year2;
	cout << endl << "-----------------------" << endl;

	int id;
	int days, months, years;
	int cost;
	string note;

	ifstream reader("expense history.txt");
	int index = 1;

	if (reader.is_open())
	{
		while (reader >> days >> months >> years >> cost >> note)
		{
			if (years > year1 && years < year2)
			{
				cout << "Date: " << days << '/' << months << '/' << years << endl;
				cout << "Cost: $" << cost << endl;
				cout << "Note: " << note << endl;
				cout << endl;
			}
			else if (year1 == year2)
			{
				if (months > month1 && months < month2)
				{
					cout << "Date: " << days << '/' << months << '/' << years << endl;
					cout << "Cost: $" << cost << endl;
					cout << "Note: " << note << endl;
					cout << endl;
				}
				else if (months == month1 && months != month2)
				{
					if (days >= day1)
					{
						cout << "Date: " << days << '/' << months << '/' << years << endl;
						cout << "Cost: $" << cost << endl;
						cout << "Note: " << note << endl;
						cout << endl;
					}
				}
				else if (months != month1 && months == month2)
				{
					if (days <= day2)
					{
						cout << "Date: " << days << '/' << months << '/' << years << endl;
						cout << "Cost: $" << cost << endl;
						cout << "Note: " << note << endl;
						cout << endl;
					}
				}
				else if (months == month1 && months == month2)
				{
					if (days >= day1 && days <= day2)
					{
						cout << "Date: " << days << '/' << months << '/' << years << endl;
						cout << "Cost: $" << cost << endl;
						cout << "Note: " << note << endl;
						cout << endl;
					}
				}
			}
			else if (years == year1 && years != year2)
			{
				if (months > month1)
				{
					cout << "Date: " << days << '/' << months << '/' << years << endl;
					cout << "Cost: $" << cost << endl;
					cout << "Note: " << note << endl;
					cout << endl;
				}
				else if (months == month1)
				{
					if (days > day1)
					{
						cout << "Date: " << days << '/' << months << '/' << years << endl;
						cout << "Cost: $" << cost << endl;
						cout << "Note: " << note << endl;
						cout << endl;
					}
				}
			}
			else if (years != year1 && years == year2)
			{
				if (months < month2)
				{
					cout << "Date: " << days << '/' << months << '/' << years << endl;
					cout << "Cost: $" << cost << endl;
					cout << "Note: " << note << endl;
					cout << endl;
				}
				else if (months == month2)
				{
					if (days < day2)
					{
						cout << "Date: " << days << '/' << months << '/' << years << endl;
						cout << "Cost: $" << cost << endl;
						cout << "Note: " << note << endl;
						cout << endl;
					}
				}
			}
			// case for the same dates
			else if (years == year1 && months == month1 && days == day1)
			{
				cout << "Date: " << days << '/' << months << '/' << years << endl;
				cout << "Cost: $" << cost << endl;
				cout << "Note: " << note << endl;
				cout << endl;
			}
			else if (years == year2 && months == month2 && days == day2)
			{
				cout << "Date: " << days << '/' << months << '/' << years << endl;
				cout << "Cost: $" << cost << endl;
				cout << "Note: " << note << endl;
				cout << endl;
			}

		}
		reader.close();
	}
	else
		cout << "No expenses added yet" << endl;


	system("pause");
	system("cls");
	main();
}