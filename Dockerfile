FROM gcc:14 AS builder
WORKDIR /APP

COPY CMakelists.txt .
COPY main.cpp .

RUN apt-get update && apt-get install -y cmake && rm -rf /var/lib/apt/lists/*
RUN cmake -S . -B build && camke --build build

FROM debian:bookwoem-slim
WORKDIR /app

ENV APP_DB_FILE=/data/tasks.db

RUN mkdir -p /data
COPY --from=builder /app/build/devops-task-runner /app/devops-task-runner

VOLUME ["/data"]

CMD ["/app/devops-task-runner"]
