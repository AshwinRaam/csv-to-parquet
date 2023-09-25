# CSV to Parquet Converter

This C++ project converts all CSV files from a given directory to Parquet format and stores them in a new directory.

## Getting Started

These instructions will help you set up the project on your local machine for development and testing purposes.

### Prerequisites

Ensure you have the following installed on your system:

- C++ Compiler (supporting C++17 for filesystem library)
- Apache Arrow and Apache Arrow Parquet libraries

## Compilation

This project uses CMake for building. To compile the code, run the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

Run the program using:

bashCopy code

`./csv_to_parquet <path_to_csv_folder> <path_to_new_folder_for_parquet>`

Where:

- `<path_to_csv_folder>` is the directory containing the CSV files to convert.
- `<path_to_new_folder_for_parquet>` is the directory where the Parquet files will be stored.

If the destination directory does not exist, the program will create it.

## Features

- Converts all CSV files in a directory to Parquet format.
- Provides meaningful error messages in case of file read/write failures or issues during the conversion process.
- Ensures efficient memory usage with Apache Arrow's memory pool.

## Contributing

If you find any issues or have suggestions for improvements, please submit a pull request or open an issue in the repository.
