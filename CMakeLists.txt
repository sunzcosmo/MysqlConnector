cmake_minimum_required(VERSION 2.6)
PROJECT(sun_mysql_connector)

AUX_SOURCE_DIRECTORY(./src SRC_LIST)

SET(EXECUTABLE_OUTPUT_PATH ./bin)
SET(LIBRARY_OUTPUT_PATH ./lib)

ADD_LIBRARY(sun_mysql_connector SHARED ${SRC_LIST})

SET(MYSQL_INCLUDE_DIR /usr/include/mysql)
SET(MYSQL_LIB /usr/lib64/mysql)
ADD_DEFINITIONS( -g -std=c++11)


INCLUDE_DIRECTORIES(./ ./include ${MYSQL_INCLUDE_DIR})
LINK_DIRECTORIES(./ ./src ${MYSQL_LIB})

TARGET_LINK_LIBRARIES(sun_mysql_connector mysqlclient_r)
