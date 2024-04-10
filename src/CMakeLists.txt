aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC) #将该目录下的所有源文件赋值给变量SRC

add_library(myrpc ${SRC}) #生成静态库

target_link_libraries(myrpc muduo_net muduo_base pthread zookeeper_mt)

