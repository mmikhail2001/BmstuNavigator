#pragma once

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

class Keyboard
{
public:
    Keyboard(const vector<string>& buttonStrings);
    ~Keyboard();
protected:
    ReplyKeyboardMarkup::Ptr *kb = nullptr;
};


//_________________________________________________________________________________

class Search
{
public:
    Search();
    virtual vector<string> FindRoute(const string& point1, const string& point2);
    virtual bool HavePoint(const string &point);
};

//_________________________________________________________________________________

class StartKeyboard : public Keyboard 
{
public:
    StartKeyboard(const vector<string>& buttonStrings);
};

//_________________________________________________________________________________


class CategoricalKeyboard : public Keyboard 
{
public:
    CategoricalKeyboard(const vector<string>& buttonStrings, const vector<vector<string>>& inlineKeyboards);

    void CreateInlineKeyboard(const string& category, const vector<string>& inButtonStrings);
protected:
    // unordered_map<std::string, InlineKeyboardMarkup::Ptr> map_inline_kbs; 
    unordered_map<string, vector<string>> map_inline_kbs; 
};

//_________________________________________________________________________________


class BotManager
{
public:
    BotManager();
    void Create_CategoricalKeyboard(const vector<string>& buttons_category_kb,
                             const vector<vector<string>>& buttons_inline_kbs);
    void Create_StartKeyboard(const vector<string>& buttons_start_kb);
    int SetStartEnd(string value);
    bool Find();
    ~BotManager();
protected:
    CategoricalKeyboard *categoricalKeyboard = nullptr; 
    StartKeyboard *startKeyboard = nullptr; 
    Search search;
    vector<string> images; 
    string *start_point = nullptr;
    string *end_point = nullptr;
};

//_________________________________________________________________________________

class VideoRoute
{
public:
    VideoRoute();
    string ConvertVideo(const vector<string> &images);
private:
    string video_path;  
};

//_________________________________________________________________________________

class Messenger : public BotManager
{
public:
    Messenger();
    void MessageProcessing(int code_msg);
    virtual void SendMessage(string message);
    void ShowResults();
    ~Messenger();
private:
    VideoRoute *video = nullptr;
};