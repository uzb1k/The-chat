#pragma once
#include <iostream>
using namespace std;

class User {
public:
	User();
	User(const string& login, const string& password);

	~User();

	void SetLogin(const string& login);
	string GetLogin();

	void SetPassword(const string& password);
	string GetPassword();

	void AddMessage(const string& message);
	void ShowMessage();

	bool CheckCredentials(const string& login, const string& password);

private:
	string _Login;
	string _Password;
	string* _Messages;
	int _CountMessages;
};


class Chat {
public:
	Chat();
	
	~Chat();

	const User* GetUsers() const;

	void AddUser(const User& newUser);
	void DeleteUser(const string& delUser);

	void Register();
	User* Authenticate(const string& login, const string& password);

	void SendMessage(const string& fromlogin, const string& tologin, const string& message);
	void ShowGeneralMessages();

	int GetSize();
private:
	User* users;
	int _size;
};



