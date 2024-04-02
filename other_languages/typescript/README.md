# TypeScript Development Environment Setup

This guide will help you set up a TypeScript development environment in Visual Studio Code (VSCode) and run a TypeScript program.

## Prerequisites

Before you begin, make sure you have the following installed on your system:

- Node.js: [Download and install Node.js](https://nodejs.org/en/download/)
- Visual Studio Code: [Download and install VSCode](https://code.visualstudio.com/)

## Setting up TypeScript in VSCode

1. Open VSCode and install the TypeScript extension by Microsoft. You can find it in the VSCode Extensions marketplace or install it from the command palette (`Ctrl+Shift+X`) by searching for "TypeScript".

2. Once the TypeScript extension is installed, open the command palette (`Ctrl+Shift+P`) and search for "TypeScript: Select TypeScript Version". Choose the latest version of TypeScript available.

3. Next, open the command palette again and search for "TypeScript: Configure Project". Select it to create a `tsconfig.json` file in your workspace.

4. Restart VSCode to apply the changes.

## Running a TypeScript Program

1. Create a new TypeScript file with a `.ts` extension, for example `main.ts`.

2. In the new TypeScript file, write your TypeScript program code.

3. To run the TypeScript program, open the integrated terminal in VSCode by selecting `View -> Terminal` or using the shortcut `Ctrl+` backtick.

4. In the terminal, navigate to the directory where your TypeScript file is located using the `cd` command.

5. Finally, use the `tsc` command followed by the name of your TypeScript file to compile it into JavaScript. For example:

    ```shell
    tsc main.ts
    ```

    This will generate a JavaScript file with the same name as your TypeScript file.

6. To run the JavaScript file, use the `node` command followed by the name of the generated JavaScript file. For example:

    ```shell
    node main.js
    ```

    The output of your TypeScript program will be displayed in the terminal.

That's it! You now have a TypeScript development environment set up in VSCode and know how to run a TypeScript program.

Happy coding!