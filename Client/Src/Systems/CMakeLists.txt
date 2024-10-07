
add_library(Systems update_system.cpp
                    render_system.cpp
                    shoot_system.cpp
            )
target_link_libraries(Systems PRIVATE r-type_client_interfaces)
