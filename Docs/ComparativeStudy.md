# Comparative Study

## Technologies Overview

This section provides a comparative analysis of the key technologies and tools used in our project. Each decision was based on specific project needs, focusing on optimizing performance, ease of use, and cross-platform compatibility.

### Build System

<!-- #### CMake

CMake was selected as the build system for this project due to its widespread use in C++ development and its flexibility in handling complex build processes. It simplifies the build configuration across different platforms, including Windows and Linux, which aligns with our project's requirement for cross-platform compatibility. CMake's extensive community support and integration with other tools (e.g., IDEs, CI pipelines) also make it a reliable choice for managing large-scale C++ projects.

#### Make

While Make is a classic tool for Linux-based builds, it lacks the multi-platform support and modern features offered by CMake.

#### Bazel

Bazel offers powerful build capabilities, but its learning curve and specific focus on larger projects made CMake a more fitting choice for our team. -->

| Criteria                     | CMake                                             | Make                                       | Bazel                                            |
| ---------------------------- | ------------------------------------------------- | ------------------------------------------ | ------------------------------------------------ |
| **Strengths**                | Cross-platform, flexible, integrates with IDEs/CI | Simple, well-known for Linux               | Powerful for large-scale projects                |
| **Weaknesses**               | Steeper learning curve                            | Limited to Linux, lacks modern features    | Steep learning curve, complexity in setup        |
| **Platform Support**         | Windows, Linux, macOS                             | Primarily Linux                            | Cross-platform                                   |
| **Configuration Complexity** | Medium                                            | Low                                        | High                                             |
| **Tool Integration**         | Integrates with CI, IDEs, and test frameworks     | Limited to Linux-based build chains        | Integrates well with distributed systems         |
| **Documentation**            | Extensive online resources and community support  | Simple, well-known                         | Comprehensive but more challenging for beginners |
| **Reason for Choice**        | Chosen for flexibility and community support      | Not chosen due to limited platform support | Not chosen due to complexity for this project    |

CMake was chosen for its cross-platform capabilities and extensive community support, making it suitable for managing our C++ project across multiple operating systems. In contrast, Make was ruled out due to its limitations in cross-platform support, while Bazel's complexity deterred its use for this particular project.

### Programming language

<!-- #### C++

C++ is the mandated language for this project, chosen for both the client and server components. On the client side, C++ is a natural fit for creating high-performance graphical applications, particularly in video game development, where its rich ecosystem of libraries (such as SFML) is highly advantageous. For the server side, C++ is preferred for its efficiency, particularly in managing concurrent tasks and multi-threaded processing, which are critical for handling multiple game sessions and players. The language’s performance characteristics ensure low-latency and real-time responsiveness, which are essential for a networked gaming experience.

#### Rust

While Rust offers modern memory safety features and excellent performance, the team opted for C++ due to its more mature ecosystem and the team's existing expertise.

#### Java

Java’s cross-platform capabilities are strong, but its garbage collection introduces latency unsuitable for real-time gaming. -->

| Criteria                | C++                                                  | Rust                                                | Java                                                 |
| ----------------------- | ---------------------------------------------------- | --------------------------------------------------- | ---------------------------------------------------- |
| **Strengths**           | High performance, low-level memory control           | Modern memory safety, concurrency, high performance | Cross-platform, robust libraries, easy to learn      |
| **Weaknesses**          | Complex memory management, manual threading          | Smaller ecosystem, less C++ library integration     | Garbage collection leads to latency                  |
| **Learning Curve**      | Steep due to manual memory and thread management     | Moderate, but higher due to ownership model         | Easy, particularly for Java-based developers         |
| **Concurrency**         | Manual control over threads                          | Built-in concurrency primitives, safer model        | Built-in multithreading, but slower                  |
| **Ecosystem**           | Mature, vast libraries (e.g., SFML)                  | Growing but smaller than C++                        | Massive, especially in enterprise environments       |
| **Use Case in Project** | Client-server architecture, real-time responsiveness | Not chosen due to ecosystem immaturity              | Not suited for real-time, low-latency scenarios      |
| **Reason for Choice**   | Chosen for performance and team expertise            | Not chosen due to ecosystem maturity                | Not chosen due to unsuitability for real-time gaming |

C++ was selected as the primary programming language due to its performance advantages and the team's existing expertise. While Rust offers modern features, its smaller ecosystem led to its exclusion. Java was not suitable due to its garbage collection, which could introduce unacceptable latency in a real-time gaming context.

### Networking

<!--
#### ASIO

it was suggested to us in subject

