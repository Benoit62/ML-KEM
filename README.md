# ML-KEM

C++ implentation of the post-quantum key establishment scheme ML-KEM


## Authors

- [@Benoît Wattinne](https://www.github.com/Benoit62)
- [@Aurélien Degain](https://www.github.com/aurelienDgn)
- [@Hamza Berbache](https://www.github.com/Hamz11)
- [@Louis Landouzy](https://www.github.com/LouisLandouzy)
- [@Enzo Barea](https://www.github.com/Ximaere)
- [@Clément Gorse](https://www.github.com/clementgorse)
- [@Rémi Protin](https://www.github.com/Remiprotin)

## Deployment

This guide will help you set up and run the project

#### Prerequisites

Before you begin, make sure you have the following installed on your system:

- C++ Compiler: Install a C++ compiler such as GCC or Clang. You can download GCC from the official website or install Clang using package managers like Homebrew (for macOS) or apt-get (for Linux).

[comment]: <> (- Visual Studio Code: [Download and install VSCode](https://code.visualstudio.com/))


### Installing project and library

The cryptopp library must be installed manually.
Example with g++ : ```g++-11 Bit.cpp BitArray.cpp Byte.cpp ByteArray.cpp Crypto.cpp NTT.cpp Zeta.cpp IntArray.cpp test.cpp XOF.cpp -o main -lcryptopp```

#### Compiling and Running the project


## Documentation

Ce dossier reprend l'ensemble des fonctions définies dans le [FIPS 203](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.203.ipd.pdf), à l'exception des fonctions K-PKE et de l'encapsulation avec ML-KEM. L'ensemble des fonctions auxilliaires ont été écrites de façon à être le plus modulable possible et mises sous forme de classe pour respecter le pseudo-code au mieux possible. Le code a été pensé pour faciliter le plus possible l'implémentation future des fonctions K-PKE et ML-KEM.
