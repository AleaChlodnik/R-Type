
add_library(server_ECS Entities/entity_factory.cpp Systems/update_system.cpp Systems/shoot_system.cpp Systems/update_system.cpp)

target_link_libraries(server_ECS PRIVATE server_Entities server_systems r-type_client_interfaces)