We chose the Asio library for network communication due to its robust support for asynchronous operations and cross-platform compatibility, essential for building a performant and responsive application. Asio simplifies the development of networked systems by abstracting away low-level networking details, while still allowing precise control over socket-level communication. Its support for both synchronous and asynchronous I/O makes it an excellent choice for developing scalable network applications in C++, particularly those requiring real-time interaction, like our multiplayer game.

#### Boost.Asio

Boost.Asio is a feature-rich version of Asio integrated within the Boost library. While similar, we chose standalone Asio for its lighter footprint.

#### Raw Sockets

We ruled out using raw socket programming due to the platform-specific complexities and lack of built-in asynchronous support, which Asio handles more elegantly. -->

| Criteria                 | Asio                                               | Boost.Asio                                 | Raw Sockets                                    |
| ------------------------ | -------------------------------------------------- | ------------------------------------------ | ---------------------------------------------- |
| **Strengths**            | Cross-platform, asynchronous networking            | Feature-rich, part of Boost library        | Full control over protocols                    |
| **Weaknesses**           | Requires manual memory management                  | Larger footprint due to Boost integration  | Platform-specific complexities, low-level      |
| **Asynchronous Support** | Robust asynchronous I/O                            | Same as Asio, but integrated in Boost      | Limited, requires manual setup                 |
| **Abstraction Level**    | High, simplifies network handling                  | High, simplifies and extends functionality | Low, manual control needed for every operation |
| **Community Support**    | Large due to use in modern C++ projects            | Extensive due to being part of Boost       | Minimal, more used in academic and niche cases |
| **Reason for Choice**    | Chosen for scalability and asynchronous operations | Not chosen due to larger footprint         | Not chosen due to complexity                   |

The Asio library was selected for its asynchronous capabilities and cross-platform support, making it ideal for the networked nature of our application. Boost.Asio was considered but ultimately not chosen due to its larger footprint. Raw sockets were also ruled out due to the complexities involved in manual management.

### Graphic

<!-- #### SFML

SFML was chosen for handling the client’s graphical interface, audio, and user input. Its simplicity and ease of use make it ideal for quickly developing 2D graphics, a core aspect of our game client. SFML also provides comprehensive support for windowing, event handling, and multimedia tasks, including real-time audio and input management. Its C++ integration ensures smooth compatibility with the rest of the project, and being cross-platform, it supports our goal of deploying the game on multiple operating systems. Our team’s familiarity with SFML further accelerates development.

#### SDL (Simple DirectMedia Layer)

While SDL is another popular choice for multimedia development, we did not choose it due to its steeper learning curve and focus on lower-level operations. SFML’s higher-level abstractions better suited our need for rapid development of a 2D graphical interface.

#### NCurses

We also considered NCurses, but it was ruled out due to its limitations in rendering graphical sprites and complex multimedia tasks. NCurses is well-suited for terminal-based UIs, but it is not appropriate for a graphically intensive project like ours. -->

| Criteria               | SFML                                               | SDL                                              | NCurses                                                      |
| ---------------------- | -------------------------------------------------- | ------------------------------------------------ | ------------------------------------------------------------ |
| **Strengths**          | Easy to use, good for 2D graphics and multimedia   | Powerful for multimedia, supports wide platforms | Lightweight, good for terminal-based interfaces              |
| **Weaknesses**         | Limited to 2D, less powerful for low-level control | Steep learning curve, more focused on low-level  | No graphical sprite support, unsuitable for complex graphics |
| **Learning Curve**     | Easy due to higher-level abstractions              | Steep due to low-level operations                | Very low                                                     |
| **Multimedia Support** | Good for audio, input, and window management       | Comprehensive for multimedia, but more complex   | None, designed for terminal interaction                      |
| **Cross-Platform**     | Yes, supports Windows, macOS, Linux                | Yes, very strong cross-platform capabilities     | Yes, but limited to terminal applications                    |
| **Reason for Choice**  | Chosen for simplicity and 2D game development      | Not chosen due to complexity for our needs       | Not suitable for graphically intensive games                 |

SFML was selected for its simplicity and effectiveness in handling 2D graphics, making it ideal for the game client. SDL was considered but not chosen due to its complexity. NCurses was ruled out as it could not support the graphical requirements of the project.

### Architecture

<!--
#### ECS (Entity-Component-System)

because it is use by Unreal Engine & Unity, witch are Industry Standard

