#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <string_view>
#include <iostream>
#include <string>

#include "../search_lib/search.h"
#include "../search_lib/database.h"
#include "../search_lib/database.h"

// #include "tg_bot.h"

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

static const std::string CATEG = "category";
static const std::string VIDEO = "video";
static const std::string TEXT = "text";
static const std::string CALLBACK = "callback";
static const std::string SELECT = "select";
static const std::string SYS= "commands";

enum STATE_MESSAGE {DONE, NOT_FOUND, POS_FILLED};

inline constexpr auto hash_djb2a(const std::string_view sv) {
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}
 
inline constexpr auto operator"" _sh(const char *str, size_t len) {
    return hash_djb2a(std::string_view{ str, len });
}
// struct Route
// {
//     std::vector<std::string> images;
// };

std::vector <BasePoint> fillTestBasePoints1() {
    BasePoint a(1), b(2), c(3), d(4);
    // base
    {
        Edge edge(1, 2, 2, "1->2.txt");
        a.AddEdge(edge);
    }
    {
        Edge edge(1, 4, 1, "1->4.txt");
        a.AddEdge(edge);
    }
    // infr
    {
        Edge edge(1, 9, 5, "1->9.txt");
        a.AddEdge(edge);
    }
    {
        Edge edge(1, 10, 2, "1->10.txt");
        a.AddEdge(edge);
    }
    {
        Edge edge(1, 11, 2, "1->11.txt");
        a.AddEdge(edge);
    }
    {
        Edge edge(1, 102, 1, "1->canteen.txt");
        a.AddEdge(edge);
    }

    // base
    {
        Edge edge(2, 1, 2, "2->1.txt");
        b.AddEdge(edge);
    }
    {
        Edge edge(2, 3, 5, "2->3.txt");
        b.AddEdge(edge);
    }
    // infr
    {
        Edge edge(2, 10, 0, "2->10.txt");
        b.AddEdge(edge);
    }
    {
        Edge edge(2, 11, 1, "2->11.txt");
        b.AddEdge(edge);
    }
    {
        Edge edge(2, 12, 2, "2->12.txt");
        b.AddEdge(edge);
    }
    {
        Edge edge(2, 13, 3, "2->13.txt");
        b.AddEdge(edge);
    }

    // base
    {
        Edge edge(3, 2, 5, "3->2.txt");
        c.AddEdge(edge);
    }
    {
        Edge edge(3, 4, 2, "3->4.txt");
        c.AddEdge(edge);
    }
    // infr
    {
        Edge edge(3, 12, 1, "3->12.txt");
        c.AddEdge(edge);
    }
    {
        Edge edge(3, 13, 1, "3->13.txt");
        c.AddEdge(edge);
    }

    // base
    {
        Edge edge(d.GetId(), 1, 1, "4->1.txt");
        d.AddEdge(edge);
    }
    {
        Edge edge(d.GetId(), 3, 2, "4->3.txt");
        d.AddEdge(edge);
    }
    // infr
    {
        Edge edge(d.GetId(), 103, 1, "4->canteen.txt");
        d.AddEdge(edge);
    }

    std::vector <BasePoint> graf = {a, b, c, d};
    return graf;
}

std::vector <Infrastructure> fillInfrPoints1() {
    Infrastructure i9(9), i10(10), i11(11), i12(12), i13(13), i102(102), i103(103);

    i9.AddName("399u");
    {
        Edge edge(i9.GetId(), 1, 5, "9->1.txt");
        i9.AddEdge(edge);
    }

    i10.AddName("400u");
    {
        Edge edge(i10.GetId(), 1, 2, "10->1.txt");
        i10.AddEdge(edge);
    }
    {
        Edge edge(i10.GetId(), 2, 0, "10->2.txt");
        i10.AddEdge(edge);
    }

    i11.AddName("401u");
    {
        Edge edge(i11.GetId(), 1, 2, "11->1.txt");
        i11.AddEdge(edge);
    }
    {
        Edge edge(i11.GetId(), 2, 1, "11->2.txt");
        i11.AddEdge(edge);
    }

    i12.AddName("402u");
    {
        Edge edge(i12.GetId(), 2, 2, "12->2.txt");
        i12.AddEdge(edge);
    }
    {
        Edge edge(i12.GetId(), 3, 1, "12->3.txt");
        i12.AddEdge(edge);
    }

    i13.AddName("403u");
    {
        Edge edge(i13.GetId(), 2, 2, "13->2.txt");
        i13.AddEdge(edge);
    }
    {
        Edge edge(i13.GetId(), 3, 1, "13->3.txt");
        i13.AddEdge(edge);
    }

    i102.AddName("canteen");
    i102.AddName("canteen2");
    {
        Edge edge(i102.GetId(), 1, 1, "canteen->1.txt");
        i102.AddEdge(edge);
    }

    i103.AddName("canteen");
    i103.AddName("canteen3");
    i103.AddName("canteen_near_physics");
    {
        Edge edge(i103.GetId(), 4, 1, "canteen->4.txt");
        i103.AddEdge(edge);
    }

    std::vector <Infrastructure> graf = {i9, i10, i11, i12, i13, i102, i103};
    return graf;
}

