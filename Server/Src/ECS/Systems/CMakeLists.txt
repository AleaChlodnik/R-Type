
add_library(server_Systems update_system.cpp
                    shoot_system.cpp
            )
target_link_libraries(server_Systems PRIVATE r-type_client_interfaces)
