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
