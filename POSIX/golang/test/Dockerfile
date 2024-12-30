FROM gcc:11.5.0 AS builder
WORKDIR /app
COPY . .
RUN go mod tidy
RUN go build -o mmkv-test .

FROM debian:bullseye-slim
WORKDIR /app
COPY --from-builder mmkv-test /app/mmkv-test
CMD ["./mmkv-test"]
