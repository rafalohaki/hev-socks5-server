#!/bin/sh

# Set the path to the configuration file
CONFIG_FILE="/app/etc/hev-socks5-server.yml"

# Ensure the configuration directory and file exist and are writable if they are meant to be modified
# This might require adjusting Dockerfile permissions or handling file creation here if it doesn't exist
# For now, assuming /app/etc/ and the yml file are copied and chown'd correctly in Dockerfile for 'nobody' to 'sed'

if [ -n "$PORT" ] && [ "$PORT" != "1080" ]; then
  sed -i "s/port: 1080/port: $PORT/" "$CONFIG_FILE"
fi

if [ -n "$LISTEN_ADDRESS" ] && [ "$LISTEN_ADDRESS" != '::' ]; then
  # Escape special characters in LISTEN_ADDRESS if it can contain them, e.g., for sed
  # For basic IP addresses or '0.0.0.0', direct substitution is usually fine.
  # If LISTEN_ADDRESS could be, for example, '*' or contain other regex special chars,
  # more careful sed escaping would be needed. Assuming simple addresses here.
  sed -i "s/listen-address: '::'/listen-address: '$LISTEN_ADDRESS'/" "$CONFIG_FILE"
fi

if [ -n "$AUTH" ]; then
  USERNAME=$(echo "$AUTH" | cut -d ':' -f 1)
  PASSWORD=$(echo "$AUTH" | cut -d ':' -f 2)
  # Ensure the target lines for auth are correctly matched (e.g., exact spaces)
  sed -i "s/#auth:/auth:/" "$CONFIG_FILE"
  sed -i "s/#  username:/  username: $USERNAME/" "$CONFIG_FILE"
  sed -i "s/#  password:/  password: $PASSWORD/" "$CONFIG_FILE"
fi

# exec the server
exec /app/bin/hev-socks5-server "$CONFIG_FILE"
