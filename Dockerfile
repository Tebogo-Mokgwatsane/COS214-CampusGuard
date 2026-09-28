# ============================================================
# CampusGuard — Dockerfile
# COS214 Practical 5
# ============================================================

FROM gcc:13

RUN apt-get update && \
    apt-get install -y --no-install-recommends make valgrind && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make clean && make

CMD ["./campusguard"]
