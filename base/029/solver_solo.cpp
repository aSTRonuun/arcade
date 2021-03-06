#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Note{
    string title;
    string content;
public:
    Note(string title = " ", string content = " "){
        this->title = title;
        this->content = content;
    }

    string getTitle(){
        return title;
    }
    string getContent(){
        return content;
    }

    void setTitle(string title){
        this->title = title;
    }

    void setContent(string content){
        this->content = content;
    }

    friend ostream& operator<<(ostream& os, Note& note){
        os << note.title << ":" << note.content;
        return os;
    }

};

class User{
    string username;
    string password;
    vector<Note> notes;
public:

    User (string username = "", string password = ""){
        this->username = username;
        this->password = password;
    }

    string getUsername(){
        return username;
    }

    bool addNote(string title, string content){
        for(auto note : notes)
            if(note.getTitle() == title)
                throw ("fail: entrada ja cadastrada");
        notes.push_back(Note(title, content));
        return true;
    }

    bool checkPassword(string password){
        return this->password == password;
    }

    vector<Note> getNotes(){
        return notes;
    }

    friend ostream& operator<<(ostream& os, User& user){
        os << "user: " << user.username << endl;
        int i = 0;
        for(auto note : user.notes)
            os << "[" << i++ << ":" << note << "]" << endl;
        return os;
    }
};


class System{
    vector<User> users;
    User * currentUser;

    User * getUser(string username){
        for(auto& user : users)
            if((user.getUsername() == username))
                return &user;
        return nullptr;
    }

    User * getCurrent(){
        if(currentUser == nullptr)
            throw string("fail: ninguem logado");
        return currentUser;
    }

public:
    
    System(){
        this->currentUser = nullptr;
    }

    //não pode ter dois usernames iguais
    void addUser(string username, string password){
        for(auto user : users)
            if(user.getUsername() == username)
                throw string("fail: username duplicado");
        users.push_back(User(username, password));
    }

    void login(string username, string password){
        if(currentUser != nullptr)
            throw string("fail: ja existe alguem logado");
        auto user = getUser(username);
        if(user == nullptr)
            throw string("fail: usuario nao encontrado");
        if(!user->checkPassword(password))
            throw string("fail: senha invalida");
        currentUser = user;
    }

    void logout(){
        if(getCurrent() == nullptr)
            throw string("fail: nao existe ninguem logado");
        currentUser = nullptr;
    }

    string getUsernames(){
        string output = "[ ";
        for(auto& user : users)
            output += user.getUsername() + " ";
        return output + "]\n";
    }

    void addNote(string title, string content){
        getCurrent()->addNote(title, content);
    }

    friend ostream& operator<<(ostream& os, System& system){
        os << *system.getCurrent();
        return os;
    }
};

vector<string> split(string line){
    stringstream ss(line);
    string token;
    vector<string> output;
    while(ss >> token)
        output.push_back(token);
    return output;
}

int main(){
    System sistema;

    while(true){
        try{
            string line, cmd;
            getline(cin, line);
            cout << "$" << line << "\n";
            vector<string> ui = split(line);
            cmd = ui[0];
            if(cmd == "end"){
                break;
            }else if(cmd == "users"){
                cout << sistema.getUsernames();
            }else if(cmd == "addUser"){
                sistema.addUser(ui[1], ui[2]);
            }else if(cmd == "login"){
                sistema.login(ui[1], ui[2]);
            }else if(cmd == "show"){
                cout << sistema;    
            }else if(cmd == "logout"){
                sistema.logout();
            }else if(cmd == "addNote"){
                string output;
                for(int i = 2; i < (int) ui.size(); i++)
                    output += " " + ui[i];
                sistema.addNote(ui[1], output.substr(1));
            }else{
                cout << "fail: comando invalido\n";
            }
        }catch(string e){
            cout << e << endl;
        }
    }
}
























