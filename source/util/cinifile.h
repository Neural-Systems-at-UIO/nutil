#pragma once
//#include "cutil.h"
#include <string>
#include <vector>
#include <iostream>
#include <QString>
#include <QDebug>

class CItem {
public:
    string name, strval;
    double dval;
};

class CIniFile  {
public:
    string filename;

    vector<CItem> items;

    void load(string fname) {
        CUtil::verify_file(fname);

        fstream f(fname.c_str(), ios::in);
        if (!f)
            throw string("Could not load file "+filename);

        char s[2000];
        string er = "";
        while(!f.eof()) {
            f.getline(s,2000);
            vector<string> tok;
            CUtil::Tokenize(s, tok,"=");
            if (tok.size()==2) {
                CItem it;
                it.dval = -1;
                it.name = CUtil::trim(tok[0]);
                it.strval = CUtil::trim(tok[1]);
                try {
                    it.dval  = strtod(tok.at(1).c_str(),0);
                } catch(...) {
                }
                items.push_back(it);
            }
        }
        f.close();
    }

    string getstring(string name) {
        for (unsigned int i=0;i<items.size();i++) {
            if (items[i].name==CUtil::trim(name))
                return items[i].strval;
        }
        throw string("Could not find any parameter '" + name +"'");
    }

    unsigned char getchar(string name) {
        for (unsigned int i=0;i<items.size();i++) {
            if (items[i].name==CUtil::trim(name))
                return items[i].strval[0];
        }
        throw string("Could not find any parameter '" + name +"'");
    }


    bool getbool(string name) {
        for (unsigned int i=0;i<items.size();i++) {
            if (items[i].name==CUtil::trim(name)) {
                if (items[i].strval=="true")
                    return true;
                return false;
            }
        }
        throw string("Could not find any parameter '" + name +"'");
    }

    int getint(string name) {
        for (unsigned int i=0;i<items.size();i++) {
            if (items[i].name==CUtil::trim(name))
                return (int)items[i].dval;
        }
        throw string("Could not find any parameter '" + name +"'");
    }

    double getdouble(string name) {
        for (unsigned int i=0;i<items.size();i++) {
            if (items[i].name==CUtil::trim(name))
                return items[i].dval;
        }
        throw string("Could not find any parameter '" + name +"'");
    }

    bool find(QString key, QString value) {
        QString actualValue = QString::fromStdString(getstring(key.toLower().toStdString()));
        return value.toLower().compare(actualValue) == 0;
    }

    bool find(QString key, int value) {
        return getint(key.toStdString()) == value;
    }

    bool find(QString key, bool value) {
        return getbool(key.toStdString()) == value;
    }
};
