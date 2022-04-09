#include "Citizen.h"

Citizen::Citizen()
{
}

Citizen::Citizen(long long id, string fn, string pw, char gen, int a, string g)
{
	ID = id;
	fullname = fn;
	password = pw;
	gender = gen;
	age = a;
	governorate = g;
}

Citizen::Citizen(long long id, string pass)
{
	ID = id;
	password = pass;
}

void Citizen::CitDisplay() const
{
	if (this == nullptr)
	{
		return;
	}
	cout << "ID: " << ID << endl;
	cout << "Name: " << fullname << endl;
	cout << "Password: " << password << endl;
	cout << "Gender: " << gender << endl;
	cout << "Age: " << age << endl;
	cout << "Governorate: " << governorate << endl;
	cout << "Dose 1: " << (dose1 ? "Taken" : "Not Taken")<< endl;
	cout << "Dose 2: " << (dose2 ? "Taken" : "Not Taken") << endl;
}

void Citizen::setId(long long _id)
{
	ID = _id;
}

void Citizen::setName(string _name)
{
	fullname = _name;
}

void Citizen::setPass(string _pass)
{
	password = _pass;
}

void Citizen::setGender(char _gend)
{
	gender = _gend;
}

void Citizen::setAge(int _age)
{
	age = _age;
}

void Citizen::setGov(string _gov)
{
	governorate = _gov;
}

void Citizen::setVacc1(bool _vacc)
{
	dose1 = _vacc;
}

void Citizen::setVacc2(bool _vacc)
{
	dose2 = _vacc;
}

long long Citizen::getId() const
{
	return ID;
}

string Citizen::getName() const
{
	return fullname;
}

string Citizen::getPass() const
{
	return password;
}

char Citizen::getGender() const
{
	return gender;
}

int Citizen::getAge() const
{
	return age;
}

string Citizen::getGov() const
{
	return governorate;
}

bool Citizen::getVacc1() const
{
	return dose1;
}

bool Citizen::getVacc2() const
{
	return dose2;
}

void Citizen::Update()
{
	int edit_choice;
	int new_number;
	string new_string;

	while (true)
	{
		cout << "\nPlease choose the info you want to edit: \n\n";
		cout << "\n1-name\n2-password\n3-age\n4-Confirm\n\n";
		cin >> edit_choice;
		cout << "\n";
		if (edit_choice == 1) {
			cout << "Please enter the new name: ";
			cin >> new_string;
			fullname = new_string;
		}
		if (edit_choice == 2) {
			cout << "Please enter the new password: ";
			cin >> new_string;
			password = new_string;
		}
		else if (edit_choice == 3) {
			cout << "Please enter the new age: ";
			cin >> new_number;
			age = new_number;
		}
		else
		{	
			cout << "\ninfo updated\n";
			return;
		}
		cout << "\ninfo updated\n";
	}

}
