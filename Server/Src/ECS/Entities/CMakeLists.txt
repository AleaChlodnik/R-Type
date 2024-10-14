
add_library(Entities entity_factory.cpp)
target_link_libraries(Entities PRIVATE r-type_client_interfaces)
