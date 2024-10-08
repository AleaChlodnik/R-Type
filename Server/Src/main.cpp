/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "netCommon.hpp"
#include <olcNet.hpp>

class CustomServer : public olc::net::ServerInterface<CustomMsgTypes> {
  public:
    CustomServer(uint16_t nPort)
        : olc::net::ServerInterface<CustomMsgTypes>(nPort)
    {
    }
    std::unordered_map<uint32_t, sPlayerInformation> m_mapPlayerRoster;
    std::vector<uint32_t> m_vGarbageIDs;

    int getNbrPlayer() { return m_vPlayerRoster.size(); }

    void pushPlayer(sPlayerInformation desc)
    {
        m_vPlayerRoster.push_back(desc);
    }

    std::vector<sPlayerInformation> getPlayers() { return m_vPlayerRoster; }

  protected:
    virtual bool checkPlayerPosition(sPlayerInformation desc)
    {
        std::vector<sPlayerInformation> players = getPlayers();
        for (auto &player : players) {
            if (player.nUniqueID != desc.nUniqueID) {
                if (player.vPos.x =
                        desc.vPos.x && player.vPos.y == desc.vPos.y) {
                    return false;
                }
            }
        }
        return true;
    }

    virtual void InitiatePlayers(olc::net::message<CustomMsgTypes> &msg)
    {
        sPlayerInformation desc;
        desc.nUniqueID = getNbrPlayer();
        desc.vPos = {static_cast<float>(rand() % 800),
            static_cast<float>(rand() % 600)};
        while (checkPlayerPosition(desc) == false) {
            desc.vPos = {static_cast<float>(rand() % 800),
                static_cast<float>(rand() % 600)};
        }
        msg << desc;
        std::cout << desc.nUniqueID << "or struct" << std::endl;
        std::cout << msg.body.front() << "on struct" << std::endl;
        pushPlayer(desc);
    }

    virtual void InitListEntities(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client,
        sPlayerInformation desc)
    {
        olc::net::message<CustomMsgTypes> msgAddPlayer;
        msgAddPlayer.header.id = CustomMsgTypes::Game_AddEntity;
        for (auto &player : m_vPlayerRoster) {
            if (desc.nUniqueID != player.nUniqueID) {
                msgAddPlayer << player;
                client->Send(msgAddPlayer);
            }
        }
    }

    virtual bool OnClientConnect(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerAccept;
        InitiatePlayers(msg);
        std::cout << "Client [" << client->GetID() << "] Connected\n";
        client->Send(msg);
        sPlayerInformation desc;
        msg >> desc;
        InitListEntities(client, desc);
        return true;
    }

    virtual void OnClientDisconnect(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
        if (client) {
            if (m_mapPlayerRoster.find(client->GetID()) ==
                m_mapPlayerRoster.end()) {
            } else {
                auto &pd = m_mapPlayerRoster[client->GetID()];
                std::cout << "[UNGRACEFUL REMOVAL]:" +
                        std::to_string(pd.nUniqueID) + "\n";
                m_mapPlayerRoster.erase(client->GetID());
                m_vGarbageIDs.push_back(client->GetID());
            }
        }
    }

    virtual void PlayersUpdate(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        olc::net::message<CustomMsgTypes> msg;
        for (auto &player : m_vPlayerRoster) {
            msg.header.id = CustomMsgTypes::Game_UpdateEntity;
            msg << player;
            client->Send(msg);
        }
    }

    virtual void PlayerPositionUpdate(sPlayerInformation desc)
    {
        for (auto &player : m_vPlayerRoster) {
            if (player.nUniqueID == desc.nUniqueID) {
                player.vPos = desc.vPos;
            }
        }
    }

    // Called when a message arrives
    virtual void OnMessage(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client,
        olc::net::message<CustomMsgTypes> &msg)
    {
        if (!m_vGarbageIDs.empty()) {
            for (auto pid : m_vGarbageIDs) {
                olc::net::message<CustomMsgTypes> m;
                m.header.id = CustomMsgTypes::Game_RemoveEntity;
                m << pid;
                std::cout << "Removing " << pid << "\n";
                MessageAllClients(m);
            }
            m_vGarbageIDs.clear();
        }
        switch (msg.header.id) {
        case CustomMsgTypes::ServerPing: {
            std::cout << "[" << client->GetID() << "]: Server Ping\n";

            // Simply bounce message back to client
            client->Send(msg);
        } break;

        case CustomMsgTypes::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All\n";

            // Construct a new message and send it to all clients
            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerMessage;
            msg << client->GetID();
            MessageAllClients(msg, client);

        } break;
        case CustomMsgTypes::Client_RegisterWithServer: {
            sPlayerInformation desc;
            msg >> desc;
            desc.nUniqueID = client->GetID();
            m_mapPlayerRoster.insert_or_assign(desc.nUniqueID, desc);

            olc::net::message<CustomMsgTypes> msgSendID;
            msgSendID.header.id = CustomMsgTypes::Client_AssignID;
            msgSendID << desc.nUniqueID;
            MessageClient(client, msgSendID);

            olc::net::message<CustomMsgTypes> msgAddPlayer;
            msgAddPlayer.header.id = CustomMsgTypes::Game_AddEntity;
            msgAddPlayer << desc;
            MessageAllClients(msgAddPlayer);

            for (const auto &player : m_mapPlayerRoster) {
                olc::net::message<CustomMsgTypes> msgAddOtherPlayers;
                msgAddOtherPlayers.header.id = CustomMsgTypes::Game_AddEntity;
                msgAddOtherPlayers << player.second;
                MessageClient(client, msgAddOtherPlayers);
            }

            break;
        }
        case CustomMsgTypes::Game_UpdateEntity: {
            PlayersUpdate(client);
            break;
        }
        case CustomMsgTypes::Game_UpdatePositionEntity: {
            sPlayerInformation desc;
            msg >> desc;
            PlayerPositionUpdate(desc);
            break;
        }

        case CustomMsgTypes::Client_UnregisterWithServer: {
            break;
        }
        }
    }

  private:
    int nbrPlayer = 0;
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