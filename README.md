# R-Type

## Install

### Linux

```bash
cmake -S . -B build && cmake --build build -j "$(nproc)"
```

#### NixOS

deploy environment
```bash
nix develop
```
```bash
cmake -S . -B build && cmake --build build -j "$(nproc)"
```

## Usage

### Server

#### Linux

```bash
./r-type_server
```

### Client

#### Linux

```bash
./r-type_client
```

## Examples

