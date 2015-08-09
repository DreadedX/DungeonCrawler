#ifndef COMMAND_H
#define COMMAND_H

namespace Command {

    const std::string commandList[] = {"test", "give", "remove", "list", "sell", "buy"};
    const int count = sizeof(commandList)/sizeof(std::string);

    bool run(std::string command);
};

#endif