We implemented an Entity-Component-System (ECS) architecture to improve the modularity, scalability, and performance of the game. ECS separates data (components) from behavior (systems) and entities, which makes it easier to manage game objects and their interactions. This design pattern is widely used in game development due to its ability to efficiently update entities in bulk through system processing, which is particularly beneficial when managing large numbers of game objects. Additionally, ECS simplifies the addition of new features, as components and systems can be modified or extended independently without disrupting the overall architecture.

#### Object-Oriented Architecture

While traditional object-oriented design is widely used, ECS offers greater scalability and flexibility in handling complex interactions between game objects, making it the more suitable choice for our needs.

#### other possible Architecture (to find)

... -->

| Criteria              | Entity-Component-System (ECS)                                  | Object-Oriented Design                                              |
| --------------------- | -------------------------------------------------------------- | ------------------------------------------------------------------- |
| **Strengths**         | Highly modular, scalable, good for handling large game objects | Familiar design pattern for most developers                         |
| **Weaknesses**        | More complex to implement, requires learning ECS patterns      | Limited scalability for large, interactive systems                  |
| **Scalability**       | High, allows efficient bulk entity processing                  | Low to medium, less efficient in handling large numbers of entities |
| **Extensibility**     | Easy to add new systems and components                         | More rigid, can be difficult to add new functionality               |
| **Performance**       | High, optimized for game development and interaction           | Slower due to object inheritance and dependencies                   |
| **Reason for Choice** | Chosen for handling multiple game objects efficiently          | Not chosen due to scalability concerns                              |

An Entity-Component-System (ECS) architecture was implemented to enhance modularity and scalability. While traditional object-oriented design is familiar, ECS proved to be more efficient for managing the interactions of numerous game objects.

### Version Control

<!-- #### Git

Git was used as the version control system to manage the project’s codebase. Its distributed nature allows each team member to work independently, while still providing powerful collaboration tools like branching, merging, and conflict resolution. Git's ability to track the entire project history ensures that changes can be rolled back if necessary, making it an indispensable tool for maintaining code integrity throughout the development process.

#### Mercurial

we have to use git & our team have less knowledge on this software -->

| Criteria              | Git                                                       | Mercurial                                 |
| --------------------- | --------------------------------------------------------- | ----------------------------------------- |
| **Strengths**         | Distributed version control, powerful collaboration tools | Strong branching and merging support      |
| **Weaknesses**        | Slightly complex for beginners                            | Less community support                    |
| **Reason for Choice** | Chosen for distributed development and team familiarity   | Not chosen due to lack of team experience |

Git was selected for its robust version control capabilities and team familiarity, facilitating effective collaboration. Mercurial was not considered due to a lack of experience within the team.

### Host codebase

<!-- #### Github

GitHub was selected to host our repository, providing a central hub for our team to collaborate. In addition to source control, GitHub offers project management features like issue tracking, pull requests, and code reviews. These features help streamline the development process by facilitating better team communication and ensuring that all changes are thoroughly reviewed before being merged into the main branch.

#### Gitlab

we have to use github & our team have less knowledge on this software

#### GitBucket

we have to use github & our team have less knowledge on this software -->

| Criteria                 | GitHub                                    | GitLab                                | GitBucket                            |
| ------------------------ | ----------------------------------------- | ------------------------------------- | ------------------------------------ |
| **Ease of Use**          | Very user-friendly, intuitive interface   | More complex but feature-rich         | Simple, but lacks advanced features  |
| **CI/CD Integration**    | Excellent integration with GitHub Actions | Strong CI/CD capabilities             | Limited CI/CD capabilities           |
| **Community Support**    | Large community, active development       | Growing community, good documentation | Smaller community, less support      |
| **Self-Hosting Options** | Limited self-hosting options              | Strong self-hosting capabilities      | Basic self-hosting options           |
| **Reason for Choice**    | Familiarity and extensive features        | Not chosen due to lack of familiarity | Not chosen for lesser known features |

GitHub was chosen to host the codebase due to its user-friendly interface and strong integration with CI/CD tools. Other options like GitLab and GitBucket were not pursued due to familiarity issues.

### Continuous Integration / Continuous Deployment (CI/CD)

<!-- #### Github Action

We integrated GitHub Actions into the project to automate the build and testing processes. GitHub Actions enables continuous integration, where the project is built and tested automatically every time code is pushed to the repository. This reduces the likelihood of introducing bugs and ensures that the project remains in a deployable state at all times. Additionally, GitHub Actions supports parallel job execution and caching, which accelerates the build process, particularly when testing on multiple platforms (Windows and Linux).

#### Jenkins

we didn't use jenkins for this project because it is self-host & our team have less knowledge on this software -->

