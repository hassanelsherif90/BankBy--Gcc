#pragma once
#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string FisrtName, string LastName, string Email, string Phone)
	{
		_FirstName = FisrtName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(string FirstName)
	{
		_FirstName = FirstName;
	}

	string GetFirstName()
	{
		return _FirstName;
	}

	void SetLastName(string LastName)
	{
		_LastName = LastName;
	}

	string GetLastName()
	{
		return _LastName;
	}

	void SetEmail(string Email)
	{
		_Email = Email;
	}

	string GetEmail()
	{
		return _Email;
	}

	void SetPhone(string Phone)
	{
		_Phone = Phone;
	}

	string GetPhone()
	{
		return _Phone;
	}

	string FullName()
	{
		return GetFirstName() + " " + GetLastName();
	}
};
