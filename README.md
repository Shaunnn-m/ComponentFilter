# ComponentFilter

The PGM Image Processor is a command-line tool designed for processing PGM (Portable Graymap Format) images. It supports extracting connected components based on a user-defined threshold,
filtering components by size, and writing the results back to a new PGM file.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- GCC compiler (with C++20 support)
- Make
- Catch2 (for running tests)

### Compiling

To compile the main application, run the following command from the root of the project directory:

bash
    make

Running the Program:
./pgm_processor <input_pgm_file> -s <min_size> <max_size> -p -t <threshold> -w <output_pgm_file>
e.g ./pgm_processor Shapes.pgm -s 25000 7538076 -p -t 128 -w output.pgm

where:
    <input_pgm_file> is the path to the input PGM image.
    <min_size> and <max_size> define the size range for filtering components.
    <threshold> is the threshold for detecting components.
    <output_pgm_file> is the path to the output PGM image.

Running Tests:
    make test

Authors:
    Thabang Mokoena
