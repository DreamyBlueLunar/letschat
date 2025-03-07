aux_source_directory(. SRC_LIST)
aux_source_directory(./db SRC_LIST)

add_executable(chatserver ${SRC_LIST})
target_link_libraries(chatserver muduo_net muduo_base mysqlclient pthread)