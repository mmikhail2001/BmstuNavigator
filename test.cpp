// #include <iostream>
// #include <vector>
// #include <exception>
// #include <cassert>
// #include <tgbot/tgbot.h>
// #include <nlohmann/json.hpp>
// #include <string_view>
// #include <iostream>
// #include <string>

// using TgBot::Bot;
// using TgBot::ReplyKeyboardMarkup;
// using TgBot::InlineKeyboardMarkup;
// using TgBot::KeyboardButton;
// using TgBot::InlineKeyboardButton;
// using TgBot::ReplyKeyboardRemove;
// using TgBot::InputFile;
// using TgBot::InputMediaPhoto;
// using TgBot::InputMedia;
// using std::vector;
// using std::string;

// static const std::string CATEG = "category";
// static const std::string VIDEO = "video";
// static const std::string TEXT = "text";
// static const std::string CALLBACK = "callback";
// static const std::string SELECT = "select";
// static const std::string SYS= "commands";

// enum STATE_MESSAGE {DONE, NOT_FOUND, POS_FILLED};

// inline constexpr auto hash_djb2a(const std::string_view sv) {
//     unsigned long hash{ 5381 };
//     for (unsigned char c : sv) {
//         hash = ((hash << 5) + hash) ^ c;
//     }
//     return hash;
// }
 
// inline constexpr auto operator"" _sh(const char *str, size_t len) {
//     return hash_djb2a(std::string_view{ str, len });
// }
// struct Route
// {
//     std::vector<std::string> images;
// };

// struct Positions
// {
//     Positions() : currentPointer(0) {}
//     std::string start = std::string();
//     std::string end = std::string();
//     int currentPointer; 
// };

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

// class IModel
// {
// public:
//     IModel(DataBase *db) : search(db) {};
//     virtual Route *FindRouteModel(const Positions &pos) = 0;
//     virtual bool isValid(std::string point) = 0;
// protected:
//     Search search;
// };

// class Model : public IModel
// {
// public:
//     Model(DataBase *db) : IModel(db) {}
//     Route *FindRouteModel(const Positions &pos) 
//     {
//         Route *route = search.FindRoute(pos);
//         return route;
//     }
//     bool isValid(std::string point)
//     {
//         return search.HavePoint(point);
//     }
// };


// class Message
// {
// public:
//     Message(std::vector<std::string> vecImages, int chatId) : vecImages(vecImages), chatId(chatId) {}
//     Message(std::string text, int chatId) : text(text), chatId(chatId) {}
//     Message(const Message &other) = delete;
//     std::string GetText()
//     {
//         return text;
//     }
//     int GetChatId()
//     {
//         return chatId;
//     }
//     std::vector<std::string> vecImages;
// private:
//     std::string text = std::string();
//     int chatId = int();
// };

// class IView
// {
// public:
//     IView(std::string type) : type(type) {}
//     virtual void SendMessage(Message &msg) = 0;
//     std::string GetTypeView()
//     {
//         return type;
//     }
// protected:
//     std::string type;
// };


// class InlineView : public IView
// {
// public:
//     InlineView(std::string type, InlineKeyboardMarkup::Ptr inlineKb, Bot *bot) : IView(type), bot(bot), inlineKb(inlineKb) {};
//     void SendMessage(Message &msg)
//     {
//         bot->getApi().sendMessage(msg.GetChatId(), msg.GetText(), false, 0, inlineKb);
//     }
//     // void SendRoute(Images &images)
//     // {
//     //     // std::vector<InputMedia::Ptr> vec;
//     //     // for (auto &image : images.GetImages())
//     //     // {
//     //     //     InputMediaPhoto::Ptr photo(new InputMediaPhoto);
//     //     //     photo->media = image;
//     //     //     photo->media = InputFile::fromFile(image, "image/jpeg")
//     //     //     vec.push_back(photo);
//     //     // }
//     //     // bot->getApi().sendMediaGroup(images.GetChatId(), vec);
        
