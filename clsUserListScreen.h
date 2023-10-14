#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsUserListScreen : protected clsScreen
{
private:
    static void PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << ""
             << "| " << setw(15) << left << User.GetUserName();
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.GetPhone();
        cout << "| " << setw(20) << left << User.GetEmail();
        cout << "| " << setw(10) << left << User.GetPassword();
        cout << "| " << setw(12) << left << User.GetPermissions();
    }

public:
    static void ShowUserList()
    {
        vector<clsUser> vUsers = clsUser::GetUsersList();

        string Title = "\t User List";
        string SubTitle = "\t (" + to_string(vUsers.size()) + ") Users ";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << ""
             << "\n\t___________________________________________";
        cout << "____________________________________________________________\n"
             << endl;
        cout << setw(8) << left << ""
             << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permission";
        cout << setw(8) << left << ""
             << "\n\t___________________________________________";
        cout << "____________________________________________________________\n"
             << endl;

        if (vUsers.size() == 0)
            cout << "\n\t\t\tNo Clients Available In the System!";
        else

            for (clsUser C : vUsers)
            {
                PrintUserRecordLine(C);
                cout << endl;
            }

        cout << setw(8) << left << "\n\t___________________________________________";
        cout << "____________________________________________________________\n"
             << endl;
    }
};
