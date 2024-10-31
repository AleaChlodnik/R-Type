# Comparative Study

## Technologies Overview

This section provides a comparative analysis of the key technologies and tools used in our project. Each decision was based on specific project needs, focusing on optimizing performance, ease of use, and cross-platform compatibility.

### Build System

The **Build System** table compares various build systems that can be employed for project compilation and management. This comparison evaluates strengths, weaknesses, platform support, and integration capabilities, helping the team choose the most suitable system for handling the complexities of cross-platform development.

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

In the **Programming Language** table, a detailed analysis of C++, Rust, and Java is presented to identify the best programming language for the project's needs. The assessment considers performance, ecosystem maturity, learning curves, and suitability for real-time gaming applications, ensuring that the chosen language aligns with the team's expertise and project requirements.

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

The **Networking** table examines different networking libraries available for the project, highlighting their strengths, weaknesses, and support for asynchronous operations. This analysis focuses on how each option supports the application's networked components and the overall performance, guiding the selection of an efficient and effective networking solution.

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

The **Graphic** table evaluates various graphics libraries, including SFML, SDL, and NCurses, based on criteria such as ease of use, multimedia support, and cross-platform capabilities. This comparison aids in identifying the most appropriate library for developing the game's graphical interface, balancing simplicity with functionality.

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

In the **Architecture** table, two design patterns Entity-Component-System (ECS) and Object-Oriented Design are compared. The focus is on scalability, performance, and modularity, ultimately helping to determine the architecture that best supports the project's requirements and enhances manageability as the game grows.

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

The **Version Control** table assesses Git and Mercurial as version control systems. It highlights their strengths and weaknesses in collaboration, ease of use, and community support, providing insights into which system can effectively manage the project’s codebase and streamline team collaboration.

| Criteria              | Git                                                       | Mercurial                                 |
| --------------------- | --------------------------------------------------------- | ----------------------------------------- |
| **Strengths**         | Distributed version control, powerful collaboration tools | Strong branching and merging support      |
| **Weaknesses**        | Slightly complex for beginners                            | Less community support                    |
| **Reason for Choice** | Chosen for distributed development and team familiarity   | Not chosen due to lack of team experience |

Git was selected for its robust version control capabilities and team familiarity, facilitating effective collaboration. Mercurial was not considered due to a lack of experience within the team.

### Host codebase

In the **Host Codebase** table, three popular code hosting platforms—GitHub, GitLab, and GitBucket—are compared on their user experience, CI/CD integration, and community support. This analysis helps in selecting the platform that best meets the project's hosting and collaboration needs.

| Criteria                 | GitHub                                    | GitLab                                | GitBucket                            |
| ------------------------ | ----------------------------------------- | ------------------------------------- | ------------------------------------ |
| **Ease of Use**          | Very user-friendly, intuitive interface   | More complex but feature-rich         | Simple, but lacks advanced features  |
| **CI/CD Integration**    | Excellent integration with GitHub Actions | Strong CI/CD capabilities             | Limited CI/CD capabilities           |
| **Community Support**    | Large community, active development       | Growing community, good documentation | Smaller community, less support      |
| **Self-Hosting Options** | Limited self-hosting options              | Strong self-hosting capabilities      | Basic self-hosting options           |
| **Reason for Choice**    | Familiarity and extensive features        | Not chosen due to lack of familiarity | Not chosen for lesser known features |

GitHub was chosen to host the codebase due to its user-friendly interface and strong integration with CI/CD tools. Other options like GitLab and GitBucket were not pursued due to familiarity issues.

### Continuous Integration / Continuous Deployment (CI/CD)

The **Continuous Integration / Continuous Deployment (CI/CD)** table reviews different CI/CD tools, focusing on their ease of setup, scalability, and platform support. This comparison assists in identifying the best CI/CD solution for automating builds and deployments, ensuring efficient development cycles.

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

In the **Documentation Generation** table, Doxygen and Sphinx are compared in terms of their strengths, supported languages, and integration capabilities with CI tools. This evaluation guides the selection of a documentation generation tool that can efficiently create and maintain documentation for the project.

