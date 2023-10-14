#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{

private:
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

public:
    static void ShowDeleteUser()
    {
        _DrawScreenHeader("\t  Delete User\n");
        string UserName;

        cout << "\nPlease Enter User Name : ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Name is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);

        cout << "\nAre you Want to delete Account Number ? y / n ? ";

        char Answer = 'N';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nClient Deleted Successfully :) .";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError Client Was not Deleted .";
            }
        }
        else
        {
            cout << "\nClient Was not Deleted .";
        }
    }
};
