# R-Type

R-Type is a classic side-scrolling shoot 'em up game where players pilot a spaceship to battle waves of alien enemies and bosses.

## Features

- UDP protocol
- server / client app

## Usage/Examples

### Server

```bash
./r-type_server
```

### Client

```bash
./r-type_client
```

## Installation

### Linux

Install r-type_client & r-type_server with CMake

```bash
cmake -S . -B build && cmake --build build -j "$(nproc)"
```

#### NixOS

Install r-type_client & r-type_server with CMake on nixOS

```bash
nix develop --command bash -c 'cmake -S . -B build && cmake --build build -j "$(nproc)"'
```

### Windows

Install r-type_client & r-type_server with CMake

```cmd
cmake -S . -B build
cmake --build build -- /maxcpucount:4
```

## Documentation

[Developer Documentation](./Docs/DOC.md)
[Protocol Documentation](./Docs/DOC.md)
[Architecture Documentation](./doc_doxygen/html/index.html)

## Tech Stack

**Client:** C++, SFML, ASIO

**Server:** C++, ASIO

## Running Tests

To run tests, run the following command

```bash
  npm run test
```

## Contributing

Contributions are always welcome!

See `contributing.md` for ways to get started.

Please adhere to this project's `code of conduct`.

## Authors

- [@Alea Chlodnik](https://www.github.com/AleaChlodnik)
- [@Marc.dva](https://www.github.com/Dvaking)
- [@QuentinLeguay](https://www.github.com/QuentinLeguay)
- [@Tom-Mendy](https://www.github.com/Tom-Mendy)

## Acknowledgements

- [Awesome Readme Templates](https://awesomeopensource.com/project/elangosundar/awesome-README-templates)
- [Awesome README](https://github.com/matiassingers/awesome-readme)
- [How to write a Good readme](https://bulldogjob.com/news/449-how-to-write-a-good-readme-for-your-github-project)

## Screenshots

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)
