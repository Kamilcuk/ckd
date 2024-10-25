FROM alpine:latest AS abase
RUN apk add --no-cache py3-jinja2 cmake build-base ninja git doxygen graphviz

FROM abase AS alpine
WORKDIR /app
COPY . .
RUN make CONFARGS=-DCKD_NOSANITIZE=1 CC=gcc

FROM abase AS make_doxygen
WORKDIR /app
COPY . .
RUN make doxygen

FROM scratch AS doxygen
COPY --from=make_doxygen /app/public .

###############################################################################

FROM ubuntu AS base
RUN printf "%s\n" 'APT::Install-Suggests "0";' 'APT::Install-Recommends "0";' >> /etc/apt/apt.conf.d/00-docker
ENV DEBIAN_FRONTEND=noninteractive
ENV PIP_BREAK_SYSTEM_PACKAGES=1
RUN set -x && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake ninja-build make clang gcc python3-pip git time && \
    pip3 --no-cache-dir install jinja2 && \
    rm -rf /var/lib/apt/lists/*

FROM base AS clang
WORKDIR /app
COPY . .
RUN make CC=clang

FROM base AS gcc
WORKDIR /app
COPY . .
RUN make CC=gcc

FROM intel/oneapi AS intel
RUN printf "%s\n" 'APT::Install-Suggests "0";' 'APT::Install-Recommends "0";' >> /etc/apt/apt.conf.d/00-docker
ENV DEBIAN_FRONTEND=noninteractive
ENV PIP_BREAK_SYSTEM_PACKAGES=1
RUN set -x && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        cmake ninja-build make python3-pip git time && \
    pip3 --no-cache-dir install jinja2 && \
    rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN make CC=icx-cc CONFARGS=-DCKD_NOSANITIZE=1

