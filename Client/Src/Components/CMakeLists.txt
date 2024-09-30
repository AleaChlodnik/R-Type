
add_library(Components temp.cpp)

target_include_directories(Components PRIVATE
    "../../Include"
    "../../Include/Components"
    "../../Include/Entities"
    "../../Include/Systems"
)
