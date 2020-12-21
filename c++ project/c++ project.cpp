#include <iostream>
#include <string>
#include <vector>
#include<fstream>
using namespace std;
class Buyer
{
public:
	virtual void printInfo() = 0;
	virtual double getTax() = 0;
protected:
	string ID;
};
class TaxAutomobile :public Buyer
{
public:
	TaxAutomobile(string regNumber, int p, int a)
	{
		ID = regNumber;
		power = p;
		age = a;
	}
	virtual void printInfo()
	{
		cout << "RegNumber:" << ID << endl;
		cout << "Power:" << power << endl;
		cout << "Vazrast:" << age << endl;
	};
	virtual double getTax()
	{
		double dan = 0;
		if (power < 37)dan += 100;
		if (power > 37 && power <= 55) dan += power * 1.2;
		else if (power > 55 && power <= 74) dan += power * 1.62;
		else if (power > 74 && power <= 110) dan += power * 3.30;
		else if (power > 110) dan += power * 3.69;
		if (age > 5 && age <= 14) dan += (dan * 1.5);
		else if (age <= 5) dan += (dan * 2.8);
		return dan;
	};
private:
	int power;
	int age;
};
class thirdPartyLiabilityInsurance :public Buyer
{
public:
	thirdPartyLiabilityInsurance(string regNumber, int hA, int yExp, int p)
	{
		ID = regNumber;
		humanAge = hA;
		yearsOfExperience = yExp;
		power = p;
	}
	virtual void printInfo()
	{
		cout << "RegNumber:" << ID << endl;
		cout << "Power:" << power << endl;
		cout << "Age of the customer:" << humanAge << endl;
		cout << "Years Of experience:" << yearsOfExperience << endl;
	};
	virtual double getTax()
	{
		double priceTopay = 200;
		if (humanAge > 26) priceTopay *= 1.2;
		else if (humanAge < 26) priceTopay *= 1.4;
		if (yearsOfExperience == 0) return 2 * priceTopay;
		if (yearsOfExperience >= 10) priceTopay += (priceTopay * 0.3);
		else if (yearsOfExperience < 10) priceTopay += (priceTopay * 0.5);
		if (power > 55 && power <= 74) priceTopay += 50.00;
		else if (power > 74 && power <= 110) priceTopay += 100.00;
		else if (power > 110) priceTopay += 250.69;
		return priceTopay;
	};
private:
	int humanAge;
	int yearsOfExperience;
	int power;
};
class annualTechnicalInspection :public Buyer
{
public:
	annualTechnicalInspection(string regNumber, int p, string c)
	{
		ID = regNumber;
		price = p;
		category = c;
	}
	virtual void printInfo()
	{
		cout << "RegNumber:" << ID << endl;
		cout << "Price:" << price << endl;
		cout << "Category of the automobile:" << category << endl;
	};
	virtual double getTax()
	{
		double dann = price;
		if (category == "M1") dann += 6;
		if (category == "L1") dann += 2;
		if (category == "L4") dann += 4;
		return dann;
	};
private:
	int price;
	string category;
};
class Query
{
public:
	void addClient(Buyer* b) { query.push_back(b); }
	void listOfPeople()
	{
		if (!query.empty())
		{
			for (size_t i = 0; i < query.size(); i++)
			{
				query[i]->printInfo();
				cout << endl;
			}
		}
		else cout << "There are no clients at the moment!" << endl;
	}
	void Process()
	{
		if (query.size() > 0)
		{
			double gains = 0;
			cout << "\nKlient: \n";
			query[0]->printInfo();
			cout << "The company gains: " << query[0]->getTax() << endl;
			transactions.push_back(query[0]->getTax());
			query.erase(query.begin());
		}
		else cout << "There are no clients at the moment!" << endl;
	}
	vector <Buyer*>searcher() { return query; };
	vector<double> totalSum() { return transactions; };
private:
	vector<Buyer*> query;
	vector<double>transactions;
};
int main()
{
	Query query;
	string choice = "";
	while (choice != "Exit")
	{
		cout << "\n\nMENU\n=============================\n";
		cout << "1. MPS TAX\n2. Civil Liability Price \n3. Casco Price \n4. List of Orders\n";
			cout << "5. Service\n6. Profit\n0.Exit\n============================ = \nChoice:";
			cin >> choice;
		if (choice == "1")
		{
			string regNumber;
			int power, age;
			cin.ignore(100, '\n');
			cout << "\nMPS TAX:\n\nRegular number: ";
			getline(cin, regNumber);
			cout << "Power: ";
			cin >> power;
			cout << "Age of the car: ";
			cin >> age;
			query.addClient(new TaxAutomobile(regNumber, power, age));
		}
		else if (choice == "2")
		{
			string regNumber;
			int humanAge, yearsOfExperience, power;
			cin.ignore(10, '\n');
			cout << "\n Civil Liability Price: \n\nRegular number: ";
			getline(cin, regNumber);
			cout << "Power: ";
			cin >> power;
			cout << "Age of the customer: ";
			cin >> humanAge;
			cout << "Years of driving experince:";
			cin >> yearsOfExperience;
			query.addClient(new thirdPartyLiabilityInsurance(regNumber, power,
				humanAge, yearsOfExperience));
		}
		else if (choice == "3")
		{
			string regNumber, Category; int price;
			cin.ignore(100, '\n');
			cout << "\nCasco Price: \n\nRegular Number:";
			getline(cin, regNumber);
			cout << "Price: ";
			cin >> price;
			cout << "Category: ";
			cin >> Category;
			query.addClient(new annualTechnicalInspection(regNumber, price,
				Category));
		}
		else if (choice == "4")
		{
			cout << "\nList of People:\n\n";
			query.listOfPeople();
		}
		else if (choice == "5") query.Process();
		else if (choice == "6")
		{
			cout << "\nCompany profit: \n\n";
			double sum = 0;
			for (size_t i = 0; i < query.totalSum().size(); i++) sum +=
				query.totalSum()[i];
			cout << "Total current profit is: " << sum << endl;
		}
		else if (choice == "Exit") cout << "Thank you for using our program!" <<endl;
		else cout << "Invalid input! Please try again!" << endl;
	}
}