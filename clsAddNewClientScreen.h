#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsAddNewClientScreen : protected clsScreen
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
    static void ShowAddNewClient()
    {
        _DrawScreenHeader("\t  Add New Client\n");
        string AccountNumber;

        cout << "\nPlease Enter client Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is alraedy Used, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        cout << "\n\nAdd Client :\n";
        cout << "_____________________";

        _ReadClientInfo(NewClient);
        cout << "_____________________";

        clsBankClient::enSaveResults SaveResults;

        SaveResults = NewClient.Save();

        switch (SaveResults)
        {
        case clsBankClient::enSaveResults::svSucceded:
        {
            cout << "\nAccount Added Successfully :) \n";
            _PrintClient(NewClient);
            break;
        }

        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError Account was not saved because it�s Empty :( \n";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExsit:
        {
            cout << "\nAccount number is already Used";
            break;
        }
        }

        cout << endl;
    }
};
