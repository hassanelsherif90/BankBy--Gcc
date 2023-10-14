#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{

private:
    static void _ReadClientInfo(clsBankClient &Client)
    {

        cout << "\nFirstName      : ";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nLastName       : ";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEmail          : ";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nPhone          : ";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nPinCode        : ";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nAccountBalance : ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________";
        cout << "\nFirstName    : " << Client.GetFirstName();
        cout << "\nLastName     : " << Client.GetLastName();
        cout << "\nFull Name    : " << Client.FullName();
        cout << "\nEmail        : " << Client.GetEmail();
        cout << "\nPhone        : " << Client.GetPhone();
        cout << "\nAcc. Number  : " << Client.AccountNumber();
        cout << "\nPassword     : " << Client.GetPinCode();
        cout << "\nBalance      : " << Client.GetAccountBalance();
        cout << "\n__________________________";
    }

public:
    static void ShowUpdateClient()
    {
        _DrawScreenHeader("\tUpdate Client\n");

        string Account_Number;

        cout << "\nPlease Enter client Account Number : ";
        Account_Number = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(Account_Number))
        {
            cout << "\nAccount number is not found, choose another one: ";
            Account_Number = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(Account_Number);
        _PrintClient(Client1);

        cout << "\n\nUpdate Client :\n";
        cout << "_____________________";

        _ReadClientInfo(Client1);
        cout << "_____________________";

        clsBankClient::enSaveResults SaveResults;

        SaveResults = Client1.Save();

        switch (SaveResults)
        {
        case clsBankClient::enSaveResults::svSucceded:
        {
            cout << "\nAccount Updated Successfully :) \n";
            _PrintClient(Client1);
            break;
        }

        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError Account was not saved because it�s Empty :( \n";
            break;
        }
        }
    }
};
