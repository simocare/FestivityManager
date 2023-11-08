#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <json/json.h>
#include <vector>

#include "jsonFileManager.h"
#include "pathManager.h"

class user {
private:    
    std::string username;
    std::string password;
    std::string ruolo;

public:
    user(const std::string& name , const std::string& ruolo, const std::string& password = "");
    user(const user&);

    user& operator=(const user&);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRuolo() const;
    void setUsername(const std::string&);
    void setPassword(const std::string&);
    void setRuolo(const std::string&);

    void serialize(Json::Value&) const;
    static user* deserialize(const Json::Value&, const std::string&);

    static void remove(const std::string&);
    void save() const;
    static user* load(const std::string&);
    static std::vector<user*> loadAll();
};

#endif