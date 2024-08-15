# ChatGPT CLI

ChatGPT CLI is a command-line interface for chatting with OpenAI's ChatGPT API built from start to finish with an AI-first product development workflow.

![Demo Video](assets/demo.apng)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
  - [Windows](#windows)
  - [macOS](#macos)
  - [Linux](#linux)
- [Usage](#usage)
- [License](#license)

## Introduction

ChatGPT CLI is a lightweight, flexible command-line tool that allows users to chat via OpenAI's ChatGPT API directly from their terminal. The application provides a simple interface for sending messages to ChatGPT, viewing chat history, and saving conversations

This project was conceived and developed with the following goals in mind:

- **AI-First Workflow**: The project showcases the application of AI in product management and software development, highlighting how AI tools can be used effectively in the creation of software products.
- **Educational and Demonstrative Value**: Beyond its functionality, this project serves as a demonstration of my ability to manage the end-to-end product development process, from ideation and design to implementation and deployment.

## Features

- **Interactive Command Line Interface**: Easily interact with ChatGPT through a series of intuitive commands.
- **Chat History Management**: View, save, and clear your chat history directly from the command line.
- **File Integration**: Read inputs from files and save your conversations to text files.
- **Cross-Platform Support**: The application is built to run on Windows, macOS, and Linux.

## Installation

### macOS

1. **Install Prerequisites**:
   - Install `libcurl`, `nlohmann/json`, and `termcolor` using Homebrew:
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

4. **Run the Application**:
   ```sh
   ./chatgpt_cli
   ```

### Linux

1. **Install Prerequisites**:
   - Install `libcurl`:
     ```sh
     sudo apt-get install libcurl4-openssl-dev
     ```
   - Install `nlohmann/json`:
     ```sh
     sudo apt-get install nlohmann-json3-dev
     ```
   - Install `termcolor` via installation instructions on its repo [termcolor](https://github.com/ikalnytskyi/termcolor) 

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

4. **Set up ChatGPT API Key**
   
   The app calls the ChatGPT API and will need the following environment variable set up.
   ```sh
   export OPENAI_KEY="your-openai-api-key"
   ```

5. **Run the Application**:
   ```sh
   ./chatgpt_cli
   ```


## Usage

Inspired by magic commands in Python notebooks, commands are preceeded by `%` and can be entered in after the prompt.

- %save [filename]              Saves your chat as a file.
- %readfile [filename]          Reads in a file from the cwd.
- %clear                        Clears the chat history.
- %deletelast                   Deletes the last record in the chat history.
- %printhistory                 Prints the chat history to the console.
- %quit                         Exits the program.
- %help                         Prints the help menu.


## License

This project is licensed under the BSD 2-Clause License. See the [LICENSE](LICENSE) file for details.
