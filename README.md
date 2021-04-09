# Pathfinder
Path Finding Algorithm and Tools

[![Validate](https://github.com/Jcabza008/pathfinder/actions/workflows/validate.yml/badge.svg?branch=master)](https://github.com/Jcabza008/pathfinder/actions/workflows/validate.yml)

# Contributing
## Set up
### VS Code
- Install VS code and open the project as a VS Code Workspace; the workspace file is at `.vscode/pathfinder.code-workspace`.
- The workspace will the recommend the required extensions, among them:
  - CPP Tools by Microsoft: Intellisense and other tools.
  - Trailing Spaces by Shardulm94: This extension highlights trailing spaces, helps to keep the code clean.
  - TestMate by Matepek: Integrates with Google Tests and allows you to see them and run them on the VS Code Tests Panel.
  - Doxydoc Gen by Cschlosser: helps to generate documentation.

### Google Tests:
  - You can run `./scripts/setup_gtest.sh` to install and setup Google Tests.
  - [How to install Google Tests on Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/). Google Tests libraries should end up at           `/usr/lib/` to be compatible with the existing makefile.

### Nektos Act
This repositore contains Github Actions to validate Pull Request. If desired, it is possible to run this workflows locally before pushing you changes; this enables faster feedback.
In order to do this you must:
- Install Act: [Act Repository](https://github.com/nektos/act), installation instructions are on their README.md.
- Set Up Secrets: In order to run, this workflows use tokens stored in the form of secrets. You must create a Github Token with repo permissions, then create a     file in your computer and write:
  ```
  ACCESS_TOKEN=<your-generated-token>
  ```
  Then to run you the workflows you execute: `act --secret-file <path-to-your-secret-file>`.

  Optionally you can specify:
    - `-W <path-of-desired-workflow>`.
    - `-j <name-of-specific-job>`.

## Building
### Important commands:
- `make all`: will build all libraries and executables.
- `make pathfinder`: will build the pathfinder executable.
- `make mapgenerator`: will build the mapgenerator executable.
- `make tests`: will build the tests executable.
- `make run_*`: where * is either pathfinder, mapgenerator or tests will build the specified program and run it.

## Directory Structure
The directory structure to be followed is:
- `/src`: this is where `.cpp` files go.
- `/include`: this is where headers (`.h`) files go.
- `/tests`: this is where we writes tests.

## Makefile
As more libraries are created the Makefile must be updated by adding this library to the `LIBS` variable and by creating the required recipies to build this libraries. Existing recipes for building libraries are at the end of the file and can serve as examples on how to do this.

## Testing
We are using the Google Tests testing framework. 
### Structure
#### Files
Tests go on the `tests/` directory. An independent `.cpp` will be written for each library, these will have the format `<library_name>_test.cpp`.
#### Tests
Each tests is defined with the macro:
``` c++
TEST(<Test_Suite>, <Test_Name>)
```
For convention, `<Test_Suite>` should be replaces with the name of the class and `<Test_Name>` will be in the following format `methodName_briefTestDescription`.
