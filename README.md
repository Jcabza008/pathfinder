# Pathfinder
Path Finding Algorithm and Tools

[![Validate](https://github.com/Jcabza008/pathfinder/actions/workflows/validate.yml/badge.svg?branch=master)](https://github.com/Jcabza008/pathfinder/actions/workflows/validate.yml)

## Usage
You can start the program by running `bin/pathfinder` from the project root.
### Help
Running `bin/pathfinder --help` will list the allows option and a quick description of each.
#### Allows options
  - `--help` : produce help message
  - `--map-file arg`: map file to load (required)
  - `--new-map`: create map
  - `--debug-level arg`: log level. Default: info. Supported: trace = 0, debug = 1, info = 2, warning = 3, error = 4.
  - `--map-width arg`: map width. Default: 800.
  - `--map-height arg`: map height. Default: 600.
  - `--algorithm arg`: algorithm to use. Default: dijkstrs. Supported: dijkstras and astar.
  - `--preset arg`: random gen preset. Ignores random gen parameres. Default: default. Supported: default, high and low.
  - `--visual`: if pass, the map will be drawn as it is being generated.
##### Advanced Random Generator Options
  - `--slope-var-mean arg`: mean of random slope variation.
  - `--slope-var-std arg`: standard deviation of random slope variation.
  - `--features-elevation-mean arg`: mean of random features height.
  - `--features-elevation-std arg`: standard deviation of random features height.
#### Graphic UI
The functionality of the buttons at the top; from left to right are: 
- `Save`: saves your map.
- `Find`: find the path from the selected point to the next point you click.
- `Clear Paths`: removes the found paths from the map.
- `Clear Map`: removes all features from the map, making it a flat terrain.
- `Random`: generates random features on the map.
- `Up` and `Down`: allow you to manually create features in the map at the selected point.

## Building
### Important commands:
- `make all`: will build all libraries and executables.
- `make pathfinder`: will build the pathfinder executable.
- `make mapgenerator`: will build the mapgenerator executable.
- `make tests`: will build the tests executable.
- `make run_*`: where * is either pathfinder, mapgenerator or tests will build the specified program and run it.

### Directory Structure
The directory structure to be followed is:
- `/src`: this is where `.cpp` files go.
- `/include`: this is where headers (`.h`) files go.
- `/tests`: this is where we writes tests.

### Makefile
As more libraries are created the Makefile must be updated by adding this library to the `LIBS` variable and by creating the required recipies to build this libraries. Existing recipes for building libraries are at the end of the file and can serve as examples on how to do this.

### Testing
We are using the Google Tests testing framework.
#### Structure
##### Files
Tests go on the `tests/` directory. An independent `.cpp` will be written for each library, these will have the format `<library_name>_test.cpp`.
##### Tests
Each tests is defined with the macro:
``` c++
TEST(<Test_Suite>, <Test_Name>)
```
For convention, `<Test_Suite>` should be replaces with the name of the class and `<Test_Name>` will be in the following format `methodName_briefTestDescription`. If the function being tested is not a class member then `<Test_Suite>` should be replaced by the name of the library (eg. `Graph`).

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
  - [How to install Google Tests on Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/). Google Tests libraries should end up at `/usr/local/lib/` to be compatible with the existing makefile.

### Nektos Act
This repositore contains Github Actions to validate Pull Request. If desired, it is possible to run this workflows locally before pushing you changes; this enables faster feedback.
In order to do this you must:
- Install Act: [Act Repository](https://github.com/nektos/act), installation instructions are on their README.md.
- Set Up Secrets: In order to run, this workflows use tokens stored in the form of secrets. You must create a Github Token with repo permissions, then create a     file in your computer and write:
  ```
  ACCESS_TOKEN=<your-generated-token>
  ```
  Then to run the workflows you execute: `act --secret-file <path-to-your-secret-file>`.

  Optionally you can specify:
    - `-W <path-of-desired-workflow>`.
    - `-j <name-of-specific-job>`.