class DataBaseTest : public DataBase {
public:
    std::vector <BasePoint> getBasePoints() override {
        return fillTestBasePoints1();
    }
    std::vector <Infrastructure> getInfrastructurePoints() override {
        return fillInfrPoints1();
    }
};


struct Positions
{
    Positions() : currentPointer(0) {}
    std::string start = std::string();
    std::string end = std::string();
    int currentPointer; 
};

// class DataBase
// {

// };

// class DataBaseBMSTU : public DataBase
// {

// };


// class Search
// {
// public:
//     Search (DataBase *db) : db(db) {}
//     Route *FindRoute(const Positions &pos)
//     {
//         Route *route = new Route; 
//         route->images.push_back("mem.jpg"); 
//         route->images.push_back("apple.jpg"); 
//         // route->images.push_back("video.mp4"); 
//         return route;
//     }
//     bool HavePoint(std::string point)
//     {
//         return true;
//     }
// private:
//     DataBase *db;
// };

class IModel
{
public:
    IModel(DataBase *db) : search(db) {};
    virtual std::vector<std::string> FindRouteModel(const Positions &pos) = 0;
    virtual bool isValid(std::string point) = 0;
protected:
    Search search;
};

class Model : public IModel
{
public:
    Model(DataBase *db) : IModel(db) {}
    std::vector<std::string> FindRouteModel(const Positions &pos) 
    {
        std::vector<Point*> points = search.GetByName(pos.start);
        if (points.size())
        {
            unsigned int id = points[0]->GetId();
            Route route = search.FindRoute(id, pos.end);
            std::vector<std::string> vecPath = route.GetLinks();
            return vecPath;
        }
        throw std::runtime_error("error");
        // Route *route = search.FindRoute(pos);
        // return route;
    }
    bool isValid(std::string point)
    {
        std::cout << point << " " << search.HavePoint(point) << std::endl;
        return search.HavePoint(point);
    }
};


class Message
{
public:
    Message(std::vector<std::string> vecImages, int chatId) : vecImages(vecImages), chatId(chatId) {}
    Message(std::string text, int chatId) : text(text), chatId(chatId) {}
    Message(const Message &other) = delete;
    std::string GetText()
    {
        return text;
    }
    int GetChatId()
    {
        return chatId;
    }
    std::vector<std::string> vecImages;
private:
    std::string text = std::string();
    int chatId = int();
};

class IView
{
public:
    IView(std::string type) : type(type) {}
    virtual void SendMessage(Message &msg) = 0;
    std::string GetTypeView()
    {
        return type;
    }
protected:
    std::string type;
};


class InlineView : public IView
{
public:
    InlineView(std::string type, InlineKeyboardMarkup::Ptr inlineKb, Bot *bot) : IView(type), bot(bot), inlineKb(inlineKb) {};
    void SendMessage(Message &msg)
    {
        bot->getApi().sendMessage(msg.GetChatId(), msg.GetText(), false, 0, inlineKb);
    }
    // void SendRoute(Images &images)
    // {
    //     // std::vector<InputMedia::Ptr> vec;
    //     // for (auto &image : images.GetImages())
    //     // {
    //     //     InputMediaPhoto::Ptr photo(new InputMediaPhoto);
    //     //     photo->media = image;
    //     //     photo->media = InputFile::fromFile(image, "image/jpeg")
    //     //     vec.push_back(photo);
    //     // }
    //     // bot->getApi().sendMediaGroup(images.GetChatId(), vec);
        
