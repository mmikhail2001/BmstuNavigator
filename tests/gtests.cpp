#include <iostream>
#include <sys/sysinfo.h>
#include <gtest/gtest.h>
#include "gmock/gmock.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

#include "tg_bot.h"

class MockMessenger : public Messenger 
{
public:
    void SendMessage(string message) override
    {
        DoSend();
    }
    MOCK_METHOD0(DoSend, void());
};


TEST(test_user_actions, test_number_Send_calls) {
    MockMessenger messenger;
    EXPECT_CALL(messenger, DoSend()).Times(5);

    messenger.MessageProcessing(1);
    messenger.MessageProcessing(427);
    messenger.MessageProcessing(2);
    messenger.MessageProcessing(512);
    messenger.MessageProcessing(3);
}

class ChildCategKb : public CategoricalKeyboard 
{
public:
    ChildCategKb(const vector<string>& buttonStrings, const vector<vector<string>>& inlineKeyboards) : CategoricalKeyboard(buttonStrings, inlineKeyboards) {}

    unordered_map<string, vector<string>> Get_InlineKeyboards()
    {
        return map_inline_kbs;
    }
    bool Get_CategoricalKeyboards()
    {
        return !!kb;
    }
};

class ChildStartKb : public StartKeyboard 
{
public:
    ChildStartKb(const vector<string>& buttonStrings)
    : StartKeyboard(buttonStrings) {};

    bool Get_StartKeyboards()
    {
        return !!kb;
    }
};

TEST(test_tools, test_create_keyboards) {

    vector<string> vecStartButtons = {"Пунк отправления", "Пункт назначения", "Найти маршрут"};
    vector<string> vecCategoryButtons = {"Столовая", "Актовый зал"};
    vector<string> vecInButtons1 = {"Столовая 1", "Столовая 2", "Столовая 3"};
    vector<string> vecInButtons2 = {"Актовый зал 1", "Актовый зал 2"};
    vector<vector<string>> vecInKeyboards;
    vecInKeyboards.push_back(vecInButtons1);
    vecInKeyboards.push_back(vecInButtons2);

    ChildStartKb startKb(vecStartButtons);
    ChildCategKb categKb(vecCategoryButtons, vecInKeyboards);

    EXPECT_TRUE(categKb.Get_CategoricalKeyboards());

    EXPECT_EQ(categKb.Get_InlineKeyboards().size(), vecCategoryButtons.size());
    EXPECT_EQ(categKb.Get_InlineKeyboards()["Актовый зал"], vecInButtons2);
    
    EXPECT_EQ(categKb.Get_InlineKeyboards().size(), vecCategoryButtons.size());
    EXPECT_TRUE(startKb.Get_StartKeyboards());
}

class ChildMessenger : public Messenger
{
public:
    vector<string> GetImages()
    {
        return images;
    }

    string *GetStartPoint()
    {
        return start_point;
    }

    string *GetEndPoint()
    {
        return end_point;
    }
};


TEST(test_user_actions, test_find_route) {
    ChildMessenger messenger;

    messenger.MessageProcessing(1);
    EXPECT_FALSE(messenger.Find());

    EXPECT_EQ(messenger.GetStartPoint(), nullptr);
    EXPECT_EQ(messenger.GetEndPoint(), nullptr);

    EXPECT_NO_THROW(messenger.MessageProcessing(427));

    EXPECT_EQ(messenger.GetStartPoint()[0], "427");
    EXPECT_EQ(messenger.GetEndPoint(), nullptr);
    EXPECT_FALSE(messenger.Find());

    messenger.MessageProcessing(2);

    EXPECT_EQ(messenger.GetEndPoint(), nullptr);

    EXPECT_NO_THROW(messenger.MessageProcessing(527));
    EXPECT_EQ(messenger.GetEndPoint()[0], "527");

    messenger.MessageProcessing(3);

    EXPECT_TRUE(messenger.Find());
    EXPECT_GT(messenger.GetImages().size(), 1);

}

TEST(test_inneer, test_set_position) {
    ChildMessenger messenger;
    int code;
    code = messenger.SetStartEnd("sdkgnsfg");
    EXPECT_EQ(code, 0);

    messenger.GetStartPoint()[0] = "414";
    code = messenger.SetStartEnd("435");
    EXPECT_EQ(code, 2);

    code = messenger.SetStartEnd("467");
    EXPECT_EQ(code, 0);

}

TEST(test_tools, test_convert_video) {

    VideoRoute video;
    EXPECT_ANY_THROW(video.ConvertVideo({"adfdf", "dfdf"}));
    EXPECT_NO_THROW(video.ConvertVideo({"125->127.jpeg", "127->131.jpeg"}));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}