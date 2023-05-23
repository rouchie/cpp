#ifndef COMMAND_H
#define COMMAND_H

#include "bigdog.h"

// 命令模式

// 四个组成部分
// Command
// ConcreteCommand
// Receiver
// Invoker

class Command {
public:
    virtual void execute() = 0;
};

class TV {
public:
    void open() {
        SPDLOG_DEBUG("open tv");
    }

    void close() {
        SPDLOG_DEBUG("close tv");
    }

    void change() {
        SPDLOG_DEBUG("change chn");
    }
};

class OpenCommand : public Command {
    TV tv;
public:
    virtual void execute() override {
        tv.open();
    }
};

class CloseCommand : public Command {
    TV tv;
public:
    virtual void execute() override {
        tv.close();
    }
};

class ChangeCommand : public Command {
    TV tv;
public:
    virtual void execute() override {
        tv.change();
    }
};

class Invoker {
public:
    void runCommand(Command * cmd) {
        cmd->execute();
    }
};

#define PTR_VALUE(TYPE, NAME) std::shared_ptr<TYPE> NAME(new TYPE)
#define PTR(TYPE) std::shared_ptr<TYPE>(new TYPE)

void test_command()
{
    PTR_VALUE(Invoker, inv);

    inv->runCommand(PTR(OpenCommand).get());
    inv->runCommand(PTR(ChangeCommand).get());
    inv->runCommand(PTR(CloseCommand).get());
}

#endif // COMMAND_H
