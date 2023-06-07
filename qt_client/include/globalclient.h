#ifndef GLOBALCLIENT_H
#define GLOBALCLIENT_H

#include "client.h"

class GlobalClient
{
public:
//    static std::shared_ptr<Client> client;
    static Client* client;
//    static Client client;
};

#endif // GLOBALCLIENT_H
