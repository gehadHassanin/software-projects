FROM ubuntu:latest

RUN apt-get update && sudo apt-get install -y g++ cmake make

WORKDIR /app

COPY RoboBank-Portfolio/src/*.cpp .
COPY RoboBank-Portfolio/main.cpp .
COPY RoboBank-Portfolio/tests/*.cpp .

RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make

RUN g++ ./RoboBank-Portfolio/src/*.cpp ./RoboBank-Portfolio/main.cpp -o roboBankProgram

RUN g++ -std=c++17 \
    -IRoboBank-Portfolio/inc \
    -Igoogletest/googletest/include \
    RoboBank-Portfolio/tests/*.cpp \
    RoboBank-Portfolio/src/*.cpp \
    googletest/build/lib/libgtest.a \
    googletest/build/lib/libgtest_main.a \
    -pthread -o RoboBank-Portfolio/tests/test

CMD [ "./RoboBank-Portfolio/tests/test" ]
            
            
            
            
            
            
