#include "Chat.h"
#include <iostream>
#include <string>
#include <exception>

using namespace std;

int main() {
    Chat c;
    int choose;
    string password, login, tologin, message;
    User* user;
    bool programRun = true;
    bool addGeneral = true; //Объявляем условия продолжение цикла

    User general("General", "123"); //Объявляем общий чат


    while (programRun) {
        try {
            cout << "What can we do for you? (1 - Register. 2 - Login in. 3 - Exit.) " << endl;
            cin >> choose;

            if (choose != 1 && choose != 2 && choose != 3) { //Проверка пользователя на корректный ввод
                throw "Incorrect option"; //И перехват исключения в случае ошибки
            }

            switch (choose) {
            case 1:
                c.Register();
                break;

            case 2:
                if (c.GetUsers() == nullptr) { //Проверяем наличие пользователей и останавливаем вход в случае их отсутсвия
                    cout << "Currently, there are no registered users." << endl;
                    break;
                }

                while (addGeneral) { //Добавляем пользователя, для общего чата
                    c.AddUser(general);
                    addGeneral = false; //И переключаем флаг, чтобы избежать многократного добавления
                }

                cout << "Enter your login: " << endl;
                cin >> login;

                cout << "Enter your password: " << endl;
                cin >> password;
                user = c.Authenticate(login, password);

                if (user != nullptr) {
                    cout << "Welcome! " << user->GetLogin() << endl;
                    bool chatting = true;
                    while (chatting) {
                        try {
                            cout << "Enter the option" << endl;
                            cout << "1 - Write the message. 2 - Read the message. 3 - Write the general message. 4 - Read the general message. 5 - delete account: " << endl;
                            cin >> choose;

                            if (choose != 1 && choose != 2 && choose != 3 && choose != 4 && choose != 5) { //Снова проверяем корректность ввода
                                throw "Incorrect option";
                            }

                            switch (choose) {
                            case 1:
                                cout << "Enter login of the recepient: " << endl;
                                cin >> tologin;

                                cout << "Enter your message: " << endl;

                                cin.ignore();
                                getline(cin, message);

                                c.SendMessage(login, tologin, message);

                                cout << "Do you want to continue chatting? 1 - yes, 2 - no" << endl;
                                cin >> choose;

                                if (choose != 1 && choose != 2) {
                                    throw "Incorrect option";
                                }
                                if (choose != 1) {
                                    chatting = false;
                                }

                                break;
                            case 2:
                                user->ShowMessage();
                                cout << "Do you want to continue chatting? 1 - yes, 2 - no" << endl;
                                cin >> choose;

                                if (choose != 1 && choose != 2) {
                                    throw "Incorrect option";
                                }
                                if (choose != 1) {
                                    chatting = false;
                                }

                                break;
                            case 3:
                                cout << "Enter your message: " << endl;
                                cin.ignore();
                                getline(cin, message);

                                c.SendMessage(login, "General", message);

                                cout << "Do you want to continue chatting? 1 - yes, 2 - no" << endl;
                                cin >> choose;

                                if (choose != 1 && choose != 2) {
                                    throw "Incorrect option";
                                }
                                if (choose != 1) {
                                    chatting = false;
                                }

                                break;

                            case 4:
                                c.ShowGeneralMessages();
                                cout << "Do you want to continue chatting? 1 - yes, 2 - no" << endl;
                                cin >> choose;

                                if (choose != 1 && choose != 2) {
                                    throw "Incorrect option";
                                }

                                if (choose != 1) {
                                    chatting = false;
                                }
                                break;
                            case 5:
                                c.DeleteUser(login);
                                chatting = false;
                            }
                        }
                        //Перехват исключений
                        catch (const char* e) {
                            cout << "Exeption caught: " << e << endl;

                            cin.clear();
                            cin.ignore(99999, '\n');

                            continue;
                        }
                    }
                }
                break;

            case 3:
                cout << "Exiting...";
                return 0;
            }
        }
        //Ещё один перехват для каждого switch
        catch (const char* e) {
            cout << "Exeption caught: " << e << endl;

            cin.clear();
            cin.ignore(99999, '\n');

            continue;
        }

    }
    return 0;
}