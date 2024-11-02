# Developer Documentation

## Standard

**Formatter**: Clang with config
**Folder Name:** PascalCase
**File Name:**  snake\_case

**Code**:

- **Class:** PascalCase
- **Function:** camelCase
- **Variable:** camelCase
- **Comment:** Above function & next to line (right side)

**Commit:** gc \-m "\[TITLE\] name of changed item" \-m "description"

- **ADD:** Add a feature
- **UPD:** Update/modify a feature
- **FIX:** Fix an error
- **DEL**: Delete a file/folder
- **MERGE**

## CI / CD

github action cache:

- use documentation: [Github Action Cache](https://docs.github.com/en/actions/writing-workflows/choosing-what-your-workflow-does/caching-dependencies-to-speed-up-workflows#comparing-artifacts-and-dependency-caching)

auto-format:

- use git-auto-commit-action:
  - documentation: [git-auto-commit-action](https://github.com/stefanzweifel/git-auto-commit-action)

## Dev Container

on linux with X11

```bash
xhost local:root
```

open the dev container with visual studio code

## Archi

### Global



```mermaid
graph TD
    A["Main Application (R-Type)"]

    subgraph Entity_Component_System
        B[EntityManager]
        C[ComponentManager]
        D[SystemManager]
        E[TextureManager]
    end

    subgraph Client
        F[Client Networking]
        G[Main Menu]
    end

    subgraph Components
        H[PositionComponent]
        I[VelocityComponent]
        J[SpriteComponent]
        K[HealthComponent]
        L[ScoreComponent]
        M[ForceWeaponComponent]
        N[TextComponent]
    end

    subgraph Systems
        O[RenderSystem]
        P[UpdateSystem]
    end

    A --> Entity_Component_System
    Entity_Component_System --> B
    Entity_Component_System --> C
    Entity_Component_System --> D
    Entity_Component_System --> E

    B --> H
    B --> I
    B --> J
    B --> K
    B --> L
    B --> M
    B --> N

    C --> H
    C --> I
    C --> J
    C --> K
    C --> L
    C --> M
    C --> N

    D --> O
    D --> P

    A --> Client
    F --> B
    F --> C
    G --> A
```

This schema depicts the core architecture:

- **Entity Component System**: Contains the primary managers (EntityManager, ComponentManager, SystemManager, and TextureManager).
- **Components**: Represents individual components such as Position, Velocity, Sprite, Health, Score, Weapon, and Text.
- **Systems**: Systems like RenderSystem and UpdateSystem operate on the entities and components.
- **Client**: Manages client networking and interfaces such as the main menu, connecting it to the ECS.

Let me know if any specific details or additional components need to be included!


### Server



```mermaid
graph TD
    subgraph Server
        SRV_MAIN["Main Server"]
        SRV_ECS["ECS Components"]
        SRV_NETWORK["Network Module"]
        SRV_DB["Database"]
    end

    subgraph Client
        CLI_MAIN["Client Application"]
        CLI_RENDER["Rendering Module"]
        CLI_INPUT["Input System"]
    end

    CLI_MAIN --> CLI_RENDER
    CLI_MAIN --> CLI_INPUT
    CLI_MAIN <--> SRV_NETWORK
    SRV_MAIN --> SRV_ECS
    SRV_MAIN --> SRV_NETWORK
    SRV_MAIN --> SRV_DB

    subgraph ECS
        ComponentManager["Component Manager"]
        EntityManager["Entity Manager"]
        SystemManager["System Manager"]
    end

    SRV_ECS --> ComponentManager
    SRV_ECS --> EntityManager
    SRV_ECS --> SystemManager
```

This structure:

1. **Server** has subsystems for managing entities and components via ECS.
2. **Client** communicates with the server's network module and has separate modules for rendering and input.
3. **Database** holds persistent data shared with the main server.

You can adapt this further with more specific ECS details or add networking protocols if needed. Let me know if you'd like modifications!


### Client

```mermaid
graph TD
    subgraph ECS Architecture
        EntityManager -->|manages| Entity
        Entity -->|contains| ComponentManager
        Entity -->|contains| Component

        subgraph Components
            Component --> PositionComponent
            Component --> SpriteComponent
            Component --> HealthComponent
            Component --> HitboxComponent
            Component --> ForceWeaponComponent
        end

        subgraph Systems
            SystemManager --> RenderSystem
            SystemManager --> UpdateSystem
            SystemManager --> CollisionSystem
            SystemManager --> InputSystem
            SystemManager --> NetworkSystem
        end
    end

    subgraph Texture Management
        TextureManager -->|loads| SpriteComponent
        RenderSystem -->|uses| TextureManager
    end

    subgraph Networking
        NetworkSystem --> Client
        Client -->|connects to| Server
        Client -->|sends/receives| Messages
    end
```

In this diagram:

-  **EntityManager** manages entities.
-  **ComponentManager** contains various components that define entity attributes.
-  **SystemManager** oversees systems that execute game logic (e.g., `RenderSystem` for rendering, `UpdateSystem` for game state, `CollisionSystem` for collisions, etc.).
-  **TextureManager** loads textures used by RenderSystem.
-  **NetworkSystem** handles networking with the server, where `Client` connects to `Server`.

### Network

```mermaid
graph TD
    subgraph Client
        C_Context[Asio Context]
        C_Socket[Socket]
        C_Endpoint[Endpoint]
        C_MsgProcess[Message Process]
        C_MsgQueue[Message Queue]
    end

    subgraph Server
        S_Context[Asio Context]
        S_Socket[Socket]
        S_ClientSocket[Client Socket]
        S_MsgProcess[Message Process]
        S_MsgQueue[Message Queue]
    end

    S_Socket -->| generate for new client connection | S_ClientSocket
    S_Socket -->| add incomming message| S_MsgQueue
    S_MsgProcess -->| send message| S_ClientSocket
    S_MsgQueue -->| take last message| S_MsgProcess
    S_ClientSocket -->| Send message| C_Endpoint
    C_Socket -->|Connect/Disconnect| S_Socket
    C_Endpoint -->| add incomming message | C_MsgQueue
    C_MsgQueue -->| take last message| C_MsgProcess
    C_MsgProcess -->| send message if needed| C_Socket
```

### ECS - System

```mermaid
graph TD
    subgraph ECS_Architecture
        Entity[Entity]
        Component[Component]
        System[System]
        EntityManager[EntityManager]
        ComponentManager[ComponentManager]
        SystemManager[SystemManager]
        TextureManager[TextureManager]
    end

    Entity -->|contains| Component
    EntityManager -->|manages| Entity
    ComponentManager -->|manages| Component
    SystemManager -->|manages| System
    TextureManager -->|provides| Component

    Entity -->|interacts with| System
    System -->|operates on| Component
    SystemManager -->|operates on| EntityManager
    SystemManager -->|accesses| ComponentManager
    ComponentManager -->|provides| Component
    TextureManager -->|provides| Entity
```

This structure represents the core relations among the elements in your ECS setup. The **EntityManager** and **ComponentManager** handle entities and components, respectively, while the **SystemManager** coordinates systems, which interact with entities and components as needed. The **TextureManager** is specific to components, aiding with graphics rendering.


### Entities

```mermaid
classDiagram
    direction TB
    class EntityManager {
        - entities : List~Entity~
        + createEntity() : Entity
        + getEntity(id) : Entity
        + removeEntity(id)
    }

    class ComponentManager {
        - components : Map~ComponentType, List~Component~~
        + addComponent(entity, component)
        + getComponent(entity, type) : Component
        + removeEntityComponents(entity)
    }

    class SystemManager {
        - systems : List~System~
        + addSystem(system : System)
        + removeSystem(system : System)
        + updateSystems()
    }

    class TextureManager {
        - textures : Map~TextureID, Texture~
        + getTexture(id) : Texture
        + loadTexture(path)
    }

    class Entity {
        - id : UUID
        + getId() : UUID
    }

    class Component {
        <<interface>>
        + entityID : UUID
    }

    class System {
        <<interface>>
        + update()
    }

    EntityManager --> Entity : manages
    ComponentManager --> Component : contains
    SystemManager --> System : contains
    Entity --> Component : aggregates
    SystemManager --> ComponentManager : interacts with
    SystemManager --> EntityManager : interacts with
    TextureManager ..> ComponentManager : uses
```


This schema provides a visual overview of how different managers in the ECS work together within the R-Type architecture. The relationships show `EntityManager` managing `Entity` instances, `ComponentManager` handling the `Component` instances, and `SystemManager` managing `System` instances, which interact with both managers to perform updates&#8203;:contentReference[oaicite:0]{index=0}.


### Componant

```mermaid
classDiagram
    class Entity {
        +int _id
        +getId()
    }

    class Component {
        <<interface>>
    }

    class PositionComponent {
        +float x
        +float y
    }

    class VelocityComponent {
        +float speed
    }

    class HealthComponent {
        +int health
        +int max_health
    }

    class ForceWeaponComponent {
        +float bullet_speed
        +int damage
    }

    class EntityManager {
        +createEntity()
        +removeEntity()
        +getEntity()
    }

    class ComponentManager {
        +addComponent()
        +getComponent()
        +removeEntityFromComponent()
    }

    class System {
        <<interface>>
        +update()
    }

    class RenderSystem {
        +render()
    }

    class UpdateSystem {
        +update()
    }

    Entity --> Component : has
    Component <|-- PositionComponent
    Component <|-- VelocityComponent
    Component <|-- HealthComponent
    Component <|-- ForceWeaponComponent

    EntityManager --> Entity : manages
    ComponentManager --> Component : manages
    System <|-- RenderSystem
    System <|-- UpdateSystem
```
