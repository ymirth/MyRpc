aux_source_directory(${PROJECT_SOURCE_DIR}/example/service SERVICE_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/example/client CLIENT_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/example/protos PROTO_SRC)

# 设置项目可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 服务提供者
add_executable(myrpcservice ${SERVICE_SRC} ${PROTO_SRC})
target_link_libraries(myrpcservice myrpc protobuf)

# 服务调用者
add_executable(myrpcclient ${CLIENT_SRC} ${PROTO_SRC})
target_link_libraries(myrpcclient myrpc protobuf)

