FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    cmake \
    libsfml-dev \
    xorg \
    x11-apps \
    g++ \
    && rm -rf /var/lib/apt/lists/*

ENV DISPLAY=:0
COPY . /app
RUN mkdir -p /app/build && \
    cd /app/build && \
    cmake .. && \
    make


CMD ["/app/build/BankSystem"]