    //     bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
    // }
private:
    InlineKeyboardMarkup::Ptr inlineKb;
    Bot *bot;
};


class MessageView : public IView
{
public:
    MessageView(std::string type, Bot *bot) : IView(type), bot(bot) {};
    void SendMessage(Message &msg)
    {
        bot->getApi().sendMessage(msg.GetChatId(), msg.GetText());
    }
    // void SendRoute(Images &images)
    // {
        // bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
    // }
private:
    Bot *bot;
};

class VideoView : public IView
{
public:
    VideoView(std::string type, Bot *bot) : IView(type), bot(bot) {};
    // void SendMessage(Message &msg)
    // {
    //     // bot->getApi().sendPhoto(msg.GetChatId(), InputFile::fromFile(msg.GetText(), "image/jpeg"));
    //     // bot->getApi().sendMessage(msg.GetChatId(), msg.GetText());
    //     bot->getApi().sendVideo(msg.GetChatId(), InputFile::fromFile(msg.GetText(), "video/mp4"));
        
    // }
    void SendMessage(Message &msg)
    {
        std::vector<InputMedia::Ptr> vec;
        for (auto &image : msg.vecImages)
        {
            InputMediaPhoto::Ptr photo(new InputMediaPhoto);
            // photo->media = "attach://" + image;
            photo->media = "https://img.mvideo.ru/Big/small_pic/480/30063081bb.jpg";
            // photo->media = InputFile::fromFile(image, "image/jpeg");
            vec.push_back(photo);
        }
        // std::string js = "{\"type\": \"photo\", \"media\": \"mem.jpg\"}";
        bot->getApi().sendMediaGroup(msg.GetChatId(), vec);
        
        // bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
    }
private:
    Bot *bot;
};


class IPresenter
{
public:
    IPresenter(vector<IView *> vecViews_, IModel *model) :  model(model), vecViews(vecViews_) {}
    virtual void Check(Message &msg) = 0;
    IView *FindView(std::string type)
    {
        auto view = std::find_if(vecViews.begin(), vecViews.end(), [&type](IView *view){
            return type == view->GetTypeView();
        });
        if (view != vecViews.end())
        {
            return *view;
        }
        return nullptr;
    }
protected:
    IModel *model;
    STATE_MESSAGE SetPosition(std::string str_point)
    {
        if (model->isValid(str_point))
        {
            if (pos.start.empty())
            {
                pos.start = str_point;
                return DONE;
            }
            else if (pos.end.empty()) 
            {   
                pos.end = str_point;
                return DONE;
            }
        }
        else 
        {
            return NOT_FOUND;
        }
        return POS_FILLED;
    }
    const Positions &GetPos()
    {
        return pos;
    }
    bool isReady()
    {
        return !pos.start.empty() && !pos.end.empty();
    }
    void Info(int chatId)
    {
        std::string currentState = "Текущее состояние.\nНачальная позиция: " + (pos.start.empty() ? "-" : pos.start) + "\nКонечная позиция: " + (pos.end.empty() ? "-" : pos.end);
        Message outputMsg(currentState, chatId);
        if (IView *view = FindView(TEXT))
        {
            view->SendMessage(outputMsg);
        }
    }
    void Clear()
    {
        pos.start.clear();
        pos.end.clear();
    }
private:
    Positions pos;
    std::vector<IView *> vecViews;
};

class Presenter : public IPresenter
{
public:
    Presenter(vector<IView *> vecViews_, IModel *model, nlohmann::json j) : IPresenter(vecViews_, model), j(j) {}
    void Check(Message &msg) 
    {
        if (StringTools::startsWith(msg.GetText(), "/"))
        {
            CheckCommand(msg);
        }
        else 
        {
            CheckCallback(msg);
        }
    }
private:
    nlohmann::json j;
    void CheckCallback(Message &msg) 
    {
        // std::cout << TypeInput(j.at(CATEG), msg.GetText()) << std::endl;
        switch(hash_djb2a(msg.GetText()))
        {
            case "dining"_sh:
            case "audit"_sh:
            case "toilet"_sh:
            {
                Message outputMsg("Выберите: " + std::string(j.at(CATEG).at(msg.GetText()).at(TEXT)), msg.GetChatId());
                if (IView *view = FindView(msg.GetText()))
                {
                    view->SendMessage(outputMsg);
                }
                break;
            }
            default:
            {
                std::string message = msg.GetText();
                for (auto &elem : j.at(CATEG))
                {
                    if (elem.at(CALLBACK) == msg.GetText())
                    {
                        message = elem.at(TEXT);
                        break;
                    }
                    if (elem.contains(SELECT) && elem.at(SELECT).contains(msg.GetText()))
                    {
                        message = elem.at(SELECT).at(msg.GetText()).at(TEXT);
                        break;
                    }
                }
                STATE_MESSAGE code = SetPosition(message);
                for (auto &elem : j.at("messages"))
                {
                    if (elem.at("id") == code)
                    {
                        Message outputMsg(std::string(elem.at("text")), msg.GetChatId()); 
                        if (IView *view = FindView(TEXT))
                        {
                            view->SendMessage(outputMsg);
                        }
                        break;
                    }
                }
                Info(msg.GetChatId());
            }
        }
    }

