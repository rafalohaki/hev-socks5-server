# Optimized multi-stage Dockerfile for hev-socks5-server

#
# Build stage - Optimized for fast builds and minimal size
#
FROM alpine:3.19 AS builder

# Install build dependencies
RUN apk add --no-cache --virtual .build-deps \
    build-base \
    yaml-dev \
    git \
    cmake \
    ninja

# Set the working directory for the build stage
WORKDIR /tmp/hev-socks5-server

# Copy only necessary files first for better layer caching
COPY .git ./.git/
COPY .gitmodules ./
COPY third-part ./third-part/
COPY src ./src/
COPY Makefile build.mk ./
COPY conf ./conf/

# Initialize submodules and build
RUN set -ex && \
    echo "Initializing submodules..." && \
    git submodule update --init --recursive && \
    echo "Building optimized version..." && \
    make -j"$(nproc)" ENABLE_STATIC=1 && \
    echo "Installing to /app..." && \
    make install INSTDIR="/app" && \
    echo "Stripping binary for smaller size..." && \
    strip /app/bin/hev-socks5-server && \
    echo "Build completed successfully"

#
# Runtime stage - Security hardened and optimized
#
FROM alpine:3.19

# Set default timezone
ENV TZ=Europe/Warsaw

# Create dedicated user for security
RUN addgroup -g 1000 -S socks5 && \
    adduser -u 1000 -S socks5 -G socks5

# Install only runtime dependencies
RUN apk add --no-cache \
    tzdata \
    yaml \
    ca-certificates \
    && rm -rf /var/cache/apk/*

# Create required directories with proper permissions
RUN mkdir -p /app/bin /app/etc /app/logs /app/tmp && \
    chown -R socks5:socks5 /app

# Copy the built application from builder stage
COPY --from=builder --chown=socks5:socks5 /app/bin /app/bin/

# Copy configuration files
COPY --chown=socks5:socks5 conf/main.yml /app/etc/hev-socks5-server.yml

# Copy and set permissions for entrypoint script
COPY --chmod=755 --chown=socks5:socks5 docker/entrypoint.sh /app/entrypoint.sh

# Security hardening
RUN chmod 755 /app/entrypoint.sh && \
    chmod 755 /app/bin/hev-socks5-server && \
    # Remove unnecessary packages and clear cache
    rm -rf /var/cache/apk/* /tmp/* /var/tmp/*

# Switch to non-root user
USER socks5

# Set working directory
WORKDIR /app

# Health check for container health monitoring
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD netstat -tlnp 2>/dev/null | grep ":${PORT:-1080}" || exit 1

# Expose ports (both TCP and UDP for SOCKS5)
EXPOSE 1080/tcp 1080/udp

# Use exec form for better signal handling
ENTRYPOINT ["/app/entrypoint.sh"]

# Add labels for better container management
LABEL maintainer="your-email@domain.com" \
      description="High-performance SOCKS5 proxy server" \
      version="optimized" \
      org.opencontainers.image.source="https://github.com/heiher/hev-socks5-server"
