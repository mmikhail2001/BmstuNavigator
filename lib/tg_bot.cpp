#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <tgbot/tgbot.h>

#include "tg_bot.h"

using namespace std;
using namespace TgBot;



Keyboard::Keyboard(const vector<string>& buttonStrings)
{
    cout << "Keyboard" << endl;
    kb = new ReplyKeyboardMarkup::Ptr;

};
Keyboard::~Keyboard()
{
    delete kb;
}

//_________________________________________________________________________________

Search::Search()
{
    cout << "Constructor Search" << endl;
}
vector<string> Search::FindRoute(const string& point1, const string& point2)
{
    cout << "Route search between " << point1 << " and " << point2 << "..." << endl;
    return {"310->312.jpeg", "312->316.jpeg"};
}
bool Search::HavePoint(const string &point)
{
    cout << "HavePoint Point is found!" << endl;   
    return true;
}


//_________________________________________________________________________________

StartKeyboard::StartKeyboard(const vector<string>& buttonStrings) : Keyboard(buttonStrings)
{
    cout << "StartKeyboard" << endl;
}

//_________________________________________________________________________________


CategoricalKeyboard::CategoricalKeyboard(const vector<string>& buttonStrings, const vector<vector<string>>& inlineKeyboards)
                                                                                                    : Keyboard(buttonStrings)
{
    cout << "Constructor CategoricalKeyboard" << endl;
    for (size_t i = 0; i < buttonStrings.size(); i++)
    {
        cout << buttonStrings[i] << endl;
        CreateInlineKeyboard(buttonStrings[i], inlineKeyboards[i]);
    }
}

void CategoricalKeyboard::CreateInlineKeyboard(const string& category, const vector<string>& inButtonStrings)
{
    cout << "Constructor SetInlineKeyboard" << endl;
    map_inline_kbs[category] = inButtonStrings;
}

//_________________________________________________________________________________

BotManager::BotManager()
{
    cout << "Constructor BotManager" << endl;
}
void BotManager::Create_CategoricalKeyboard(const vector<string>& buttons_category_kb,
                            const vector<vector<string>>& buttons_inline_kbs)
{
    assert(buttons_category_kb.size() == buttons_inline_kbs.size());
    categoricalKeyboard = new CategoricalKeyboard(buttons_category_kb, buttons_inline_kbs);
}
void BotManager::Create_StartKeyboard(const vector<string>& buttons_start_kb)
{
    startKeyboard = new StartKeyboard(buttons_start_kb);
}
int BotManager::SetStartEnd(string value)
{
    if (!start_point && search.HavePoint(value))
    {
        start_point = new string;
        *start_point = value;
        return 1;
    }
    if (!end_point && search.HavePoint(value))
    {
        end_point = new string;
        *end_point = value;
        return 2;
    }
    return 0;
}
bool BotManager::Find()
{
    if (!start_point || !end_point)
    {
        return false;
    }
    // images = new vector<string>;
    images = search.FindRoute(*start_point, *end_point);
    return true;
}

BotManager::~BotManager()
{
    if (categoricalKeyboard)
    {
        delete categoricalKeyboard;
    }
    if (startKeyboard)
    {
        delete startKeyboard;
    }
    if (start_point)
    {
        delete start_point;
    }
    if (end_point)
    {
        delete end_point;
    }
}

//_________________________________________________________________________________


VideoRoute::VideoRoute()
{
    cout << "Constructor Video" << endl;
}
string VideoRoute::ConvertVideo(const vector<string> &images)
{
    cout << "ConvertVideo" << endl;
    video_path = "Route.mp4";
    return video_path;
}
//_________________________________________________________________________________

Messenger::Messenger()
{
    cout << "Constructor Messenger" << endl;
}
void Messenger::MessageProcessing(int code_msg)
{
    switch(code_msg)
    {
        case 1: // "Установить пункт отправления"
        {
            start_point = nullptr;
            end_point = nullptr;
            SendMessage("Введите пункт отправления");
            break;
        }
        case 2: // "Установить пункт назначения"
        {
            end_point = nullptr;
            SendMessage("Введите пункт назначения");
            break;
        }
        case 3: // "Найти маршрут"
        {
            bool result = Find();
            if (!result)
            {
                SendMessage("Route is not found"); 
            }
            SendMessage("Route is found!"); 
            ShowResults();
            break;
        }
        default:
        {
            string msg = to_string(code_msg);
            int code_set_point = SetStartEnd(msg);
            switch (code_set_point)
            {
                case 0:
                {
                    SendMessage("Point is not found");
                    break;
                }
                case 1:
                {
                    SendMessage("Point Start set");
                    break;
                }
                case 2:
                {
                    SendMessage("Point End set");
                    break;
                }
            }
        }
    }
}

void Messenger::SendMessage(string message)
{
    cout << message << endl;
}
void Messenger::ShowResults()
{
    video = new VideoRoute;
    string videoPath = video->ConvertVideo(images);
    for (string image : images)
    {
        cout << image << " ";
    }
    cout << endl << "ShowResults" << endl;
}
Messenger::~Messenger()
{
    if (video)
    {
        delete video;
    }
}