    // int TypeInput(nlohmann::json j, const std::string &input)
    // {
    //     for (auto &object : j)
    //     {   
    //         if (object.contains(SELECT))
    //         {
    //             std::cout << "S " << std::string(object.at(CALLBACK)) << " " << input << std::endl;
    //             if (std::string(object.at(CALLBACK)) == input)
    //             {
    //                 return 2;
    //             }
    //             return TypeInput(object.at(SELECT), input);
    //         }
    //         else
    //         {
    //             std::cout << "NS " << object.at(CALLBACK) << std::endl;
    //             if (std::string(object.at(CALLBACK)) == input)
    //             {
    //                 return 1;
    //             }
    //         }
    //     }
    //     return 0;
    // }

    void CheckCommand(Message &msg) 
    {
        switch(hash_djb2a(msg.GetText()))
        {
            case "/start"_sh:
            case "/reset"_sh:
            {
                Clear();
            }
            case "/categ"_sh:
            {
                Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
                if (IView *view = FindView(CATEG))
                {
                    view->SendMessage(outputMsg);
                }
                break;
            }
            case "/go"_sh:
            {
                if (isReady())
                {
                    // Route *route = model->FindRouteModel(GetPos());
                    std::vector<std::string> vecPath = model->FindRouteModel(GetPos());
                    std::string str; 
                    for (auto &elem : vecPath) str += elem; 
                    Message videoMsg(str, msg.GetChatId());
                    if (IView *view = FindView(TEXT))
                    {
                        view->SendMessage(videoMsg);
                    }
                }
                else 
                {
                    Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
                    if (IView *view = FindView(TEXT))
                    {
                        view->SendMessage(outputMsg);
                    }
                    Info(msg.GetChatId());
                }
                break;
            }
            default:
            {
                Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
            }
        }
    }
};

void createInlineKeyboard(const std::vector<std::string>& buttonStrings, const std::vector<std::string>& callbacks, InlineKeyboardMarkup::Ptr& kb)
{
    assert(buttonStrings.size() == callbacks.size() && "wrong size button and callbacks");
    for (size_t i = 0; i < buttonStrings.size(); ++i) {
        std::vector<InlineKeyboardButton::Ptr> row;
        InlineKeyboardButton::Ptr button(new InlineKeyboardButton);
        button->text = buttonStrings[i];
        button->callbackData = callbacks[i];
        row.push_back(button);
        kb->inlineKeyboard.push_back(row);
    }
}

InlineKeyboardMarkup::Ptr CreateKeyboard(const nlohmann::json &j)
{
    std::vector<std::string> vecButtons;
    std::vector<std::string> vecCallback;
    for (auto elem : j)
    {
        vecButtons.push_back(elem.at(TEXT));
        vecCallback.push_back(elem.at(CALLBACK));
    }
    InlineKeyboardMarkup::Ptr inlineKb(new InlineKeyboardMarkup);
    createInlineKeyboard(vecButtons, vecCallback, inlineKb);
    return inlineKb;
}

void CreateViews(std::vector<IView *> &vecViews, const std::string &parent_name, const nlohmann::json &j, Bot &bot)
{
    {
        auto inlineKb = CreateKeyboard(j);
        vecViews.push_back(new InlineView(parent_name, inlineKb, &bot)); 
    }
    for (auto &object : j.items())
    {
        if (object.value().contains(SELECT))
        {
            // std::cout << object.key() << std::endl;
            CreateViews(vecViews, std::string(object.key()), object.value().at(SELECT), bot);
        }
    }
}
