#include "Chat.h"
#include <iostream>
using namespace std;

User::User() : _Messages(nullptr), _CountMessages(0) {}
User::User(const string& login, const string& password) : _Login(login), _Password(password) {}

User::~User() {
    delete[] _Messages;
}

//Добавление сеттеров и геттеров
void User::SetLogin(const string& login) {
    _Login = login;
}
string User::GetLogin() {
    return _Login;
}

void User::SetPassword(const string& password) {
    _Password = password;
}
string User::GetPassword() {
    return _Password;
}

void User::AddMessage(const string& NewMessage) {
    string* NewMessages = new string[_CountMessages + 1]; //Создаём динамический массив больше размером для добавки новых сообщений и выделения памяти для них
    for (int i = 0; i < _CountMessages; ++i) {
        NewMessages[i] = _Messages[i]; //Копирование старых сообщений
    }
    
    NewMessages[_CountMessages] = NewMessage; //Добавление нового сообщения
    delete[] _Messages; //Очищение старого массива с сообщениями
    _Messages = NewMessages; //Заполнение уже с новым сообщением
    ++_CountMessages;
}

void User::ShowMessage(){
    if (_CountMessages == 0) {
        cout << "There's no new messages :(" << endl;
    }
    else {
        for (int i = 0; i < _CountMessages; ++i) {
            cout << _Messages[i] << endl;
        }
    }
}

//Проверка правильности логина и пароля
bool User::CheckCredentials(const string& login, const string& password) {
    return(_Login == login && _Password == password);
}

//Конструктор деструктор
Chat::Chat() : users(nullptr), _size(0){}

Chat::~Chat() {
    delete[] users;
}

//Геттеры
int Chat::GetSize() {
    return _size;
}

const User* Chat::GetUsers() const {
    return users;
}

//Функция добавления нового пользователя
void Chat::AddUser(const User& newUser) {
    User* newArray = new User[_size + 1]; //Создание динамического массива с выделением памяти под кождого нового пользователя
    for (int i = 0; i < _size; ++i) {
        newArray[i] = users[i]; //Копирование старых пользователей
    }

    newArray[_size] = newUser; //Добавление нового пользователя
    delete[] users; //Очищение старого массива
    users = newArray; //Добавление уже с новым пользователем
    ++_size;
}

//(Доп.функция) Удаление пользователя
void Chat::DeleteUser(const string& delUser) {
    int indexOfUs;

    for (int i = 0; i < _size; ++i) {
        if (users[i].GetLogin() == delUser) {
            indexOfUs = i; //Узнаём индекс нужного для удаления пользователя
        }
    }

    User* newArray = new User[_size - 1]; //Создаём динамический массив с меньшим размером

    for (int i = 0; i < indexOfUs; ++i) {
        newArray[i] = users[i]; //Копируем пользователей до нужного нам
    }

    for (int i = indexOfUs + 1; i < _size; ++i) {
        newArray[i - 1] = users[i]; //Копируем пользователей после нужного
    }

    delete[] users; //Очищаем
    users = newArray; //Добавляем без того пользователя

    cout << "The account has been deleted." << endl;

    --_size;
}

void Chat::Register() {
    string login, password;

    cout << "Enter your new Login: " << endl;
    cin >> login;

    cout << "Enter your new Password: " << endl;
    cin >> password;

    User newUser(login, password);
    AddUser(newUser); //Считываем новый логин и пароль и добавляем при помощи нашей функции

    cout << "User has registered!" << endl;
}

User* Chat::Authenticate(const string& login, const string& password) {

    for (int i = 0; i < _size; ++i) {
        if (users[i].CheckCredentials(login, password)) { //Проверяем логин и пароль при помощи нашей функции
            cout << "User authenticated successfully." << endl;
            return &users[i]; //И возвращаем указатель на авторизировавшегося пользователя 
        }
    }
    cout << "Invalid Login or Passwrod!" << endl;
    return nullptr; //В противном случае возвращаем нулевой указатель
}

void Chat::SendMessage(const string& fromlogin, const string& tologin, const string& message){
    //Берём указатели на от кого и кому будет сообщение
    User* From = nullptr;
    User* To = nullptr;

    for (int i = 0; i < _size; ++i) {
        if (users[i].GetLogin() == fromlogin) {
            From = &users[i];
        }

        if (users[i].GetLogin() == tologin) {
            To = &users[i];
        }
    }
    if (From && To) {
        string FullMessage = "From " + fromlogin + ": " + message;
        To->AddMessage(FullMessage);
        cout << "Message sent" << endl;
    }
    else {
        cout << "User not found" << endl;
    }
}

//Функция для показа сообщении из общего чата
void Chat::ShowGeneralMessages() {
    for (int i = 0; i < _size; ++i) {
        if (users[i].GetLogin() == "General") {
            users[i].ShowMessage();
        }
    }
}
