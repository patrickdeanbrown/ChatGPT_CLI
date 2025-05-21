# ChatGPT CLI

**ChatGPT CLI** is a command-line interface that allows you to interact with OpenAI's ChatGPT API directly from your terminal, built from start to finish using an AI-first product development workflow.

![Demo Video](assets/demo.apng)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
  - [macOS](#macos)
  - [Linux](#linux)
- [Usage](#usage)
- [License](#license)

## Introduction

**ChatGPT CLI** is a lightweight, colorful, and flexible command-line tool designed to chat with OpenAI's ChatGPT API. It provides a straightforward interface for sending messages, viewing chat history, and saving conversations—all from the terminal.

### Project Goals

This project was developed with the following objectives:

- **AI-First Workflow**: Demonstrates the application of AI in product management and software development, showcasing how AI tools can be integrated into the software creation process.

- **Educational and Demonstrative Value**: Serves as a practical example of end-to-end product development, encompassing everything from ideation and design to implementation and deployment.

## Features

- **Interactive Command Line Interface**: Engage with ChatGPT through a series of intuitive commands.
- **Chat History Management**: Easily view, save, and clear your chat history from the command line.
- **File Integration**: Import input from files and save conversations to text files.
- **Cross-Platform Support**: Compatible with macOS and Linux.

## Installation

### macOS

1. **Install Prerequisites**:
   Install required dependencies using Homebrew:
   ```sh
   brew install curl nlohmann-json termcolor
   ```

2. **Clone the Repository**:
   ```sh
   git clone https://github.com/your-repo/ChatGPT_CLI.git
   cd ChatGPT_CLI
   ```

3. **Build the Project**:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Set Up ChatGPT API Key**:
   Configure the API key as an environment variable:
   ```sh
   export OPENAI_KEY="your-openai-api-key"
   ```

5. **Run the Application**:
   ```sh
   ./chatgpt_cli
   ```

### Linux

1. **Install Prerequisites**:
   Install required dependencies:
   ```sh
   sudo apt-get install libcurl4-openssl-dev nlohmann-json3-dev
   ```
   For `termcolor`, follow the installation instructions from the [termcolor repository](https://github.com/ikalnytskyi/termcolor).

2. **Clone the Repository**:
   ```sh
   git clone https://github.com/your-repo/ChatGPT_CLI.git
   cd ChatGPT_CLI
   ```

3. **Build the Project**:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Set Up ChatGPT API Key**:
   Configure the API key as an environment variable:
   ```sh
   export OPENAI_KEY="your-openai-api-key"
   ```

5. **Run the Application**:
   ```sh
   ./chatgpt_cli
   ```

## Usage

Inspired by magic commands in Python notebooks, commands are preceded by `%` and can be entered after the prompt:

- `%save [filename]` — Save your chat to a file.
- `%readfile [filename]` — Read input from a file in the current working directory.
- `%clear` — Clear the chat history.
- `%deletelast` — Delete the last record in the chat history.
- `%printhistory` — Print the chat history to the console.
- `%quit` — Exit the program.
- `%help` — Display the help menu.

## Running Unit Tests

This project uses [Google Test](https://github.com/google/googletest) for unit testing. The tests are built as part of the standard build process if Google Test is found by CMake (it's configured to be fetched automatically if not present).

To build and run the unit tests:

1.  **Navigate to the Build Directory**:
    If you haven't built the project yet, or to ensure a clean build for tests:
    ```sh
    # From the project root directory
    rm -rf build # Optional: for a clean start
    mkdir build
    cd build
    ```

2.  **Configure with CMake**:
    This step prepares the build system.
    ```sh
    cmake ..
    ```

3.  **Build the Tests**:
    You can build all targets, which includes the `unit_tests` executable, or build the `unit_tests` target specifically.
    ```sh
    make unit_tests
    ```
    Alternatively, to build all targets:
    ```sh
    make
    ```

4.  **Run the Tests**:
    There are two common ways to run the tests from the `build` directory:

    *   **Using CTest**:
        CTest is CMake's testing tool. It will discover and run tests automatically.
        ```sh
        ctest
        ```
        For more verbose output, especially on failures:
        ```sh
        ctest --output-on-failure
        ```

    *   **Running the Executable Directly**:
        You can also run the compiled test executable directly.
        ```sh
        ./unit_tests
        ```

All tests should pass if the environment is configured correctly and there are no issues with the code.

## License

This project is licensed under the BSD 2-Clause License. See the [LICENSE](LICENSE) file for details.