| Criteria                | Doxygen                                                           | Sphinx                                              |
| ----------------------- | ----------------------------------------------------------------- | --------------------------------------------------- |
| **Strengths**           | Specialized for C++, automatic generation from code               | Powerful for Python projects, flexible formatting   |
| **Weaknesses**          | Limited to code documentation, not suitable for all project types | Less suited for C++ projects                        |
| **Supported Languages** | Primarily C++, some support for other languages                   | Python-focused, not well-suited for C++             |
| **Output Formats**      | HTML, LaTeX, PDF, multiple formats available                      | HTML, PDF, multiple formats, but not focused on C++ |
| **Integration with CI** | Easy integration with CI tools like GitHub Actions                | Also integrates well with CI/CD                     |
| **Use Case in Project** | Chosen for automatic documentation generation from C++ code       | Not chosen due to focus on Python                   |

### Network Protocol

The **Network Protocol** section specifically analyzes network protocols, comparing UDP and TCP. This table outlines their respective strengths and weaknesses, aiding in the selection of a protocol that best suits the project's communication needs, particularly in terms of latency and reliability.

|                          | UDP                                                                     | TCP                                                |
| ------------------------ | ----------------------------------------------------------------------- | -------------------------------------------------- |
| **Strengths**            | Fast, low latency, no overhead for real-time applications               | Reliable, ensures delivery and ordering of packets |
| **Weaknesses**           | No guaranteed delivery, potential packet loss                           | Higher latency due to packet verification overhead |
| **Use Case in Project**  | Real-time game data transmission, tolerates packet loss for performance | Reliable but introduces unacceptable delays        |
| **Packet Loss Handling** | No automatic recovery, manual error detection needed                    | Automatic error recovery, guarantees packet order  |
| **Latency**              | Very low                                                                | Higher due to retransmission in case of failure    |
| **Use Case**             | Chosen for fast, low-latency communication                              | Not chosen due to higher latency                   |

### Formatter

In software development, maintaining consistent code formatting is crucial for enhancing readability, collaboration, and overall code quality. Formatting tools help enforce coding standards across a project, allowing team members to focus on functionality rather than stylistic discrepancies. This section evaluates three popular formatting tools Clang Formatter, Prettier, and AStyle based on various criteria such as strengths, weaknesses, ease of setup, integration capabilities, and supported languages. The analysis aims to guide the selection of the most suitable formatting tool for our project, ensuring that it aligns with our development needs and team expertise.

| Criteria                | Clang Formatter                                      | Prettier                                        | AStyle                                                                 |
| ----------------------- | ---------------------------------------------------- | ----------------------------------------------- | ---------------------------------------------------------------------- |
| **Strengths**           | Highly customizable, supports C++ standards          | Easy to use, wide support for various languages | Supports multiple languages, flexible options                          |
| **Weaknesses**          | Configuration can be complex                         | Primarily focused on JavaScript, HTML, and CSS  | Limited modern features compared to others                             |
| **Ease of Setup**       | Moderate, requires understanding of configuration    | Very easy to set up and use                     | Simple setup but requires more manual configuration for specific rules |
| **Integration**         | Integrates well with CI/CD tools like GitHub Actions | Excellent integration with JavaScript projects  | Can be integrated into various build systems                           |
| **Supported Languages** | Primarily C/C++, some support for other languages    | JavaScript, TypeScript, HTML, CSS               | C, C++, Java, and more                                                 |
| **Reason for Choice**   | Chosen for its robust C++ support and community      | Not chosen as it doesn't support C++ adequately | Not chosen due to lack of focus on C++                                 |

After evaluating the three formatting tools, **Clang Formatter** emerged as the best choice for our project due to its strong support for C++ standards and extensive customization options. Although it requires a moderate level of setup and understanding, its integration with CI/CD tools like GitHub Actions aligns well with our workflow. Prettier, while user-friendly and well-suited for web technologies, was ruled out due to its lack of support for C++. AStyle, although versatile in terms of language support, did not provide the modern features necessary for our C++ development. By selecting Clang Formatter, we aim to enhance code maintainability and foster a collaborative coding environment.
