#!/bin/sh
set -e

# Enhanced entrypoint with validation and better error handling
CONFIG_FILE="/app/etc/hev-socks5-server.yml"
LOG_DIR="/app/logs"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Logging functions
log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Validation functions
validate_port() {
    local port=$1
    if [ -z "$port" ]; then
        return 0  # Empty is OK, will use default
    fi
    
    if ! echo "$port" | grep -qE '^[0-9]+$'; then
        log_error "PORT must be a number"
        return 1
    fi
    
    if [ "$port" -lt 1 ] || [ "$port" -gt 65535 ]; then
        log_error "PORT must be between 1-65535"
        return 1
    fi
    
    return 0
}

validate_listen_address() {
    local addr=$1
    if [ -z "$addr" ]; then
        return 0  # Empty is OK, will use default
    fi
    
    # Basic validation for IPv4, IPv6, or :: addresses
    if echo "$addr" | grep -qE '^([0-9]{1,3}\.){3}[0-9]{1,3}$|^::$|^[0-9a-fA-F:]+$'; then
        return 0
    fi
    
    log_error "LISTEN_ADDRESS format is invalid"
    return 1
}

validate_auth() {
    local auth=$1
    if [ -z "$auth" ]; then
        return 0  # Empty is OK, no auth
    fi
    
    if ! echo "$auth" | grep -q ':'; then
        log_error "AUTH format must be 'username:password'"
        return 1
    fi
    
    local username=$(echo "$auth" | cut -d ':' -f 1)
    local password=$(echo "$auth" | cut -d ':' -f 2)
    
    if [ -z "$username" ] || [ -z "$password" ]; then
        log_error "AUTH username and password cannot be empty"
        return 1
    fi
    
    if [ ${#username} -gt 255 ] || [ ${#password} -gt 255 ]; then
        log_error "AUTH username and password must be max 255 characters"
        return 1
    fi
    
    return 0
}

# Pre-startup validation
log_info "Validating configuration..."

validate_port "$PORT" || exit 1
validate_listen_address "$LISTEN_ADDRESS" || exit 1
validate_auth "$AUTH" || exit 1

# Create logs directory if it doesn't exist
mkdir -p "$LOG_DIR"

# Ensure config file exists
if [ ! -f "$CONFIG_FILE" ]; then
    log_error "Configuration file not found: $CONFIG_FILE"
    exit 1
fi

# Create a writable copy of config file to avoid "Resource busy" errors
TEMP_CONFIG="/app/tmp/hev-socks5-server.yml"
mkdir -p "$(dirname "$TEMP_CONFIG")"
cp "$CONFIG_FILE" "$TEMP_CONFIG"

log_info "Applying configuration..."

if [ -n "$PORT" ] && [ "$PORT" != "1080" ]; then
    log_info "Setting port to: $PORT"
    sed -i "s/port: 1080/port: $PORT/" "$TEMP_CONFIG"
    # Also update UDP port
    sed -i "s/udp-port: 1080/udp-port: $PORT/" "$TEMP_CONFIG"
fi

if [ -n "$LISTEN_ADDRESS" ] && [ "$LISTEN_ADDRESS" != '::' ]; then
    log_info "Setting listen address to: $LISTEN_ADDRESS"
    # Escape special characters for sed
    escaped_addr=$(echo "$LISTEN_ADDRESS" | sed 's/[[\.*^$()+?{|]/\\&/g')
    sed -i "s/listen-address: '::'/listen-address: '$escaped_addr'/" "$TEMP_CONFIG"
fi

if [ -n "$AUTH" ]; then
    USERNAME=$(echo "$AUTH" | cut -d ':' -f 1)
    PASSWORD=$(echo "$AUTH" | cut -d ':' -f 2)
    log_info "Enabling authentication for user: $USERNAME"
    
    # Enable auth section
    sed -i "s/#auth:/auth:/" "$TEMP_CONFIG"
    sed -i "s/#  username:/  username: $USERNAME/" "$TEMP_CONFIG"
    sed -i "s/#  password:/  password: $PASSWORD/" "$TEMP_CONFIG"
else
    log_info "Running without authentication (not recommended for production)"
fi

# Use the modified temp config
CONFIG_FILE="$TEMP_CONFIG"

# Set timezone if provided
if [ -n "$TZ" ]; then
    log_info "Setting timezone to: $TZ"
    export TZ
fi

# Display startup configuration
log_info "Starting hev-socks5-server with configuration:"
log_info "  Port: ${PORT:-1080}"
log_info "  Listen Address: ${LISTEN_ADDRESS:-::}"
log_info "  Authentication: $([ -n "$AUTH" ] && echo "Enabled" || echo "Disabled")"
log_info "  Timezone: ${TZ:-system default}"
log_info "  Log Directory: $LOG_DIR"

# Final configuration check
if ! /app/bin/hev-socks5-server --help >/dev/null 2>&1; then
    log_error "hev-socks5-server binary check failed"
    exit 1
fi

log_info "Configuration validation passed, starting server..."

# Start the server
exec /app/bin/hev-socks5-server "$CONFIG_FILE"