//     //     bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
//     // }
// private:
//     InlineKeyboardMarkup::Ptr inlineKb;
//     Bot *bot;
// };


// class MessageView : public IView
// {
// public:
//     MessageView(std::string type, Bot *bot) : IView(type), bot(bot) {};
//     void SendMessage(Message &msg)
//     {
//         bot->getApi().sendMessage(msg.GetChatId(), msg.GetText());
//     }
//     // void SendRoute(Images &images)
//     // {
//         // bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
//     // }
// private:
//     Bot *bot;
// };

// class VideoView : public IView
// {
// public:
//     VideoView(std::string type, Bot *bot) : IView(type), bot(bot) {};
//     // void SendMessage(Message &msg)
//     // {
//     //     // bot->getApi().sendPhoto(msg.GetChatId(), InputFile::fromFile(msg.GetText(), "image/jpeg"));
//     //     // bot->getApi().sendMessage(msg.GetChatId(), msg.GetText());
//     //     bot->getApi().sendVideo(msg.GetChatId(), InputFile::fromFile(msg.GetText(), "video/mp4"));
        
//     // }
//     void SendMessage(Message &msg)
//     {
//         std::vector<InputMedia::Ptr> vec;
//         for (auto &image : msg.vecImages)
//         {
//             InputMediaPhoto::Ptr photo(new InputMediaPhoto);
//             // photo->media = "attach://" + image;
//             photo->media = "https://img.mvideo.ru/Big/small_pic/480/30063081bb.jpg";
//             // photo->media = InputFile::fromFile(image, "image/jpeg");
//             vec.push_back(photo);
//         }
//         // std::string js = "{\"type\": \"photo\", \"media\": \"mem.jpg\"}";
//         bot->getApi().sendMediaGroup(msg.GetChatId(), vec);
        
//         // bot->getApi().sendPhoto(images.GetChatId(), InputFile::fromFile(images.GetImages()[0], "image/jpeg"));
//     }
// private:
//     Bot *bot;
// };


// class IPresenter
// {
// public:
//     IPresenter(vector<IView *> vecViews_, IModel *model) :  model(model), vecViews(vecViews_) {}
//     virtual void Check(Message &msg) = 0;
//     IView *FindView(std::string type)
//     {
//         auto view = std::find_if(vecViews.begin(), vecViews.end(), [&type](IView *view){
//             return type == view->GetTypeView();
//         });
//         if (view != vecViews.end())
//         {
//             return *view;
//         }
//         return nullptr;
//     }
// protected:
//     IModel *model;
//     STATE_MESSAGE SetPosition(std::string str_point)
//     {
//         if (model->isValid(str_point))
//         {
//             if (pos.start.empty())
//             {
//                 pos.start = str_point;
//                 return DONE;
//             }
//             else if (pos.end.empty()) 
//             {   
//                 pos.end = str_point;
//                 return DONE;
//             }
//         }
//         else 
//         {
//             return NOT_FOUND;
//         }
//         return POS_FILLED;
//     }
//     const Positions &GetPos()
//     {
//         return pos;
//     }
//     bool isReady()
//     {
//         return !pos.start.empty() && !pos.end.empty();
//     }
//     void Info(int chatId)
//     {
//         std::string currentState = "Текущее состояние.\nНачальная позиция: " + (pos.start.empty() ? "-" : pos.start) + "\nКонечная позиция: " + (pos.end.empty() ? "-" : pos.end);
//         Message outputMsg(currentState, chatId);
//         if (IView *view = FindView(TEXT))
//         {
//             view->SendMessage(outputMsg);
//         }
//     }
//     void Clear()
//     {
//         pos.start.clear();
//         pos.end.clear();
//     }
// private:
//     Positions pos;
//     std::vector<IView *> vecViews;
// };

