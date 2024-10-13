/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "netCommon.hpp"
#include <cmath>
#include <olcNet.hpp>

class CustomServer : public olc::net::ServerInterface<CustomMsgTypes> {
  public:
    CustomServer(uint16_t nPort)
        : olc::net::ServerInterface<CustomMsgTypes>(nPort)
    {
    }
    std::vector<uint32_t> m_vGarbageIDs;

    int getNbrPlayer() { return m_vPlayerRoster.size(); }

    void pushPlayer(sPlayerInformation desc)
    {
        m_vPlayerRoster.insert_or_assign(desc.nUniqueID, desc);
    }

  protected:
    virtual bool checkPlayerPosition(sPlayerInformation desc)
    {

        for (const auto &other : m_vPlayerRoster) {
            if (desc.nUniqueID != other.first) {
                float dx = desc.vPos.x - other.second.vPos.x;
                float dy = desc.vPos.y - other.second.vPos.y;
                float distance = std::sqrt(dx * dx + dy * dy);
                if (distance <= (desc.fRadius)) {
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
        desc.fRadius = 10;
        desc.vPos = {static_cast<float>(rand() % 800),
            static_cast<float>(rand() % 600)};
        while (checkPlayerPosition(desc) == false) {
            desc.vPos = {static_cast<float>(rand() % 800),
                static_cast<float>(rand() % 600)};
        }
        msg << desc;
        pushPlayer(desc);
    }

    virtual void InitListEntities(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client,
        sPlayerInformation desc)
    {
        olc::net::message<CustomMsgTypes> msgAddPlayer;
        msgAddPlayer.header.id = CustomMsgTypes::Game_AddEntity;
        for (const auto &player : m_vPlayerRoster) {
            if (player.first != desc.nUniqueID) {
                msgAddPlayer << player.second;
                client->Send(msgAddPlayer);
            }
        }
    }

    virtual bool OnClientConnect(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        olc::net::message<CustomMsgTypes> msg;
        sPlayerInformation desc;
        InitiatePlayers(msg);
        std::cout << "Client [" << client->GetID() << "] Connected\n";
        client->Send(msg);
        msg.header.id = CustomMsgTypes::Game_UpdateEntity;
        MessageAllClients(msg);
        msg >> desc;
        InitListEntities(client, desc);
        return true;
    }

    virtual void OnClientDisconnect(
        std::shared_ptr<olc::net::Connection<CustomMsgTypes>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
        if (client) {
            if (m_vPlayerRoster.find(client->GetID()) ==
                m_vPlayerRoster.end()) {
            } else {
                auto &pd = m_vPlayerRoster[client->GetID()];
                m_vPlayerRoster.erase(client->GetID());
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
            msg << player.second;
            client->Send(msg);
        }
    }

    virtual void PlayerPositionUpdate(sPlayerInformation desc)
    {
        sPlayerInformation pd;
        olc::net::message<CustomMsgTypes> msg;
        m_vPlayerRoster[desc.nUniqueID].vPos = desc.vPos;
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

            client->Send(msg);
        } break;

        case CustomMsgTypes::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All\n";

            olc::net::message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerMessage;
            msg << client->GetID();
            MessageAllClients(msg, client);

        } break;
        case CustomMsgTypes::Client_RegisterWithServer: {
            sPlayerInformation desc;
            msg >> desc;
            desc.nUniqueID = client->GetID();
            m_vPlayerRoster.insert_or_assign(desc.nUniqueID, desc);

            olc::net::message<CustomMsgTypes> msgSendID;
            msgSendID.header.id = CustomMsgTypes::Client_AssignID;
            msgSendID << desc.nUniqueID;
            MessageClient(client, msgSendID);

            olc::net::message<CustomMsgTypes> msgAddPlayer;
            msgAddPlayer.header.id = CustomMsgTypes::Game_AddEntity;
            msgAddPlayer << desc;
            MessageAllClients(msgAddPlayer);

            for (const auto &player : m_vPlayerRoster) {
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
            olc::net::message<CustomMsgTypes> reponse;
            sPlayerInformation desc;
            msg >> desc;
            if (checkPlayerPosition(desc) == true) {
                PlayerPositionUpdate(desc);
                reponse.header.id = CustomMsgTypes::Game_UpdateEntity;
                reponse << desc;
                MessageAllClients(reponse);
            }
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