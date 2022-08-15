# CPP Diff

Simple PoC implementation of rdiff, builds as a command line app that offers three commands:
  - **signature**: builds a signature file for a given file 
  - **delta**:  creates a delta between a file and a signature
  - **patch**: apply the delta to a file

For the serialization/deserialization **protobuf** has been used to simplify the binary encoding/decoding.

# Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/CPPDiff --help
```

# Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -S test -B build/test
cmake --build build/test
./build/test/CPPDiffTests
```
# Build everything at once

The project also includes an `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```bash
cmake -S all -B build
cmake --build build

# run tests
./build/test/CPPDiffTests

# run standalone
./build/standalone/CPPDiff --help

```


# Example Usage
```bash
# build a signature
./build/standalone/CPPDiff signature fixtures/file.txt

# build a delta
./build/standalone/CPPDiff delta signature.dat fixtures/modified_file.txt

# patch original file given delta
./build/standalone/CPPDiff patch delta.dat fixtures/file.txt

# verify that files are the same
diff patched.txt fixtures/modified_file.txt

```

# TODO

- Add a strong hash for each block as the checksum is prone to collisions
- Additional tests 
- Better documentation
- Performance improvements and code optimizations