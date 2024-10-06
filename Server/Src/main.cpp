/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <olcNet.hpp>

class CustomServer : public olc::net::ServerInterface<CustomMsgTypes> {
  public:
    CustomServer(uint16_t nPort) : olc::net::ServerInterface<CustomMsgTypes>(nPort) {}

  protected:
    virtual bool OnClientConnect(std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        olc::net::Message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerAccept;
        client->Send(msg);
        return true;
    }

    // Called when a client appears to have disconnected
    virtual void OnClientDisconnect(std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }

    // Called when a message arrives
    virtual void OnMessage(std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client,
        olc::net::Message<CustomMsgTypes> &msg)
    {
        switch (msg.header.id) {
        case CustomMsgTypes::ServerPing: {
            std::cout << "[" << client->GetID() << "]: Server Ping\n";

            // Simply bounce message back to client
            client->Send(msg);
        } break;

        case CustomMsgTypes::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All\n";

            // Construct a new message and send it to all clients
            olc::net::Message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerMessage;
            msg << client->GetID();
            MessageAllClients(msg, client);

        } break;
        case CustomMsgTypes::ClientConnect: {
            std::cout << "[" << client->GetID() << "]: Client Connect\n";
        } break;
        }
    }
};

int main()
{
    CustomServer server(60000);
    server.Start();

    while (1) {
        server.Update(-1, true);
    }

    return 0;
}