
add_library(server_Entities entity_factory.cpp
            )
target_link_libraries(server_Entities PRIVATE r-type_client_interfaces)
