#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include <string>
#include"global.h"
using namespace std;
    class myFile
{
    string fileName;
    vector <Record> myRecords;

    vector<string> split_sentence(string b, char delim) {
        vector<string> a;
        string temp = "";
        for (size_t i = 0; i < b.length(); i++)
        {
            if (b[i] == delim) {
                a.push_back(temp);
                temp = "";
            }
            else
                temp += b[i];
        }
        return a;
    }
    string encrypt(string temp)
    {
        string local;
        int key = temp.length() / 2;
        for (size_t i = 0; i < temp.length(); i++)
        {
            char c;
            if (temp[i] + key > 127)
            {
                c = key - 127 + temp[i];
            }
            else c = temp[i] + key;
            local += c;
        }
        return local;
    }
    string decrypt(string temp)
    {
        string local;
        int key = temp.length() / 2;
        for (size_t i = 0; i < temp.length(); i++)
        {
            char c;
            if (temp[i] - key < 0)
            {
                c = 127 - key + temp[i];
            }
            else c = temp[i] - key;
            local += c;
        }
        return local;
    }
public:
    myFile(string a) {
        fileName = a;
    }
    vector<Record> get_All_Records() {
        return myRecords;
    }
    void write_Records() {
        fstream fout;
        fout.open(fileName, ios::out);
        for (size_t i = 0; i < myRecords.size(); i++)
        {
            fout << encrypt(myRecords[i].name) << ","
                << encrypt(myRecords[i].password) << ","
                << encrypt(to_string(myRecords[i].waveLevel)) << ","
                << encrypt(to_string(myRecords[i].score[0])) << ","
                << encrypt(to_string(myRecords[i].score[1])) << ","
                << encrypt(to_string(myRecords[i].score[2])) << ","
                << '\n';
        }
        fout.close();
    }
    bool doesRecordExist(string a) {
         for (size_t i = 0; i < myRecords.size(); i++)
        {
            if (a == myRecords[i].name) {
                return true;
            }
        }
         return false;
    }

    void add_Record(Record a)
    {
        myRecords.push_back(a);
    }
    void update_record(Record temp) {
        for (size_t i = 0; i < myRecords.size(); i++)
        {
            if (myRecords[i].name == temp.name) {
                myRecords[i].score[0] = temp.score[0];
                myRecords[i].score[1] = temp.score[1];
                myRecords[i].score[2] = temp.score[2];
                myRecords[i].waveLevel = temp.waveLevel;
            }
        }
    }
    bool validate_Record(string userName, string password) {
        if (doesRecordExist(userName)) {
            for (size_t i = 0; i < myRecords.size(); i++)
            {
                if (userName == myRecords[i].name && password == myRecords[i].password) {
                    return true;
                }
            }
        }
        return false;
    }
    Record get_Record(string userName) {
        for (size_t i = 0; i <  myRecords.size(); i++)
        {
            if (userName == myRecords[i].name) {
                return myRecords[i];
            }
        }
        return Record(); //returns an initialized structure
    }
    void read_Records()
    {
        myRecords.clear();
        fstream fin;
        fin.open(fileName, ios::in);
        string line;
        vector<string> temp;
        Record temporaryRecord;
        while (fin) {
            getline(fin, line);
            if (line == "") break; //The last line which we dont want in our vector
            temp = split_sentence(line, ',');
            temporaryRecord.name = decrypt(temp[0]);
            temporaryRecord.password = decrypt(temp[1]);
            temporaryRecord.waveLevel = stoi(decrypt(temp[2]));
            temporaryRecord.score[0] = stoi(decrypt(temp[3]));
            temporaryRecord.score[1] = stoi(decrypt(temp[4]));
            temporaryRecord.score[2] = stoi(decrypt(temp[5]));
            myRecords.push_back(temporaryRecord);
            temp.clear();
        }
        fin.close();
    }
};