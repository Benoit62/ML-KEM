# Go Development Environment Setup

This guide will help you set up a Go development environment in Visual Studio Code (VSCode) and run a Go program.

## Prerequisites

Before you begin, make sure you have the following installed on your system:

- Go: [Download and install Go](https://golang.org/dl/)
- Visual Studio Code: [Download and install VSCode](https://code.visualstudio.com/)

## Setting up Go in VSCode

1. Open VSCode and install the Go extension by Microsoft. You can find it in the VSCode Extensions marketplace or install it from the command palette (`Ctrl+Shift+X`) by searching for "Go".

2. Once the Go extension is installed, open the command palette (`Ctrl+Shift+P`) and search for "Go: Install/Update Tools". Select it to install the necessary Go tools.

3. Next, open the command palette again and search for "Go: Configure Workspace GOPATH". Select it and choose the appropriate option to set the GOPATH for your workspace.

4. Restart VSCode to apply the changes.

## Running a Go Program

1. Create a new Go file with a `.go` extension, for example `main.go`.

2. In the new Go file, write your Go program code.

3. To run the Go program, open the integrated terminal in VSCode by selecting `View -> Terminal` or using the shortcut `Ctrl+` backtick.

4. In the terminal, navigate to the directory where your Go file is located using the `cd` command.

5. Finally, use the `go run` command followed by the name of your Go file to run the program. For example:

    ```shell
    go run main.go
    ```

    The output of your Go program will be displayed in the terminal.

That's it! You now have a Go development environment set up in VSCode and know how to run a Go program.

Happy coding!