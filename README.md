# Code

[![](https://img.shields.io/github/stars/VLTHellolin/Code?style=flat-square)](https://github.com/VLTHellolin/Code/stargazers)

Competitive code written by @VLTHellolin.

**Local judging environment:**

| Key | Value |
| --: | :-- |
| CPU | 12th Gen Intel i5-1240P (16) @ 2.112GHz |
| OS | Manjaro Linux on Windows 10 x86_64 |
| Kernel | 5.15.146.1-microsoft-standard-WSL2 |
| `gcc --version` | `gcc (GCC) 13.2.1 20230801` |
| `clang --version` | `clang version 16.0.6` |
| `rustc -V` | `rustc 1.77.1 (7cf61ebde 2024-03-27)` |
| `node -v` | `v21.6.2` |
| `python -V` | `Python 3.11.8` |
| `java --version` | `openjdk 17.0.10 2024-01-16 LTS` |
| `kotlin -version` | `Kotlin version 1.9.22-release-704 (JRE 17.0.10+7-LTS)` |

| Language | Compiling | Execution |
| -------: | :-------- | :-------- |
| C | `gcc $FILE.cpp -o $FILE -std=c2x -O2 -lm -DLOCAL` | `./$FILE` |
| C++ | `clang++ $FILE.cpp -o $FILE -std=c++20 -O2 -lm -DLOCAL -stdlib=libstdc++ -Wall -Wextra -march=native -fno-asm -ffast-math` | `./$FILE` |
| Rust | `rustc $FILE.rs -o $FILE --edition 2021 -W warnings -O` | `./$FILE` |
| Javascript | `node --check $FILE.js` | `node $FILE.js` |
| Typescript | `tsc $FILE.ts --target ESNext --module commonjs --moduleResolution node` | `node $FILE.js` |
| Python | `python -m py_compile $FILE.py` | `python $FILE.py` |
| Java | `javac $FILE.java` | `java $FILE` |
| Kotlin | `kotlinc-jvm $FILE.kt -include-runtime -jvm-target 21` | `java $FILE` |
