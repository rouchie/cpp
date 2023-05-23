#ifndef FACTORY_H
#define FACTORY_H

#include "bigdog.h"

// 工厂模式的用处：
//    1. 当你需要改变类名字的时候，如果用了工厂模式则很简单，不需要在整个项目中查找修改
//    2. 经典用法日志记录器：记录可能记录到本地硬盘、系统事件、远程服务器等，用户可以选择记录日志到什么地方
//
// 优点：
//    1、一个调用者想创建一个对象，只要知道其名称就可以了。
//    2、扩展性高，如果想增加一个产品，只要扩展一个工厂类就可以。
//    3、屏蔽产品的具体实现，调用者只关心产品的接口。
//
// 缺点：每次增加一个产品时，都需要增加一个具体类和对象实现工厂，使得系统中类的个数成倍增加，
//      在一定程度上增加了系统的复杂度，同时也增加了系统具体类的依赖。这并不是什么好事。

class Log {
public:
    Log() {}
    virtual ~Log() {}
    virtual void some() = 0;
};

class TerminalLog : public Log {
public:
    TerminalLog() {}
    virtual void some() override {
        SPDLOG_DEBUG("TerminalLog some");
    }
};

class FileLog : public Log {
public:
    FileLog() {}
    virtual void some() override {
        SPDLOG_DEBUG("FileLog some");
    }
};

class NetworkLog : public Log {
public:
    NetworkLog() {}
    virtual void some() override {
        SPDLOG_DEBUG("NetworkLog some");
    }
};

// 简单工厂模式
inline Log * logFactory(int id)
{
    switch (id) {
    case 1: return new TerminalLog;
    case 2: return new FileLog;
    case 3: return new NetworkLog;
    }
    return nullptr;
}

// 工厂方法模式
class LogFactory {
public:
    virtual Log * log() = 0;
};

class TerminalLogFactory : public LogFactory {
public:
    virtual Log * log() override {
        return new TerminalLog;
    }
};

class FileLogFactory : public LogFactory {
public:
    virtual Log * log() override {
        return new FileLog;
    }
};

class NetworkLogFactory : public LogFactory {
public:
    virtual Log * log() override {
        return new NetworkLog;
    }
};

// 抽象工厂模式
class Message {
public:
    virtual ~Message() {}
    virtual void show() = 0;
};

class CharMessage : public Message {
public:
    virtual void show() override {
        SPDLOG_DEBUG("char message show");
    }
};

class HexMessage : public Message {
public:
    virtual void show() override {
        SPDLOG_DEBUG("hex message show");
    }
};

class Factory {
public:
    virtual ~Factory() {}
    virtual Log * log() = 0;
    virtual Message * message() = 0;
};

class TerminalLogWithCharMessageFactory : public Factory {
public:
    virtual Log *log() override {
        return new TerminalLog;
    }

    virtual Message * message() override {
        return new CharMessage;
    }
};

class FileLogWithHexMessageFactory : public Factory {
public:
    virtual Log *log() override {
        return new FileLog;
    }

    virtual Message * message() override {
        return new HexMessage;
    }
};

inline void test_factory()
{
    for (int i=1; i<=3; i++) {
        std::shared_ptr<Log> log(logFactory(i));
        log->some();
    }

    std::shared_ptr<Log> terminal(TerminalLogFactory().log());
    std::shared_ptr<Log> file(FileLogFactory().log());
    std::shared_ptr<Log> network(NetworkLogFactory().log());

    terminal->some();
    file->some();
    network->some();

    std::shared_ptr<Factory> f0(new TerminalLogWithCharMessageFactory);
    std::shared_ptr<Log> f0Log(f0->log());
    std::shared_ptr<Message> f0Message(f0->message());

    f0Log->some();
    f0Message->show();

    auto f1 = new FileLogWithHexMessageFactory;

    auto l1 = f1->log();
    l1->some();
    delete l1;

    auto m1 = f1->message();
    m1->show();
    delete m1;

    delete f1;
}

#endif // FACTORY_H
