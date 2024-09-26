
add_library(Systems temp.cpp)

target_include_directories(Systems PRIVATE
    "../../Include"
    "../../Include/Components"
    "../../Include/Entities"
    "../../Include/Systems"
)
