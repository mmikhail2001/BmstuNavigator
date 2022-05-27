#ifndef TG_BOT_H
#define TG_BOT_H

#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <string_view>
#include <string>

using TgBot::Bot;
using TgBot::ReplyKeyboardMarkup;
using TgBot::InlineKeyboardMarkup;
using TgBot::KeyboardButton;
using TgBot::InlineKeyboardButton;
using TgBot::ReplyKeyboardRemove;
using TgBot::InputFile;
using TgBot::InputMediaPhoto;
using TgBot::InputMedia;
using std::vector;
using std::string;

enum SET_POS {DONE, NOT_FOUND, POS_FILLED};
enum TYPE_INPUT {NONE = 0, SHEET, NODE};


static const std::string CATEG = "category";
static const std::string VIDEO = "video";
static const std::string TEXT = "text";
static const std::string CALLBACK = "callback";
static const std::string SELECT = "select";
static const std::string SYS = "commands";
static const std::string WARNING = "warnings";


struct Positions
{
    std::string start_id = std::string();
    std::string start_view = std::string();

    std::string end_id = std::string();
    std::string end_view = std::string();
};

// заглушки классов сокомандника
struct Route;

class DataBase {};

class DataBaseBMSTU : public DataBase {};


class Search
{
public:
    Search (DataBase *db);

    Route *FindRoute(const Positions &pos);

    bool HavePoint(std::string point);
    
private:
    DataBase *db;
};

// мои классы 
class IModel
{
public:

    virtual std::string FindRouteModel(const Positions &pos) = 0;
    
    virtual bool isValid(std::string point) = 0;
};

class Model : public IModel
{
public:
    Model(DataBase *db);

    std::string FindRouteModel(const Positions &pos);

    bool isValid(std::string point);

private:
    std::string convertVideo(std::vector<std::string> images);
    Search search;
};


class Message
{
public:
    Message(std::string text, int chatId);

    std::string GetText();

    int GetChatId();

private:
    std::string text;
    int chatId;
};

class IView
{
public:
    IView(std::string type);

    virtual void SendMessage(Message &msg) = 0;
    virtual ~IView() {};
    virtual std::string GetTypeView();


protected:
    std::string type;
};


class InlineView : public IView
{
public:
    InlineView(std::string type, InlineKeyboardMarkup::Ptr inlineKb, Bot *bot);
    virtual void SendMessage(Message &msg);

private:
    InlineKeyboardMarkup::Ptr inlineKb;
    Bot *bot;
};


class MessageView : public IView
{
public:
    MessageView(std::string type, Bot *bot);
    virtual void SendMessage(Message &msg);

private:
    Bot *bot;
};

class VideoView : public IView
{
public:
    VideoView(std::string type, Bot *bot);
    virtual void SendMessage(Message &msg);

private:
    Bot *bot;
};


class IPresenter
{
public:
    IPresenter(vector<IView *> vecViews_, IModel *model);

    virtual void Check(Message &msg) = 0;


protected:
    IModel *model;

    IView *FindView(std::string type);
    
    // устанавливает начальную или конечную точку
    SET_POS SetPosition(std::string pos_id, std::string pos_view);

    const Positions &GetPos();

    // проверка готовности построить маршрут
    bool isReady();

    // генерирует сообщение о текущем состоянии
    void Info(int chatId);

    void Clear();

private:
    Positions pos;
    std::vector<IView *> vecViews;
};

class Presenter : public IPresenter
{
public:
    Presenter(vector<IView *> vecViews_, IModel *model, nlohmann::json j);

    // обработка входящего сообщения
    void Check(Message &msg);
private:
    nlohmann::json j;

    void CheckCallback(Message &msg);
    // определяет тип входящего сообщение
    std::pair<TYPE_INPUT, std::string> TypeInput(nlohmann::json j, const std::string &input);

    void CheckCommand(Message &msg);
};

void createInlineKeyboard(const std::vector<std::string>& buttonStrings, const std::vector<std::string>& callbacks, InlineKeyboardMarkup::Ptr& kb);

// подготовка данных для создания клавиатуры
InlineKeyboardMarkup::Ptr CreateKeyboard(const nlohmann::json &j);

// парсит json и создает все представления
template<class ConcreteView>
void CreateViews(std::vector<IView *> &vecViews, const std::string &parent_name, const nlohmann::json &j, Bot &bot)
{
    {
        auto inlineKb = CreateKeyboard(j);
        vecViews.push_back(new ConcreteView(parent_name, inlineKb, &bot)); 
    }
    for (auto &object : j.items())
    {
        if (object.value().contains(SELECT))
        {
            CreateViews<ConcreteView>(vecViews, std::string(object.key()), object.value().at(SELECT), bot);
        }
    }
}

#endif