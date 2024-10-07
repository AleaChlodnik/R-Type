
add_library(MainMenu button.cpp
                    display.cpp
                    settingsMenu.cpp
            )
target_link_libraries(MainMenu PRIVATE r-type_client_interfaces)
