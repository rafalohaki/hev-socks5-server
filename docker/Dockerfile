# Dockerfile for hev-socks5-server

#
# Build stage
#
FROM alpine AS builder

# Set the working directory for the build stage
WORKDIR /tmp/hev-socks5-server

# Copy the local repository content to the working directory in the container
COPY . .

# Install build dependencies (including Git), initialize submodules, build, and cleanup
RUN apk update \
 && apk add --no-cache --virtual .build-deps \
      build-base yaml-dev git \
 && echo "Current directory: $(pwd)" \
 && echo "Listing files: $(ls -la)" \
 && echo "Initializing and updating submodules..." \
 && git submodule update --init --recursive \
 && echo "Building with make..." \
 && make -j"$(nproc)" \
 && echo "Installing..." \
 && make install INSTDIR="/app" \
 && echo "Cleaning build artifacts..." \
 && make clean \
 && echo "Cleaning up build environment..." \
 && cd / \
 && rm -rf /tmp/hev-socks5-server \
 && apk del .build-deps \
 && rm -rf /var/cache/apk/*

#
# Runtime stage
#
FROM alpine

ENV TZ=Europe/Warsaw

# Add runtime dependencies
RUN apk update \
  && apk add --no-cache tzdata yaml \
  && rm -rf /var/cache/apk/*

# Copy the built application from the builder stage
COPY --from=builder /app /app/

# Ensure the configuration directory (or at least the file) is writable by the 'nobody' user
# if the entrypoint script needs to modify it.
# /app/etc is a common convention. If your config file is directly in /app/
# you might chown /app/hev-socks5-server.yml if it exists, or ensure /app/etc is created and chowned.
# Assuming /app/etc will contain the config file as per previous entrypoint scripts.
RUN mkdir -p /app/etc && chown nobody:nobody /app/etc

# Copy the entrypoint script
# Assuming your entrypoint.sh is in a 'docker' subdirectory of your build context.
# If it's at the root of your build context with the Dockerfile, change the source path.
COPY docker/entrypoint.sh /app/entrypoint.sh
RUN chmod +x /app/entrypoint.sh

USER nobody
ENTRYPOINT ["/app/entrypoint.sh"]
