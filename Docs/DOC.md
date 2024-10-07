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

## Communication Protocol

## Client-Server Protocol Overview

### 1. Introduction

This document outlines the protocol used for communication between the Client and the Server. It details the request and response messages, including the format, message types, and the flow of communication.

## 2. Architecture Overview

```cpp
struct vf2d {
    float x, y;
};
struct entityInfo_s {
    uint32_t nUniqueID;
    uint32_t nAvatarID;

    // uint32_t nHealth;
    // uint32_t nAmmo;
    // uint32_t nKills;
    // uint32_t nDeaths;

    // uint32_t Ping;

    // float fRadius;

    vf2d vPosition;
    vf2d vVel;
}entityInfo_t;
```

Headers
Body (optional)

```plaintext
+---------------------------+                  +---------------------------+
|         Client            |                  |          Server           |
+---------------------------+------------------+---------------------------+
|                           |       Send       |                           |
|  process message          | <--------------- | header: DeadEntityMessage |
|                           |                  | body: entityInfo_t        |
|                           |                  |                           |
|                           |     Response     |                           |
| header: DeadEntityMessage | ---------------> |                           |
| body: entityInfo_t        |                  |                           |
+---------------------------+------------------+---------------------------+
|                           |       Send       |                           |
|  process message          | <--------------- | header: InfoEntityMessage |
|                           |                  | body: entityInfo_t        |
|                           |                  |                           |
|                           | NO FOR OPTIMIZATION |                        |
|                           |     Response     |                           |
| header: InfoEntityMessage | ---------------> |                           |
| body: entityInfo_t        |                  |                           |
+---------------------------+------------------+---------------------------+
|                           |       Send       |                           |
| header: FireBulletMessage | ---------------> |  process message          |
| body: entityInfo_t        |                  |                           |
|                           |                  |                           |
|                           |     Response     |                           |
|                           | <--------------- | header: FireBulletMessage |
|                           |                  | body: entityInfo_t        |
+---------------------------+------------------+---------------------------+
|                           |       Send       |                           |
| header: MovePlayerMessage | ---------------> |  process message          |
| body: entityInfo_t        |                  |                           |
|                           |                  |                           |
|                           | NO FOR OPTIMIZATION |                        |
|                           |     Response     |                           |
|                           | <--------------- | header: MovePlayerMessage |
|                           |                  | body: entityInfo_t        |
+---------------------------+------------------+---------------------------+
```
