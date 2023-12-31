#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode
	{
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector<string> vClientDate = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode,
							 vClientDate[0], vClientDate[1],
							 vClientDate[2], vClientDate[3],
							 vClientDate[4], vClientDate[5],
							 stod(vClientDate[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{

		string DataLine = "";

		DataLine = Client.GetFirstName() + Separator;
		DataLine += Client.GetLastName() + Separator;
		DataLine += Client.GetEmail() + Separator;
		DataLine += Client.GetPhone() + Separator;
		DataLine += Client.AccountNumber() + Separator;
		DataLine += Client.GetPinCode() + Separator;
		DataLine += to_string(Client.GetAccountBalance());

		return DataLine;
	}

	static void _SaveClientDataToFile(vector<clsBankClient> _vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string DateLine;
			for (clsBankClient C : _vClients)
			{
				if (C.MarkForDelete() == false)
				{
					DateLine = _ConvertClientObjectToLine(C);
					MyFile << DateLine << endl;
				}
			}

			MyFile.close();
		}
	}

	static vector<clsBankClient> _LoadClientsDateFromFile()
	{

		vector<clsBankClient> vClient;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClient.push_back(Client);
			}

			MyFile.close();
		}

		return vClient;
	}

	void _Update()
	{

		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDateFromFile();

		for (clsBankClient &C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientDataToFile(_vClients);
	}

	void _AddNew()
	{
		_AddDataToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataToFile(string Client)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{

			MyFile << Client << endl;

			MyFile.close();
		}
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:
	clsBankClient(
		enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber,
		string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	bool MarkForDelete()
	{
		return _MarkForDelete;
	}

	/*void Print(){
		cout << "\nClient Card:";
		cout << "\n__________________________";
		cout << "\nFirstName    : " << FirstName;
		cout << "\nLastName     : "<< LastName;
		cout << "\nFull Name    : " << FirstName + " " + LastName;
		cout << "\nEmail        : " << Email;
		cout << "\nPhone        : " << Phone;
		cout << "\nAcc. Number  : " << _AccountNumber;
		cout << "\nPassword     : " << _PinCode;
		cout << "\nBalance      : " << _AccountBalance;
		cout << "\n__________________________";
	}*/

	static clsBankClient Find(string AccountNumber)
	{

		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	enum enSaveResults
	{
		svFaildEmptyObject = 0,
		svSucceded = 1,
		svFaildAccountNumberExsit = 2
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceded;
			break;
		}
		case enMode::AddNewMode:
		{

			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExsit;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceded;
				;
				break;
			}
		}
		}
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDateFromFile();

		for (clsBankClient &C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDateFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> vClients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient C : vClients)
		{
			TotalBalances += C.GetAccountBalance();
		}

		return TotalBalances;
	}

	static vector<clsBankClient> LoadClientsDateFromFile()
	{
		return _LoadClientsDateFromFile();
	}

	static void SaveClientDataToFile(vector<clsBankClient> vClients)
	{
		_SaveClientDataToFile(vClients);
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
		}
	}
};