| Criteria                | GitHub Actions                                    | Jenkins                                           | Travis CI                                      |
| ----------------------- | ------------------------------------------------- | ------------------------------------------------- | ---------------------------------------------- |
| **Strengths**           | Simple to set up, integrates well with GitHub     | Highly customizable, powerful for larger projects | Flexible, widely supported                     |
| **Weaknesses**          | Limited customization compared to Jenkins         | Requires self-hosting, more complex to manage     | Limited compared to Jenkins and GitHub Actions |
| **Ease of Setup**       | Easy, cloud-based, minimal configuration required | Complex, requires server and manual configuration | Easy but less powerful                         |
| **Scalability**         | Scales well for small to medium projects          | Highly scalable for large projects                | Moderate scalability                           |
| **Platform Support**    | Cross-platform builds for Windows, Linux          | Cross-platform but requires manual setup          | Wide platform support                          |
| **Use Case in Project** | Chosen for its seamless integration with GitHub   | Not chosen due to complexity for this project     | Not chosen due to limited power and features   |

GitHub Actions was selected for CI/CD due to its simplicity and seamless integration with the GitHub repository. Jenkins, while powerful, was deemed too complex for our needs, and Travis CI lacked the advanced features we were looking for.

### Documentation Generation

<!-- #### Doxygen

We used Doxygen to automatically generate documentation from our C++ codebase. Doxygen extracts comments and code annotations, producing well-structured and navigable documentation that helps both current and future developers understand the project. This ensures that our documentation is always up-to-date with the latest code changes. Doxygen’s support for multiple output formats (HTML, LaTeX, etc.) provides flexibility in how we present the documentation, and it integrates seamlessly with GitHub Actions to generate and publish documentation as part of the CI pipeline.

#### Sphinx

While Sphinx is popular for Python projects, Doxygen’s specialization in C++ projects and its wide adoption in the C++ community made it a better fit. -->

| Criteria                | Doxygen                                                           | Sphinx                                              |
| ----------------------- | ----------------------------------------------------------------- | --------------------------------------------------- |
| **Strengths**           | Specialized for C++, automatic generation from code               | Powerful for Python projects, flexible formatting   |
| **Weaknesses**          | Limited to code documentation, not suitable for all project types | Less suited for C++ projects                        |
| **Supported Languages** | Primarily C++, some support for other languages                   | Python-focused, not well-suited for C++             |
| **Output Formats**      | HTML, LaTeX, PDF, multiple formats available                      | HTML, PDF, multiple formats, but not focused on C++ |
| **Integration with CI** | Easy integration with CI tools like GitHub Actions                | Also integrates well with CI/CD                     |
| **Use Case in Project** | Chosen for automatic documentation generation from C++ code       | Not chosen due to focus on Python                   |

## Algorithms and Protocols

### Network Protocol

<!-- #### UDP

We chose the UDP protocol for real-time communication between the client and server. Unlike TCP, which guarantees reliable delivery of packets, UDP provides faster transmission by forgoing such guarantees, which is critical for time-sensitive applications like multiplayer games. In scenarios where minor packet loss is acceptable, such as position updates in a game, UDP offers a performance advantage, ensuring lower latency and smoother gameplay.

#### TCP

TCP was considered but ultimately not chosen due to its overhead in ensuring reliable delivery, which would introduce additional latency. While TCP is ideal for applications requiring reliable transmission, its slower nature makes it less suited for real-time gaming scenarios. -->

|                          | UDP                                                                     | TCP                                                |
| ------------------------ | ----------------------------------------------------------------------- | -------------------------------------------------- |
| **Strengths**            | Fast, low latency, no overhead for real-time applications               | Reliable, ensures delivery and ordering of packets |
| **Weaknesses**           | No guaranteed delivery, potential packet loss                           | Higher latency due to packet verification overhead |
| **Use Case in Project**  | Real-time game data transmission, tolerates packet loss for performance | Reliable but introduces unacceptable delays        |
| **Packet Loss Handling** | No automatic recovery, manual error detection needed                    | Automatic error recovery, guarantees packet order  |
| **Latency**              | Very low                                                                | Higher due to retransmission in case of failure    |
| **Use Case**             | Chosen for fast, low-latency communication                              | Not chosen due to higher latency                   |

## Development Practices

### Formatter

#### Clang Formatter

We used Clang Format within our GitHub Actions pipeline to ensure consistent code formatting across the project. This automated tool enforces coding style guidelines, reducing stylistic discrepancies between different team members' contributions and making the codebase more maintainable.

#### Other formatter
