cmake_minimum_required(VERSION 3.6)
project(ex6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(SOURCE_FILES
        Block.cpp
        Block.h
        Cab.cpp
        Cab.h
        CarType.h
        Color.h
        Driver.cpp
        Driver.h
        LuxuryCab.cpp
        LuxuryCab.h
        Point.cpp
        Point.h
        StandardCab.cpp
        StandardCab.h
        Status.h
        Socket.cpp
        Socket.h
        Trip.cpp
        Trip.h
        Udp.cpp
        Udp.h
        Bfs.cpp
        Bfs.h
        GameFlow.cpp
        GameFlow.h
        Map.cpp
        Map.h
        Matrix.cpp
        Matrix.h
        Passenger.cpp
        Passenger.h
        TaxiCenter.cpp
        TaxiCenter.h
        Tcp.cpp
        Tcp.h
        Validation.cpp
        Validation.h
        ThreadPool.cpp
        ThreadPool.h
        Task.cpp
        Task.h
        )
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.57.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

add_executable(Client ${SOURCE_FILES}
        Block.cpp
        Block.h
        Cab.cpp
        Cab.h
        CarType.h
        Color.h
        Driver.cpp
        Driver.h
        LuxuryCab.cpp
        LuxuryCab.h
        Point.cpp
        Point.h
        StandardCab.cpp
        StandardCab.h
        Status.h
        Trip.cpp
        Trip.h
        Client.cpp
        Map.cpp
        Map.h
        Matrix.cpp
        Matrix.h
        Bfs.cpp
        Bfs.h
        Udp.cpp
        Udp.h
        Validation.cpp
        Validation.h
        ThreadPool.cpp
        ThreadPool.h
        Task.cpp
        Task.h)
add_executable(Server ${SOURCE_FILES}
        Server.cpp
        Block.cpp
        Block.h
        Cab.cpp
        Cab.h
        CarType.h
        Color.h
        Driver.cpp
        Driver.h
        LuxuryCab.cpp
        LuxuryCab.h
        Point.cpp
        Point.h
        StandardCab.cpp
        StandardCab.h
        Status.h
        Trip.cpp
        Trip.h
        Bfs.cpp
        Bfs.h
        GameFlow.cpp
        GameFlow.h
        Map.cpp
        Map.h
        Matrix.cpp
        Matrix.h
        Passenger.cpp
        Passenger.h
        TaxiCenter.cpp
        TaxiCenter.h
        Validation.cpp
        Validation.h
        ThreadPool.cpp
        ThreadPool.h
        Task.cpp
        Task.h
        )

add_executable(ex6 ${SOURCE_FILES})
target_link_libraries(ex6 ${Boost_LIBRARIES} -lpthread)

target_link_libraries(Client ${Boost_LIBRARIES} -lpthread)
target_link_libraries(Server ${Boost_LIBRARIES} -lpthread)


#target_link_libraries(ex6 ${Boost_LIBRARIES} -lpthread)