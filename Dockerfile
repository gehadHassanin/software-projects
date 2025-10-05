
FROM ubuntu:latest AS stylecheck

RUN apt-get update && apt-get install -y python3 python3-pip \
    && pip3 install --break-system-packages cpplint

WORKDIR /app

COPY RoboBank-Portfolio/ ./RoboBank-Portfolio/

RUN cpplint RoboBank-Portfolio/src/*.cpp RoboBank-Portfolio/tests/*.cpp \
    RoboBank-Portfolio/main.cpp RoboBank-Portfolio/inc/*.h

    
FROM ubuntu:latest AS build

RUN apt-get update && apt-get install -y g++ cmake make git

WORKDIR /app

COPY RoboBank-Portfolio/src/ ./src/
COPY RoboBank-Portfolio/main.cpp .
COPY RoboBank-Portfolio/tests/ ./tests/
COPY RoboBank-Portfolio/inc ./inc/

RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make


RUN g++ src/*.cpp main.cpp -I./inc -o roboBankProgram

RUN g++ -std=c++17 \
    -I./inc \
    -Igoogletest/googletest/include \
    src/*.cpp \
    tests/*.cpp \
    googletest/build/lib/libgtest.a \
    googletest/build/lib/libgtest_main.a \
    -pthread -o tests/test

CMD [ "./tests/test" ]
            
            
            
            
            
            
