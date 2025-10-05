FROM ubuntu:latest

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
            
            
            
            
            
            
