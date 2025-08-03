# Docker Setup Guide dla hev-socks5-server

## Szybki start

1. **Skopiuj przykład konfiguracji:**
```bash
cp env.example .env
```

2. **Edytuj konfigurację:**
```bash
nano .env
```

3. **Uruchom serwer:**
```bash
# Zatrzymaj poprzednie instancje
docker compose down

# Zbuduj image
docker compose build

# Uruchom w tle
docker compose up -d
```

## Podstawowe komendy

```bash
# Start
docker compose up -d

# Stop i usuń kontenery
docker compose down

# Rebuild image
docker compose build

# Rebuild i restart
docker compose build && docker compose up -d

# Pokaż logi
docker compose logs -f

# Status kontenerów
docker compose ps

# Wejdź do kontenera
docker compose exec hev-socks5-server sh
```

## Konfiguracja

### Podstawowa konfiguracja w .env:
```env
SOCKS5_PORT=2137
SOCKS5_AUTH=admin:strongPassword123!
LISTEN_ADDRESS=::
TIMEZONE=Europe/Warsaw
```

### Bezpieczne hasło:
```bash
# Wygeneruj bezpieczne hasło
openssl rand -base64 32

# Ustaw w .env
SOCKS5_AUTH=admin:$(openssl rand -base64 32)
```

## Monitoring

### Sprawdź status:
```bash
# Health check
docker compose exec hev-socks5-server netstat -tlnp

# Sprawdź czy port nasłuchuje
docker compose exec hev-socks5-server ss -tlnp | grep 2137
```

### Logi:
```bash
# Podążaj za logami
docker compose logs -f

# Ostatnie 100 linii
docker compose logs --tail=100

# Logi tylko z ostatniej godziny
docker compose logs --since="1h"
```

## Struktura plików

```
hev-socks5-server/
├── docker-compose.yml          # Główna konfiguracja Docker Compose
├── .env                        # Twoja konfiguracja (skopiowana z env.example)
├── env.example                 # Przykład konfiguracji
├── docker/
│   ├── Dockerfile              # Zoptymalizowany Dockerfile
│   └── entrypoint.sh           # Ulepsowany entrypoint z walidacją
├── conf/
│   └── main.yml                # Zoptymalizowana konfiguracja serwera
└── logs/                       # Logi (tworzone automatycznie)
    └── socks5.log
```

## Testowanie

### Test połączenia SOCKS5:
```bash
# Używając curl (jeśli masz auth)
curl --socks5 admin:password@localhost:2137 http://httpbin.org/ip

# Bez autoryzacji
curl --socks5 localhost:2137 http://httpbin.org/ip

# Test UDP (jeśli dostępne)
dig @8.8.8.8 google.com +tcp +proxy=socks5://localhost:2137
```

## Troubleshooting

### Problemy z portami:
```bash
# Sprawdź czy port jest zajęty
sudo netstat -tlnp | grep 2137

# Zmień port w .env i restart
docker compose down && docker compose up -d
```

### Problemy z permissions:
```bash
# Sprawdź ownership logs directory
ls -la logs/

# Popraw jeśli potrzeba
sudo chown -R 1000:1000 logs/
```

### Reset całej konfiguracji:
```bash
docker compose down -v
docker system prune -f
docker compose build --no-cache
docker compose up -d
```

## Produkcyjna konfiguracja

### Zalecenia bezpieczeństwa:
1. Zawsze używaj silnych haseł
2. Ogranicz `LISTEN_ADDRESS` do konkretnych interfejsów  
3. Użyj niestandardowych portów
4. Monitoruj logi regularnie
5. Aktualizuj regularnie

### Przykład produkcyjnej konfiguracji:
```env
SOCKS5_PORT=8080
SOCKS5_AUTH=admin:$(openssl rand -base64 32)
LISTEN_ADDRESS=127.0.0.1
TIMEZONE=Europe/Warsaw
```

## Performance tuning

Konfiguracja została zoptymalizowana w `conf/main.yml`:
- Zwiększona liczba workerów do 8
- Większe bufory UDP (1MB)
- Zoptymalizowane timeouty
- Zwiększone limity file descriptors (100k)

Jeśli potrzebujesz więcej wydajności, możesz:
1. Zwiększyć `workers` w `conf/main.yml`
2. Dostosować limity zasobów w `docker-compose.yml`
3. Użyć `--net=host` dla maksymalnej wydajności (mniej bezpieczne)