#pragma once
#include "myText.h"

using namespace std;
using namespace sf;
class TextField: public myText {
    string value;
    string placeHolder;
    bool focus,encrypt;
public:
   TextField() {
        text.setFillColor(Color(208, 208, 208));
        text.setCharacterSize(22);
        font.loadFromFile("fonts\\Paddington.ttf");
        text.setFont(font);
        encrypt = false;
        placeHolder = "";
        reset();
    }
   void setPlaceHolder(string a) {
       placeHolder = a;
   }
   void reset() {
       text.setString("");
       value = "";
       focus = false;
   }
   void setEncryption(bool cond) {
       encrypt = cond;
   }
    void getCharacter(char c) {
        if (focus) {
            if ((isalpha(c) || isdigit(c)) && value.length() <= 16)
                value += c;
            else if ((c == 8) && value.length() > 0) //8 is ASCII for backspace
                value.pop_back();
        }
    }
    string getString() {
        return value;
    }
    void update() {
        if (!focus && value.length() == 0) {
            text.setFillColor(Color(208, 208, 208));
            text.setString(placeHolder);
        }
        else if (focus) {
            text.setFillColor(Color::Black);
            if (!encrypt)
                text.setString(value);
            else {
                string temp = "";
                for (size_t i = 0; i < value.length(); i++)
                {
                    temp += "*";
                }
                text.setString(temp);
            }
        }
    }
    void setFocus(bool cond) {
        focus = cond;
    }
    bool isFocus() {
        return focus;
    }
};



