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
    j.at("name").get_to(p.name);
    j.at("age").get_to(p.age);
}

int main()
{
    spdlog_init();

    Person p {"Ned Flanders", 60};

    json j = p;

    SPDLOG_INFO("json[{}]", j.dump());

    auto p2 = j.get<Person>();

    return 0;
}