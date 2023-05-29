#include "3rdparty.h"

// nlohmann json 结构体转json需要定义 to_json函数

struct Person {
    std::string name;
    int age;
};

void to_json(json& j, const Person& p) {
    j = json{{"name", p.name}, {"age", p.age}};
}

void from_json(const json& j, Person& p) {
    try {
        j.at("name").get_to(p.name);
        j.at("age").get_to(p.age);
    } catch (nlohmann::json_abi_v3_11_2::detail::out_of_range e) {
        SPDLOG_INFO("exception: [{}]", e.what());
    }
}

int main()
{
    spdlog_init();

    Person p {"Ned Flanders", 60};

    json j = p;

    SPDLOG_INFO("json[{}]", j.dump());

    {
        json req = R"({"name":"rouchie", "age":30})"_json;

        auto p = req.get<Person>();

        SPDLOG_INFO("name[{}] age[{}]", p.name, p.age);
    }

    {
        // 如果json里没有结构体需要的内容则会抛出异常
        json req = R"({"name":"rouchie"})"_json;
        auto p2 = req.get<Person>();

        SPDLOG_INFO("name[{}] age[{}]", p2.name, p2.age);
    }

    return 0;
}