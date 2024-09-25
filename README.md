# R-Type

## Install

### Linux

```bash
cmake -S . -B build && cmake --build build -j "$(nproc)"
```

#### NixOS

deploy environment

```bash
nix develop --command bash -c 'cmake -S . -B build && cmake --build build -j "$(nproc)"'
```

## Usage

### Server

```bash
./r-type_server
```

### Client

```bash
./r-type_client
```

## Examples
