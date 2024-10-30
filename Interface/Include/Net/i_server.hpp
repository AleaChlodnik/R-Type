/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "common.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "thread_safe_queue.hpp"
#include <entity_struct.hpp>

namespace r_type {
namespace net {

/**
 * @brief Interface IServer pour gérer les opérations de serveur de manière générique.
 *
 * Cette interface sert de base pour les classes de serveur et fournit les méthodes
 * nécessaires à l'exécution, l'arrêt, la gestion des connexions et la mise à jour du serveur.
 *
 * @tparam T Le type de données que le serveur gère.
 */
template <typename T> class IServer {
  public:
    virtual ~IServer() = default;

    /**
     * @brief Démarre le serveur.
     *
     * @return true si le serveur démarre avec succès, false sinon.
     */
    virtual bool Start() = 0;

    /**
     * @brief Arrête le serveur.
     *
     * Cette méthode est appelée pour arrêter le serveur et libérer les ressources.
     */
    virtual void Stop() = 0;

    /**
     * @brief Envoie un message à un client spécifique.
     *
     * @param client Un pointeur partagé vers la connexion du client.
     * @param msg Le message à envoyer au client.
     */
    virtual void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg) = 0;

    /**
     * @brief Envoie un message à tous les clients connectés, en ignorant éventuellement un client
     * spécifique.
     *
     * @param msg Le message à envoyer à tous les clients.
     * @param pIgnoreClient Pointeur partagé vers un client à ignorer. Par défaut, nullptr.
     */
    virtual void MessageAllClients(
        const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr) = 0;

    /**
     * @brief Met à jour l'état du serveur, traite les messages entrants et met à jour le niveau du
     * jeu.
     *
     * Cette méthode doit traiter les messages reçus du client et maintenir à jour les entités.
     *
     * @param nMaxMessages Le nombre maximum de messages à traiter. Par défaut, tous les messages.
     * @param bWait Indicateur de temps d'attente pour les messages.
     */
    virtual void Update(size_t nMaxMessages = -1, bool bWait = false) = 0;

    /**
     * @brief Met à jour la position d'un joueur basé sur le message reçu et l'ID du client.
     *
     * Cette méthode met à jour la position d'un joueur et vérifie les collisions avec d'autres
     * entités.
     *
     * @param msg Le message contenant la nouvelle position de l'entité.
     * @param clientId L'ID du client qui envoie la mise à jour.
     */
    virtual void UpdatePlayerPosition(Message<T> &msg, uint32_t clientId) = 0;

    /**
     * @brief Attend un message d'un client de manière asynchrone.
     *
     * Cette méthode doit être implémentée pour gérer la réception asynchrone de messages
     * client par le serveur.
     */
    virtual void WaitForClientMessage() = 0;

    /**
     * @brief Retrieves the entity ID associated with a client ID.
     *
     * @param id The client ID.
     * @return uint32_t The entity ID associated with the client.
     */
    virtual uint32_t GetClientPlayerId(uint32_t id) = 0;

    /**
     * @brief Removes a player from the game based on the client ID.
     *
     * @param id The client ID of the player to be removed.
     */
    virtual void RemovePlayer(uint32_t id) = 0;

    /**
     * @brief Removes entities associated with a player.
     *
     * @param id The ID of the player whose entities are to be removed.
     */
    virtual void RemoveEntity(uint32_t id) = 0;

    /**
     * @brief Initializes a new player entity and assigns a random position.
     *
     * The function creates a new player entity, assigns it a random position, and ensures
     * that it does not overlap with any other players.
     *
     * @param clientId The client ID of the player being initialized.
     * @return EntityInformation The information of the newly created player entity.
     */
    virtual EntityInformation InitiatePlayer(int clientId) = 0;

    /**
     * @brief Formats the information of a given entity into an EntityInformation structure.
     *
     * @param entity The entity whose information is to be formatted.
     * @return EntityInformation The formatted information of the entity.
     */
    virtual EntityInformation FormatEntityInformation(uint32_t entityId) = 0;

    /**
     * @brief Initializes a missile entity associated with a player.
     *
     * @param clientId The client ID of the player firing the missile.
     * @return EntityInformation The information of the newly created missile entity.
     */
    virtual EntityInformation InitiatePlayerMissile(int clientId) = 0;

    /**
     * @brief Initializes a missile entity associated with an enemy.
     *
     * @param enemyId The ID of the enemy whose missile is to be initialized.
     * @return EntityInformation The information of the newly created enemy missile entity.
     */
    virtual EntityInformation InitiateEnemyMissile(int enemyId) = 0;

    /**
     * @brief Initializes a background entity.
     *
     * @return EntityInformation The information of the background entity.
     */
    virtual EntityInformation InitiateBackground() = 0;

    /**
     * @brief Callback function that is called when a client has been successfully validated.
     *
     * @param client A shared pointer to the validated client connection.
     */
    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) = 0;

    /**
     * @brief Retrieves the component manager associated with the server.
     *
     * This function provides access to the component manager, which is responsible for managing
     * the components associated with entities in the game. It allows for the retrieval and
     * manipulation of entity components, enabling the game logic to interact with them as needed.
     *
     * @return ComponentManager& A reference to the component manager instance.
     */
    virtual ComponentManager GetComponentManager() = 0;

    /**
     * @brief Retrieves the entity manager associated with the server.
     *
     * This function returns the entity manager responsible for creating, managing, and removing
     * entities in the game. The entity manager handles the lifecycle of entities and ensures that
     * they are correctly processed within the game's systems.
     *
     * @return EntityManager& A reference to the entity manager instance.
     */
    virtual EntityManager &GetEntityManager() = 0;

    /**
     * @brief Retrieves the entity factory associated with the server.
     *
     * This function provides access to the entity factory, which is responsible for creating
     * new entities in the game. The entity factory provides methods to instantiate various types
     * of entities, such as players, missiles, and background elements, ensuring that they are
     * correctly initialized with the necessary components.
     *
     * @return EntityFactory& A reference to the entity factory instance.
     */
    virtual EntityFactory &GetEntityFactory() = 0;

    /**
     * @brief Retrieves the current clock time of the server.
     *
     * This function returns the current time point of the server's clock, which can be used
     * for time-related calculations, such as updating game state, handling animations,
     * or scheduling events. It provides a consistent reference point for the server's operations.
     *
     * @return std::chrono::system_clock::time_point The current time point of the server's clock.
     */
    virtual std::chrono::system_clock::time_point GetClock() = 0;

    /**
     * @brief Set the Clock object
     *
     * @param newClock
     */
    virtual void SetClock(std::chrono::system_clock::time_point newClock) = 0;

  protected:
    /**
     * @brief on client connect event
     *
     * @param client
     * @return true
     * @return false
     */
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client) { return false; }

    /**
     * @brief on client disconnect event
     *
     * @param client
     */
    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client) {}

    /**
     * @brief on message event
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) {}
};

} // namespace net
} // namespace r_type
