# Comparative Study

## Technologies

### CMake

We chose CMake to compile the project because it is well-suited for C++ projects. CMake offers flexibility and power, making it a popular choice for managing complex builds across different platforms.

### C++

C++ was selected as the primary language for both the client and server. For the client, it allows the creation of graphical applications, as C++ is a standard in video game development with a rich ecosystem of libraries for this purpose. On the server side, C++ enables efficient processing, especially with its robust support for multithreading, allowing us to handle multiple processes effectively.

### ASIO

We chose the Asio library for network communication due to its cross-platform capabilities, supporting both Windows and Linux systems. Asio simplifies asynchronous communication, which is essential for a high-performance networked application.

### SFML

We chose SFML (Simple and Fast Multimedia Library) to handle graphics, audio, and user input. SFML provides an intuitive and easy-to-use interface for rendering 2D graphics, making it ideal for creating the graphical components of our client application. Additionally, SFML supports various multimedia tasks, including window management, audio playback, and real-time inputs, which are critical for a smooth gaming experience. SFML is cross-platform and integrates seamlessly with C++, making it a suitable choice for our project’s needs.

### ECS (Entity-Component-System)

We implemented the Entity-Component-System (ECS) architecture in our project to achieve modularity and scalability. ECS is widely used in game development as it separates data (components) from behavior (systems) and entities, making it easier to manage game objects and their interactions. This approach allows us to efficiently update game objects by processing them in batches through systems, improving performance, particularly when managing large numbers of entities. ECS also simplifies adding new features or behaviors without affecting existing code, as components and systems can be modified or extended independently.

### Git

We used Git as our version control system to manage code changes efficiently. Git allows multiple developers to collaborate on the project simultaneously, enabling us to track changes, manage different branches, and resolve conflicts when merging code. With its distributed nature, Git ensures that each team member has a complete copy of the project’s history, making it easier to revert changes and maintain the integrity of the codebase.

### Github

We hosted the project on GitHub, a cloud-based platform for managing Git repositories. GitHub provides a central location for our code, making it accessible to all team members, while also providing issue tracking and project management tools. GitHub facilitates open collaboration, enabling us to submit pull requests, review code, and maintain clear documentation. It also integrates seamlessly with other tools, helping streamline our workflow.

### Github Action

We integrated GitHub Actions into our project for continuous integration (CI) and continuous deployment (CD). GitHub Actions automates tasks such as building the project, running tests, and deploying code whenever changes are pushed to the repository. This ensures that every code change is thoroughly tested in various environments (e.g., Linux and Windows) before being merged into the main branch, reducing the risk of introducing bugs. GitHub Actions also provides caching and parallel job execution, which speeds up the build process and makes the CI/CD pipeline more efficient.

### Doxygen

We utilized Doxygen for generating documentation directly from the C++ codebase. Doxygen is a powerful tool that helps create detailed, structured, and easily navigable documentation by extracting comments from the source code. This approach ensures that the documentation is always in sync with the latest code changes, making it easier for both current and future developers to understand the structure and functionality of the project. Doxygen supports multiple output formats, such as HTML and LaTeX, providing flexibility for different documentation needs. It also integrates well with other tools, enabling automated documentation generation as part of the CI pipeline.

## Algorithm

### UDP

We opted to use UDP over TCP for network communication because it provides faster data transfer and greater control over the communication process. While UDP does not guarantee reliable delivery like TCP, it is ideal for real-time applications where speed is critical, such as in video games.

### Development Practices

### Clang Formatter

in the github action
