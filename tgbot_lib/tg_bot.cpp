#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <string_view>
#include <iostream>
#include <string>

#include "tg_bot.h"

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


// switch-case for std::string
inline constexpr auto hash_djb2a(const std::string_view sv) 
{
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) 
    {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}
 
inline constexpr auto operator"" _sh(const char *str, size_t len) 
{
    return hash_djb2a(std::string_view{ str, len });
}

// заглушки классов сокомандника
struct Route
{
    std::vector<std::string> images = { "123->127.jpg", "127->134.jpg" };
};



Search::Search (DataBase *db) : db(db) {}

Route *Search::FindRoute(const Positions &pos)
{
    Route *route = new Route; 
    return route;
}
bool Search::HavePoint(std::string point)
{
    return true;
}

// мои классы 

Model::Model(DataBase *db) : search(db) {}

std::string Model::FindRouteModel(const Positions &pos) 
{
    return convertVideo(search.FindRoute(pos)->images);
}
bool Model::isValid(std::string point)
{
    return search.HavePoint(point);
}
std::string Model::convertVideo(std::vector<std::string> images)
{
    return "video.mp4";
}



Message::Message(std::string text, int chatId) : text(text), chatId(chatId) {}

std::string Message::GetText()
{
    return text;
}
int Message::GetChatId()
{
    return chatId;
}

IView::IView(std::string type) : type(type) {}

std::string IView::GetTypeView()
{
    return type;
}


InlineView::InlineView(std::string type, InlineKeyboardMarkup::Ptr inlineKb, Bot *bot) : IView(type), bot(bot), inlineKb(inlineKb) {};

void InlineView::SendMessage(Message &msg)
{
    bot->getApi().sendMessage(msg.GetChatId(), msg.GetText(), false, 0, inlineKb);
}


MessageView::MessageView(std::string type, Bot *bot) : IView(type), bot(bot) {};

void MessageView::SendMessage(Message &msg)
{
    bot->getApi().sendMessage(msg.GetChatId(), msg.GetText());
}


VideoView::VideoView(std::string type, Bot *bot) : IView(type), bot(bot) {};
void VideoView::SendMessage(Message &msg)
{
    bot->getApi().sendVideo(msg.GetChatId(), InputFile::fromFile("../" + msg.GetText(), "video/mp4"));   
}


IPresenter::IPresenter(vector<IView *> vecViews_, IModel *model) :  model(model), vecViews(vecViews_) {}

IView *IPresenter::FindView(std::string type)
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
SET_POS IPresenter::SetPosition(std::string pos_id, std::string pos_view)
{
    if (model->isValid(pos_id))
    {
        if (pos.start_id.empty())
        {
            pos.start_view = pos_view;
            pos.start_id = pos_id;
            return DONE;
        }
        else if (pos.end_id.empty()) 
        {   
            pos.end_view = pos_view;
            pos.end_id = pos_id;
            return DONE;
        }
    }
    else 
    {
        return NOT_FOUND;
    }
    return POS_FILLED;
}
const Positions &IPresenter::GetPos()
{
    return pos;
}
// проверка готовности построить маршрут
bool IPresenter::isReady()
{
    return !pos.start_id.empty() && !pos.end_id.empty();
}
// генерирует сообщение о текущем состоянии
void IPresenter::Info(int chatId)
{
    std::string currentState = "Текущее состояние.\nНачальная позиция: " + (pos.start_view.empty() ? "-" : pos.start_view) + "\nКонечная позиция: " + (pos.end_view.empty() ? "-" : pos.end_view);
    Message outputMsg(currentState, chatId);
    if (IView *view = FindView(TEXT))
    {
        view->SendMessage(outputMsg);
    }
}
void IPresenter::Clear()
{
    pos = std::move(Positions{}); 
}



Presenter::Presenter(vector<IView *> vecViews_, IModel *model, nlohmann::json j) : IPresenter(vecViews_, model), j(j) {}
// обработка входящего сообщения
void Presenter::Check(Message &msg) 
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
void Presenter::CheckCallback(Message &msg) 
{
    // p = pair<код для switch-case, текст кнопки>
    auto p = TypeInput(j.at(CATEG), msg.GetText());
    switch(p.first)
    {
        case NODE:
        {
            Message outputMsg("Выберите: " + p.second, msg.GetChatId());
            if (IView *view = FindView(msg.GetText()))
            {
                view->SendMessage(outputMsg);
            }
            break;    
        }
        case SHEET:
        case NONE:
        {
            SET_POS code = SetPosition(msg.GetText(), p.second); 
            for (auto &elem : j.at(WARNING))
            {
                if (elem.at("id") == code)
                {
                    Message outputMsg(std::string(elem.at(TEXT)), msg.GetChatId()); 
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

// определяет тип входящего сообщение: конечная точка (SHEET - лист json), категория (NODE - узел), данные введены с клавиатуры (NONE - не найдено в json)
std::pair<TYPE_INPUT, std::string> Presenter::TypeInput(nlohmann::json j, const std::string &input)
{
    for (auto &object : j)
    {   
        if (object.contains(SELECT))
        {
            if (std::string(object.at(CALLBACK)) == input)
            {
                auto p = std::make_pair(NODE, std::string(object.at(TEXT)));
                return p;
            }
            auto check_inside = TypeInput(object.at(SELECT), input);
            if (check_inside.first)
            {
                return check_inside;
            }
        }
        else
        {
            if (std::string(object.at(CALLBACK)) == input)
            {
                auto p = std::make_pair(SHEET, std::string(object.at(TEXT)));
                return p;
            }
        }
    }
    auto p = std::make_pair(NONE, input);
    return p;
}

void Presenter::CheckCommand(Message &msg) 
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
                std::string pathVideo = model->FindRouteModel(GetPos());
                Message videoMsg(pathVideo, msg.GetChatId());
                if (IView *view = FindView(VIDEO))
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

// подготовка данных для создания клавиатуры
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


