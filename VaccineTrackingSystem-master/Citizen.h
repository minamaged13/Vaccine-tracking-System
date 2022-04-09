#pragma once
#include <string>
#include <iostream>
using namespace std;
class Citizen
{
private:
	long long ID = 0;
	string fullname = "";
	string password = "";
	char gender = ' ';
	int age = 0;
	string governorate = "";
	bool dose1 = false;
	bool dose2 = false;
public:
	int indexF;
	Citizen();
	Citizen(long long ID, string fullname, string password, char gender, int age, string governorate);
	Citizen(long long ID, string password);
	void CitDisplay() const;

	//setters
	void setId(long long _id);
	void setName(string _name);
	void setPass(string _pass);
	void setGender(char _gend);
	void setAge(int _age);
	void setGov(string _gov);
	void setVacc1(bool _vacc);
	void setVacc2(bool _vacc);

	//getters
	long long getId() const;
	string getName() const;
	string getPass() const;
	char getGender() const;
	int getAge() const;
	string getGov() const;
	bool getVacc1() const;
	bool getVacc2() const;
	void Update();
};
