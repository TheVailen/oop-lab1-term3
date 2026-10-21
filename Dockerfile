FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY array_ops.h array_ops.cpp main.cpp test_variant.cpp CMakeLists.txt ./

RUN cmake -B build && cmake --build build

CMD ["./build/test_variant"]
