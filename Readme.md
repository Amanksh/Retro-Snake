This guide will walk you through the process of setting up and running this project on a Windows machine.

## Prerequisites

- Make sure you have a C++ compiler installed on your machine. If not, you can download and install one from [here](https://www.mingw-w64.org/).
- Install [CMake](https://cmake.org/download/) for building the project.
- Install [Git](https://git-scm.com/download/win) for version control.

## Steps

1. **Clone the repository**

   Open your command prompt and navigate to the directory where you want to clone the project. Run the following command:

   ```bash
   git clone <repository-url>
   ```

   Replace `<repository-url>` with the URL of the Git repository.

2. **Navigate to the project directory**

   Change your current directory to the project's directory:

   ```bash
   cd <project-directory>
   ```

   Replace `<project-directory>` with the name of the directory that was created when you cloned the repository.

3. **Build the project**

   Use CMake to build the project. First, create a new directory for the build files and navigate into it:

   ```bash
   mkdir build
   cd build
   ```

   Then, run CMake to generate the build files:

   ```bash
   cmake ..
   ```

   After that, compile the project:

   ```bash
   cmake --build .
   ```

4. **Run the project**

   After building the project, you can run it with the following command:

   ```bash
   ./main
   ```

   If everything was set up correctly, you should now see the project running.
