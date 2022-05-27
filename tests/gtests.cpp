#include <iostream>
#include <sys/sysinfo.h>
#include <gtest/gtest.h>
#include <string>

#include "gmock/gmock.h"
#include "tg_bot.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;


const int id = 0;


TEST(simple_test, test_getter) 
{
    std::string test_string = "Hello";
    int test_chat_id = 1;
    Message msg(test_string, test_chat_id);
    EXPECT_EQ(msg.GetText(), test_string);
    EXPECT_EQ(msg.GetChatId(), test_chat_id);
}

// Замокаем метод SendMessage у MessageView, InlineView, VideoView
class MockMessageView : public MessageView
{
public:
    MockMessageView(std::string type, Bot *bot) : MessageView(type, bot) {}
    MOCK_METHOD1(SendMessage, void(Message &msg));

};

class MockInlineView : public InlineView
{
public:
    MockInlineView(std::string type, InlineKeyboardMarkup::Ptr inlineKb, Bot *bot) : InlineView(type, inlineKb, bot) {}
    MOCK_METHOD1(SendMessage, void(Message &msg)); 
};

class MockVideoView : public VideoView
{
public:
    MockVideoView(std::string type, Bot *bot) : VideoView(type, bot) {}
    MOCK_METHOD1(SendMessage, void(Message &msg));   
};

class MockModel : public IModel
{
public:
    MOCK_METHOD1(FindRouteModel, std::string(const Positions &pos)); 
    MOCK_METHOD1(isValid, bool(std::string point));   
};

// Тестовое окружение: создание представлений через test_data.json
class ViewsTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        TgBot::Bot bot("5181505545:AAHTLmsoVKRTby02w54aVI8Y7j-s5NuoSNk");
        std::ifstream ifs("../../tests/test_data.json");
        j = nlohmann::json::parse(ifs);
        CreateViews<MockInlineView>(vecViews, CATEG, j[CATEG], bot); 
        vecViews.push_back(new MockMessageView(TEXT, &bot));
        vecViews.push_back(new MockVideoView(VIDEO, &bot));
    }
    void TearDown() override 
    {
        for (auto &view : vecViews)
        {
            delete view;
        }
    }
    std::vector<IView *> vecViews;
    nlohmann::json j;
};

TEST_F(ViewsTest, test_create_views) 
{
    std::set<std::string> nameViews= {"category", "audit", "dining", "buffet", "toilet", "text", "video"};
    for (size_t i = 0; i < vecViews.size(); i++)
    {
        auto it = nameViews.find(vecViews[i]->GetTypeView());
        if (it != nameViews.end())
        {
            nameViews.erase(it);
        }
    }
    EXPECT_TRUE(nameViews.empty());
}

// Presenter с доступными protected методами
class PresenterNoProtected : public Presenter
{
public:
    PresenterNoProtected(vector<IView *> vecViews_, IModel *model, nlohmann::json j) : Presenter(vecViews_, model, j) {}
    IView *FindView(std::string type)
    {
        return Presenter::FindView(type);
    }
    // устанавливает начальную или конечную точку
    SET_POS SetPosition(std::string pos_id, std::string pos_view)
    {
        return Presenter::SetPosition(pos_id, pos_view);
    }

    const Positions &GetPos()
    {
        return Presenter::GetPos();
    }

    // проверка готовности построить маршрут
    bool isReady()
    {
        return Presenter::isReady();
    }
    // генерирует сообщение о текущем состоянии
    void Info(int chatId)
    {
        return Presenter::Info(chatId);
    }
    void Clear()
    {
        return Presenter::Clear();
    }
};

TEST_F(ViewsTest, test_command_start) 
{
    MockModel mockModel;
    PresenterNoProtected presenter(vecViews, &mockModel, j);
    Message msg("/start", id);
    EXPECT_CALL(*dynamic_cast<MockInlineView*>(presenter.FindView(CATEG)), SendMessage(::testing::_)).Times(1);
    presenter.Check(msg);
}

TEST_F(ViewsTest, test_choose_dining_dinig2) 
{
    MockModel mockModel;
    PresenterNoProtected presenter(vecViews, &mockModel, j);
    // Сообщение : "Выберите: Актовый зал"
    EXPECT_CALL(*dynamic_cast<MockInlineView*>(presenter.FindView("dining")), SendMessage(::testing::_)).Times(1);
    // Сообщение : "Текущее состояние. Начальная..."
    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView("text")), SendMessage(::testing::_)).Times(1);

    EXPECT_CALL(mockModel, isValid("dining2"))
      .WillOnce(::testing::DoAll(::testing::Return(true)));

    Message msg1("dining", id);
    presenter.Check(msg1);
    Message msg2("dining2", id);
    presenter.Check(msg2);
}

TEST_F(ViewsTest, test_input_no_valid) 
{
    MockModel mockModel;
    PresenterNoProtected presenter(vecViews, &mockModel, j);

    // Сообщение 1 : "Позиция не найдена"
    // Сообщение 2 : "Текущее состояние. Начальная позиция:"
    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView(TEXT)), SendMessage(::testing::_)).Times(2);

    EXPECT_CALL(mockModel, isValid("qwerty"))
      .WillOnce(::testing::DoAll(::testing::Return(false)));

    Message msg("qwerty", id);
    presenter.Check(msg);
}

TEST_F(ViewsTest, test_input_valid) 
{
    MockModel mockModel;
    PresenterNoProtected presenter(vecViews, &mockModel, j);

    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView(TEXT)), SendMessage(::testing::_)).Times(2);
    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView(CATEG)), SendMessage(::testing::_)).Times(1);
    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView("dining")), SendMessage(::testing::_)).Times(1);
    EXPECT_CALL(*dynamic_cast<MockMessageView*>(presenter.FindView("buffet")), SendMessage(::testing::_)).Times(1);

    EXPECT_CALL(mockModel, isValid("techopark"))
      .WillOnce(::testing::DoAll(::testing::Return(true)));
    EXPECT_CALL(mockModel, isValid("buffet2"))
      .WillOnce(::testing::DoAll(::testing::Return(true)));
    {
        Message msg("/start", id); presenter.Check(msg);
    }
    {
        Message msg("techopark", id); presenter.Check(msg);
    }
    {
        Message msg("dining", id); presenter.Check(msg);
    }
    {
        Message msg("buffet", id); presenter.Check(msg);
    }
    {
        Message msg("buffet2", id); presenter.Check(msg);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}