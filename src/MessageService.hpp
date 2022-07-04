//
// Created by hubert25632 on 04.07.22.
//

#ifndef BATTLESHIPS_MESSAGESERVICE_HPP
#define BATTLESHIPS_MESSAGESERVICE_HPP

#include <string>

class MessageService {
public:
    enum class MessageType {
        Error,
        Victory
    };

    virtual void showMessage(MessageType messageType, const std::string &message) = 0;
};

#endif //BATTLESHIPS_MESSAGESERVICE_HPP