// class Presenter : public IPresenter
// {
// public:
//     Presenter(vector<IView *> vecViews_, IModel *model, nlohmann::json j) : IPresenter(vecViews_, model), j(j) {}
//     void Check(Message &msg) 
//     {
//         if (StringTools::startsWith(msg.GetText(), "/"))
//         {
//             CheckCommand(msg);
//         }
//         else 
//         {
//             CheckCallback(msg);
//         }
//     }
// private:
//     nlohmann::json j;
//     void CheckCallback(Message &msg) 
//     {
//         // std::cout << TypeInput(j.at(CATEG), msg.GetText()) << std::endl;
//         switch(hash_djb2a(msg.GetText()))
//         {
//             case "dining"_sh:
//             case "audit"_sh:
//             case "dining2"_sh:
//             case "toilet"_sh:
//             {
//                 Message outputMsg("Выберите: " + std::string(j.at(CATEG).at(msg.GetText()).at(TEXT)), msg.GetChatId());
//                 if (IView *view = FindView(msg.GetText()))
//                 {
//                     view->SendMessage(outputMsg);
//                 }
//                 break;
//             }
//             default:
//             {
//                 std::string message = msg.GetText();
//                 for (auto &elem : j.at(CATEG))
//                 {
//                     if (elem.at(CALLBACK) == msg.GetText())
//                     {
//                         message = elem.at(TEXT);
//                         break;
//                     }
//                     if (elem.contains(SELECT) && elem.at(SELECT).contains(msg.GetText()))
//                     {
//                         message = elem.at(SELECT).at(msg.GetText()).at(TEXT);
//                         break;
//                     }
//                 }
//                 STATE_MESSAGE code = SetPosition(message);
//                 for (auto &elem : j.at("messages"))
//                 {
//                     if (elem.at("id") == code)
//                     {
//                         Message outputMsg(std::string(elem.at("text")), msg.GetChatId()); 
//                         if (IView *view = FindView(TEXT))
//                         {
//                             view->SendMessage(outputMsg);
//                         }
//                         break;
//                     }
//                 }
//                 Info(msg.GetChatId());
//             }
//         }
//     }

//     // int TypeInput(nlohmann::json j, const std::string &input)
//     // {
//     //     for (auto &object : j)
//     //     {   
//     //         if (object.contains(SELECT))
//     //         {
//     //             std::cout << "S " << std::string(object.at(CALLBACK)) << " " << input << std::endl;
//     //             if (std::string(object.at(CALLBACK)) == input)
//     //             {
//     //                 return 2;
//     //             }
//     //             return TypeInput(object.at(SELECT), input);
//     //         }
//     //         else
//     //         {
//     //             std::cout << "NS " << object.at(CALLBACK) << std::endl;
//     //             if (std::string(object.at(CALLBACK)) == input)
//     //             {
//     //                 return 1;
//     //             }
//     //         }
//     //     }
//     //     return 0;
//     // }

//     void CheckCommand(Message &msg) 
//     {
//         switch(hash_djb2a(msg.GetText()))
//         {
//             case "/start"_sh:
//             case "/reset"_sh:
//             {
//                 Clear();
//             }
//             case "/categ"_sh:
//             {
//                 Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
//                 if (IView *view = FindView(CATEG))
//                 {
//                     view->SendMessage(outputMsg);
//                 }
//                 break;
//             }
//             case "/go"_sh:
//             {
//                 if (isReady())
//                 {
//                     Route *route = model->FindRouteModel(GetPos());
//                     Message videoMsg(route->images, msg.GetChatId());
//                     if (IView *view = FindView(VIDEO))
//                     {
//                         view->SendMessage(videoMsg);
//                     }
//                 }
//                 else 
//                 {
//                     Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
//                     if (IView *view = FindView(TEXT))
//                     {
//                         view->SendMessage(outputMsg);
//                     }
//                     Info(msg.GetChatId());
//                 }
//                 break;
//             }
//             default:
//             {
//                 Message outputMsg(std::string(j.at(SYS).at(msg.GetText()).at(TEXT)), msg.GetChatId());
//             }
//         }
//     }
// };

