
add_library(Entities entity_factory.cpp)

target_include_directories(Entities PRIVATE
    "../../Include"
    "../../Include/Components"
    "../../Include/Entities"
    "../../Include/Systems"
)
