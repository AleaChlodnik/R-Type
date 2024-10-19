# Comparative Study

## Technologies Overview

This section provides a comparative analysis of the key technologies and tools used in our project. Each decision was based on specific project needs, focusing on optimizing performance, ease of use, and cross-platform compatibility.

### Build System

#### CMake

CMake was selected as the build system for this project due to its widespread use in C++ development and its flexibility in handling complex build processes. It simplifies the build configuration across different platforms, including Windows and Linux, which aligns with our project's requirement for cross-platform compatibility. CMake's extensive community support and integration with other tools (e.g., IDEs, CI pipelines) also make it a reliable choice for managing large-scale C++ projects.

#### Make

While Make is a classic tool for Linux-based builds, it lacks the multi-platform support and modern features offered by CMake.

#### Bazel

Bazel offers powerful build capabilities, but its learning curve and specific focus on larger projects made CMake a more fitting choice for our team.

### Programming language

#### C++

C++ is the mandated language for this project, chosen for both the client and server components. On the client side, C++ is a natural fit for creating high-performance graphical applications, particularly in video game development, where its rich ecosystem of libraries (such as SFML) is highly advantageous. For the server side, C++ is preferred for its efficiency, particularly in managing concurrent tasks and multi-threaded processing, which are critical for handling multiple game sessions and players. The language’s performance characteristics ensure low-latency and real-time responsiveness, which are essential for a networked gaming experience.

#### Rust

While Rust offers modern memory safety features and excellent performance, the team opted for C++ due to its more mature ecosystem and the team's existing expertise.

#### Java

Java’s cross-platform capabilities are strong, but its garbage collection introduces latency unsuitable for real-time gaming.

### Networking

#### ASIO

it was suggested to us in subject

We chose the Asio library for network communication due to its robust support for asynchronous operations and cross-platform compatibility, essential for building a performant and responsive application. Asio simplifies the development of networked systems by abstracting away low-level networking details, while still allowing precise control over socket-level communication. Its support for both synchronous and asynchronous I/O makes it an excellent choice for developing scalable network applications in C++, particularly those requiring real-time interaction, like our multiplayer game.

#### Boost.Asio

Boost.Asio is a feature-rich version of Asio integrated within the Boost library. While similar, we chose standalone Asio for its lighter footprint.

#### Raw Sockets

We ruled out using raw socket programming due to the platform-specific complexities and lack of built-in asynchronous support, which Asio handles more elegantly.

### Graphic

#### SFML

SFML was chosen for handling the client’s graphical interface, audio, and user input. Its simplicity and ease of use make it ideal for quickly developing 2D graphics, a core aspect of our game client. SFML also provides comprehensive support for windowing, event handling, and multimedia tasks, including real-time audio and input management. Its C++ integration ensures smooth compatibility with the rest of the project, and being cross-platform, it supports our goal of deploying the game on multiple operating systems. Our team’s familiarity with SFML further accelerates development.

#### SDL (Simple DirectMedia Layer)

While SDL is another popular choice for multimedia development, we did not choose it due to its steeper learning curve and focus on lower-level operations. SFML’s higher-level abstractions better suited our need for rapid development of a 2D graphical interface.

#### NCurses

We also considered NCurses, but it was ruled out due to its limitations in rendering graphical sprites and complex multimedia tasks. NCurses is well-suited for terminal-based UIs, but it is not appropriate for a graphically intensive project like ours.

### Architecture

#### ECS (Entity-Component-System)

because it is use by Unreal Engine & Unity, witch are Industry Standard

We implemented an Entity-Component-System (ECS) architecture to improve the modularity, scalability, and performance of the game. ECS separates data (components) from behavior (systems) and entities, which makes it easier to manage game objects and their interactions. This design pattern is widely used in game development due to its ability to efficiently update entities in bulk through system processing, which is particularly beneficial when managing large numbers of game objects. Additionally, ECS simplifies the addition of new features, as components and systems can be modified or extended independently without disrupting the overall architecture.

#### Object-Oriented Architecture

While traditional object-oriented design is widely used, ECS offers greater scalability and flexibility in handling complex interactions between game objects, making it the more suitable choice for our needs.

#### other possible Architecture (to find)

...

### Version Control

#### Git

Git was used as the version control system to manage the project’s codebase. Its distributed nature allows each team member to work independently, while still providing powerful collaboration tools like branching, merging, and conflict resolution. Git's ability to track the entire project history ensures that changes can be rolled back if necessary, making it an indispensable tool for maintaining code integrity throughout the development process.

#### Github

GitHub was selected to host our repository, providing a central hub for our team to collaborate. In addition to source control, GitHub offers project management features like issue tracking, pull requests, and code reviews. These features help streamline the development process by facilitating better team communication and ensuring that all changes are thoroughly reviewed before being merged into the main branch.

#### Gitlab

we have to use github & our team have less knowledge on this software

### Continuous Integration / Continuous Deployment (CI/CD)

#### Github Action

We integrated GitHub Actions into the project to automate the build and testing processes. GitHub Actions enables continuous integration, where the project is built and tested automatically every time code is pushed to the repository. This reduces the likelihood of introducing bugs and ensures that the project remains in a deployable state at all times. Additionally, GitHub Actions supports parallel job execution and caching, which accelerates the build process, particularly when testing on multiple platforms (Windows and Linux).

#### Jenkins

we didn't use jenkins for this project because it is self-host & our team have less knowledge on this software

### Documentation Generation

#### Doxygen

We used Doxygen to automatically generate documentation from our C++ codebase. Doxygen extracts comments and code annotations, producing well-structured and navigable documentation that helps both current and future developers understand the project. This ensures that our documentation is always up-to-date with the latest code changes. Doxygen’s support for multiple output formats (HTML, LaTeX, etc.) provides flexibility in how we present the documentation, and it integrates seamlessly with GitHub Actions to generate and publish documentation as part of the CI pipeline.

#### Sphinx

While Sphinx is popular for Python projects, Doxygen’s specialization in C++ projects and its wide adoption in the C++ community made it a better fit.

## Algorithms and Protocols

### Network Protocol

#### UDP

We chose the UDP protocol for real-time communication between the client and server. Unlike TCP, which guarantees reliable delivery of packets, UDP provides faster transmission by forgoing such guarantees, which is critical for time-sensitive applications like multiplayer games. In scenarios where minor packet loss is acceptable, such as position updates in a game, UDP offers a performance advantage, ensuring lower latency and smoother gameplay.

#### TCP

TCP was considered but ultimately not chosen due to its overhead in ensuring reliable delivery, which would introduce additional latency. While TCP is ideal for applications requiring reliable transmission, its slower nature makes it less suited for real-time gaming scenarios.

### Development Practices

### Clang Formatter

We used Clang Format within our GitHub Actions pipeline to ensure consistent code formatting across the project. This automated tool enforces coding style guidelines, reducing stylistic discrepancies between different team members' contributions and making the codebase more maintainable.