// void createInlineKeyboard(const std::vector<std::string>& buttonStrings, const std::vector<std::string>& callbacks, InlineKeyboardMarkup::Ptr& kb)
// {
//     assert(buttonStrings.size() == callbacks.size() && "wrong size button and callbacks");
//     for (size_t i = 0; i < buttonStrings.size(); ++i) {
//         std::vector<InlineKeyboardButton::Ptr> row;
//         InlineKeyboardButton::Ptr button(new InlineKeyboardButton);
//         button->text = buttonStrings[i];
//         button->callbackData = callbacks[i];
//         row.push_back(button);
//         kb->inlineKeyboard.push_back(row);
//     }
// }

// InlineKeyboardMarkup::Ptr CreateKeyboard(const nlohmann::json &j)
// {
//     std::vector<std::string> vecButtons;
//     std::vector<std::string> vecCallback;
//     for (auto elem : j)
//     {
//         vecButtons.push_back(elem.at(TEXT));
//         vecCallback.push_back(elem.at(CALLBACK));
//     }
//     InlineKeyboardMarkup::Ptr inlineKb(new InlineKeyboardMarkup);
//     createInlineKeyboard(vecButtons, vecCallback, inlineKb);
//     return inlineKb;
// }

// void CreateViews(std::vector<IView *> &vecViews, const std::string &parent_name, const nlohmann::json &j, Bot &bot)
// {
//     {
//         auto inlineKb = CreateKeyboard(j);
//         vecViews.push_back(new InlineView(parent_name, inlineKb, &bot)); 
//     }
//     for (auto &object : j.items())
//     {
//         if (object.value().contains(SELECT))
//         {
//             // std::cout << object.key() << std::endl;
//             CreateViews(vecViews, std::string(object.key()), object.value().at(SELECT), bot);
//         }
//     }
// }

// int main()
// {
//     Bot bot("5181505545:AAHTLmsoVKRTby02w54aVI8Y7j-s5NuoSNk");

//     std::ifstream ifs("data.json");
//     nlohmann::json j = nlohmann::json::parse(ifs);

//     std::vector<IView *> vecViews;
//     CreateViews(vecViews, CATEG, j[CATEG], bot);
//     vecViews.push_back(new MessageView(TEXT, &bot));
//     vecViews.push_back(new VideoView(VIDEO, &bot));

//     DataBase *db = new DataBaseBMSTU;
//     IModel *model = new Model(db);

//     Presenter presenter(vecViews, model, j);

//     bool ready = false;


//     bot.getEvents().onCommand("start", [&presenter, &ready](TgBot::Message::Ptr message) {
//         Message inputMsg(message->text, message->chat->id);
//         presenter.Check(inputMsg);
//         ready = true;
//     });

//     bot.getEvents().onCallbackQuery([&presenter, &ready] (TgBot::CallbackQuery::Ptr query) 
//     {
//         if (!ready)
//         {
//             return;
//         }
//         Message inputMsg(query->data, query->message->chat->id);
//         presenter.Check(inputMsg);
//     });
    
//     bot.getEvents().onAnyMessage([&presenter, &ready](TgBot::Message::Ptr message) 
//     {
//         if (!ready || StringTools::startsWith(message->text, "/start"))
//         {
//             return;
//         }
//         Message inputMsg(message->text, message->chat->id);
//         presenter.Check(inputMsg);
//     });

//     signal(SIGINT, [](int s) {
//         printf("SIGINT got\n");
//         exit(0);
//     });

//     try {
//         printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
//         bot.getApi().deleteWebhook();

//         TgBot::TgLongPoll longPoll(bot);
//         while (true) {
//             printf("Long poll started\n");
//             longPoll.start();
//         }
//     } catch (std::exception& e) {
//         printf("error: %s\n", e.what());
//     }

//     return 0;
// }