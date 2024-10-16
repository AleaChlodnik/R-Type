/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <r_type_client.hpp>

/**
 * @brief The entry point of the program.
 *
 * This function initializes the Rtype object and runs the game.
 *
 * @return 0 indicating successful program execution.
 *
 * @brief
 *
 * @return int
 */
int main()
{

    // get client info and connect to server

    Rtype rtype;
    rtype.run();

    // simpleClient();
    return 0;
}
