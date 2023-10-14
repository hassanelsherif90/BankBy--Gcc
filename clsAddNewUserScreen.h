#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsAddNewUserScreen : protected clsScreen
{

private:
    static void _ReadUserInfo(clsUser &User)
    {

        cout << "\nFirstName      : ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nLastName       : ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEmail          : ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nPhone          : ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nPassword       : ";
        User.SetPassword(clsInputValidate::ReadString());

        User.SetPermissions(_ReadUserPermission());
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________";
        cout << "\nFirstName    : " << User.GetFirstName();
        cout << "\nLastName     : " << User.GetLastName();
        cout << "\nFull Name    : " << User.FullName();
        cout << "\nEmail        : " << User.GetEmail();
        cout << "\nPhone        : " << User.GetPhone();
        cout << "\nPassword     : " << User.GetPassword();
        cout << "\nBalance      : " << User.GetPermissions();
        cout << "\n__________________________";
    }

    static int _ReadUserPermission()
    {
        int Permissions = 0;
        char answer = 'n';

        cout << "\nDo You want give full access ? y/n";
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            return -1;
        }

        cout << "\nShow Client List ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pListClients;
        }

        cout << "\nAdd New Client ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pAddNewClient;
        }

        cout << "\nDelete Client ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pDeleteClient;
        }

        cout << "\nUpdate Client ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pUpdateClients;
        }

        cout << "\nFind Client ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pFindClient;
        }

        cout << "\nTransactions ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pTranactiond;
        }

        cout << "\nManage user ? y/n ";
        cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            Permissions += clsUser::enMainMenuPermissions::pTranactiond;
        }

        return Permissions;
    }

public:
    static void ShowAddNewUser()
    {
        _DrawScreenHeader("\t  Add New User\n");
        string UserName;

        cout << "\nPlease Enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nAccount number is already Used, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser NewClient = clsUser::GetAddNewUserObject(UserName);

        cout << "\n\nAdd New User :\n";
        cout << "_____________________";

        _ReadUserInfo(NewClient);
        cout << "_____________________";

        clsUser::enSaveResults SaveResults;

        SaveResults = NewClient.Save();

        switch (SaveResults)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Successfully :) \n";
            _PrintUser(NewClient);
            break;
        }

        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError Account was not saved because it’s Empty :( \n";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nAccount number is already Used";
            break;
        }
        }

        cout << endl;
    }
};
