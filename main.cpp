#include <iostream>
#include <vector>
#include <exception>
#include <cassert>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>
#include <string_view>
#include <iostream>
#include <string>
#include <fstream>

#include "tg_bot.h"
// #include "DataBaseDAO.h"
#include "GraphFacade.h"

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

int main(int argc, char *argv[])
{
    DataBase *db = new GraphFacade;

    std::string code;
    std::ifstream myfile("../bot_code.txt");
    if (!myfile.is_open() || !getline(myfile,code))
    {
        return -1;
    } 
    myfile.close();
    Bot bot(code);

    std::ifstream ifs("../data.json");
    nlohmann::json j = nlohmann::json::parse(ifs);

    std::vector<IView *> vecViews;
    CreateViews(vecViews, CATEG, j[CATEG], bot);

    vecViews.push_back(new MessageView(TEXT, &bot));
    vecViews.push_back(new VideoView(VIDEO, &bot));

    IModel *model = new Model(db);

    Presenter presenter(vecViews, model, j);

    bool ready = false;


    bot.getEvents().onCommand("start", [&presenter, &ready](TgBot::Message::Ptr message) {
        Message inputMsg(message->text, message->chat->id);
        presenter.Check(inputMsg);
        ready = true;
    });

    bot.getEvents().onCallbackQuery([&presenter, &ready] (TgBot::CallbackQuery::Ptr query) 
    {
        if (!ready)
        {
            return;
        }
        Message inputMsg(query->data, query->message->chat->id);
        presenter.Check(inputMsg);
    });
    
    bot.getEvents().onAnyMessage([&presenter, &ready](TgBot::Message::Ptr message) 
    {
        if (!ready || StringTools::startsWith(message->text, "/start"))
        {
            return;
        }
        Message inputMsg(message->text, message->chat->id);
        presenter.Check(inputMsg);
    });

    signal(SIGINT, [](int s) {
        printf("SIGINT got\n");
        exit(0);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        bot.getApi().deleteWebhook();

        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (std::exception& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}