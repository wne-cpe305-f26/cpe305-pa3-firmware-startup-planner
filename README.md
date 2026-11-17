# CPE305 Programming Assignment 03

Implement a deterministic firmware startup planner using sorting, directed-graph construction, depth-first search, and cycle detection.

The complete assignment specification is distributed through Kodiak and links to this starter repository.

## Required work

Implement `make_startup_plan` in `src/startup_planner.cpp` and add at least eight focused tests to `tests/student_tests.cpp`.

Do not change the required types or function declaration in `include/startup_planner.hpp`.

## Build and test

Run commands from the repository root:

```sh
make
./bin/startup_planner
make test
make sanitize
make clean
```

The supplied `Makefile` requires a C++20 `g++` or `clang++` compiler. To use Clang explicitly, run `make CXX=clang++`.

## Design notes

Replace this section with 200–300 words that:

- state your edge direction and graph representation;
- explain how sorted root and neighbor order make the result reproducible;
- explain why reversing DFS finish order places prerequisites first in a DAG;
- describe how the three DFS states detect a cycle; and
- give your time and auxiliary-space bounds in terms of `V` and `E`.

## Optional Codespaces environment

GitHub Codespaces is optional. Select **Code**, then **Codespaces**, then **Create codespace on main**. The container builds the tests after creation. Running `make test` will fail until `make_startup_plan` is implemented.

You may instead clone or download the repository and work locally on macOS or Linux.

## Submission archive

Create the ZIP only after your implementation and tests pass:

```sh
make clean
zip -r submission.zip . -x 'submission.zip' '.git/*' 'bin/*' 'build/*' '.vscode/*'
```

Open the ZIP and confirm that it contains the complete source tree before uploading it through Kodiak.
