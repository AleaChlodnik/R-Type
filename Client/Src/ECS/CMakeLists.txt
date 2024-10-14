
add_library(client_ECS Entities/entity_factory.cpp
            Systems/render_system.cpp
            )
target_link_libraries(client_ECS PRIVATE r-type_client_interfaces)
