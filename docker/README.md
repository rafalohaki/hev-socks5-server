# hev-socks5-server for docker

## Usage

Available environment variables:
```bash
PORT
LISTEN_ADDRESS
AUTH
```

```bash
cd hev-socks5-server
docker build -t hev-socks5-server -f docker/Dockerfile .
docker run -d \
  --name hev-socks5-server \
  --restart always \
  --net host \
  -e PORT=2137 \
  -e AUTH="rafal:kozak" \
  hev-socks5-server
```

```bash
docker compose down
docker compose build
docker compose up -d

```