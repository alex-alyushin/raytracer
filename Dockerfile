FROM --platform=linux/arm64 ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    valgrind \
    linux-tools-common \
    linux-tools-generic \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src

CMD ["bash"]
