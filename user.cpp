#include "user.h"

user::user(const std::string& name, const std::string& ruolo, const std::string& password) :
 username(name), password(password), ruolo(ruolo) {}

user::user(const user& u) : username(u.username), password(u.password), ruolo(u.ruolo) {}

user& user::operator=(const user& u) {
    if(this != &u){                 //controllo di non essere nel caso di assegnazione x=x
        username=u.getUsername();
        password=u.getPassword();
        ruolo=u.getRuolo();
    }
    return *this;
}

std::string user::getUsername() const { return username; }

std::string user::getPassword() const { return password; }

std::string user::getRuolo() const { return ruolo; }

void user::setUsername(const std::string& newName) {
    username=newName;
}

void user::setPassword(const std::string& newPassword) {
    password=newPassword;
}

void user::setRuolo(const std::string& newRuolo) {
    ruolo=newRuolo;
}

void user::serialize(Json::Value& root) const {
    Json::Value user;
    user["username"] = username;
    user["password"] = password;
    user["ruolo"] = ruolo;

    root["users"].append(user);
}

user* user::deserialize(const Json::Value& root, const std::string& name) {
    for(const auto& userJson : root["users"]) {
        if(userJson["username"].asString() == name) {
            std::string username = userJson["username"].asString();
            std::string password = userJson["password"].asString();
            std::string ruolo = userJson["ruolo"].asString();
            return new user(username, ruolo, password);
        }
    }
    return nullptr; //utente non trovato
}

void user::save() const {
    JsonFileManager jfm(pathManager::getPath("users"));
    Json::Value root = jfm.readJsonFile();

    serialize(root);

    jfm.writeJsonFile(root);
}

user* user::load(const std::string& name) {
    JsonFileManager jfm(pathManager::getPath("users"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return nullptr;
    
    return deserialize(root, name);
}

std::vector<user*> user::loadAll() {
    std::vector<user*> users;

    JsonFileManager jfm(pathManager::getPath("users"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return users;

    for(const auto& userJson : root["users"]) {
        std::string username = userJson["username"].asString();
        user* u = deserialize(root, username);
        if(u) users.push_back(u);
    }
    return users;
}

void user::remove(const std::string& name) {
    JsonFileManager jfm(pathManager::getPath("users"));
    Json::Value root = jfm.readJsonFile();

    if(root.isNull())
        return;

    Json::Value& usersArray = root["users"];
    Json::Value newUsersArray(Json::arrayValue); //creiamo un nuovo array

    for (unsigned int i=0; i<usersArray.size(); ++i) {
        const Json::Value& userJson = usersArray[i];
        if(userJson["username"].asString() != name) {
            newUsersArray.append(userJson);
        }
    }
    root["users"] = newUsersArray;

    jfm.writeJsonFile(root);
}