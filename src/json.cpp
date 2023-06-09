#include "3rdparty.h"

// nlohmann json 结构体转json需要定义 to_json函数

struct Person {
    std::string name;
    int age;
    int *p;
};

struct A : public Person {
};

struct address {
    address() { housenumber = 10; }

  private:
    std::string street;
    int housenumber;
    int postcode;

  public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(address, street, housenumber, postcode)
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

// NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT 和 NLOHMANN_DEFINE_TYPE_INTRUSIVE 的区别是从json转struct时，json没有需要的配置项，一个是赋予默认值，一个是throw一个异常

struct S0 {
    int a;
    int b;
    int c;
    std::vector<int> d; // 数组也能递归进去，挺牛皮的

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(S0, a, b, c, d)
};

struct S1 {
    int a;
    int b;
    int c;
    S0  s;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(S1, a, b, c, s)
};

int main()
{
    spdlog_init();

    {
        S1 s1;
        s1.a = 10;
        s1.b = 20;
        s1.c = 30;
        s1.s.a = 1;
        s1.s.b = 2;
        s1.s.c = 3;
        s1.s.d.emplace_back(100);
        s1.s.d.emplace_back(200);
        s1.s.d.emplace_back(300);

        json j = s1;

        SPDLOG_INFO("{}", j.dump());

        S1 s = j.get<S1>();

        SPDLOG_INFO("{} {} {} {} {} {}", s.a, s.b, s.c, s.s.a, s.s.b, s.s.c);
    }

    {
        json a = R"({"housenumber":21,"postcode":10,"street":""})"_json;

        address addr = a.get<address>();
        SPDLOG_INFO("json [{}]", a.dump());

        json b = addr;
        SPDLOG_INFO("json [{}]", b.dump());

        address a0 = b.get<address>();
        json c = a0;
        SPDLOG_INFO("c json[{}]", c.dump());
    }

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