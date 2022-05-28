#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <string_view>
#include <regex>
#include <string>

#include "tg_bot.h"
#include <stdlib.h>

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

IModel::IModel(DataBase *db) : search(db) {};

Model::Model(DataBase *db) : IModel(db) {}

std::optional<std::string> Model::FindRouteModel(const Positions &pos) 
{
    std::vector<Point *> points = search.GetByName(pos.start_id); 
    if (points.size())
    {
        unsigned int id = points[0]->GetId();

        std::optional<Route> optRoute = search.FindRoute(id, pos.end_id);

        if (!optRoute) 
        {
            return {};
        }
        Route route = *optRoute;
        std::vector<std::string> vecPath = route.GetLinks();

        std::string resultCommand;
        for (auto &path : vecPath)
        {
            resultCommand += "../" + path + " ";
        }
        std::string readyCommand = "python3 ../make_video.py " + resultCommand + "2>error.txt";



        system(readyCommand.c_str());

        std::ifstream fin;
        fin.open("error.txt");
        char error;
        if (!(fin >> error)) 
        {
            return "../video.mp4";
        }
        return {};
    }
    return {};
}

bool Model::isValidFinishPoint(std::string point)
{
    return search.GetByName(point).size() > 0;
}

bool Model::isValidStartPoint(std::string point)
{
    return search.GetByName(point).size() == 1;
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
    bot->getApi().sendMessage(msg.GetChatId(), msg.GetText(), false, 0, 0, "Markdown");
}


VideoView::VideoView(std::string type, Bot *bot) : IView(type), bot(bot) {};
void VideoView::SendMessage(Message &msg)
{
    bot->getApi().sendVideo(msg.GetChatId(), InputFile::fromFile(msg.GetText(), "video/mp4"));  
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
    if (std::regex_match (pos_id, std::regex("\\d\\d\\dю") ))
    {
        pos_id.replace(3,4, "u");
    }

    if (pos.start_id.empty() && model->isValidStartPoint(pos_id))
    {
        pos.start_view = pos_view;
        pos.start_id = pos_id;
        return DONE;
    }
    else if (!pos.start_id.empty() && pos.end_id.empty() && model->isValidFinishPoint(pos_id)) 
    {   
        pos.end_view = pos_view;
        pos.end_id = pos_id;
        return DONE;
    }
    else if (!pos.start_id.empty() && !pos.end_id.empty())
    {
        return POS_FILLED;
    }
    return NOT_FOUND;
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
    std::string currentState = "*Текущее состояние.*\nНачальная позиция: " + (pos.start_view.empty() ? "-" : pos.start_view) + "\nКонечная позиция: " + (pos.end_view.empty() ? "-" : pos.end_view);
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
                std::optional<std::string> data = model->FindRouteModel(GetPos());
                if (data)
                {
                    std::string pathVideo = *data;
                    Message videoMsg(pathVideo, msg.GetChatId());
                    if (IView *view = FindView(VIDEO)) // VIDEO
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

// парсит json и создает все представления
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
            CreateViews(vecViews, std::string(object.key()), object.value().at(SELECT), bot);
        }
    }
}