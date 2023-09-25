#include <iostream>
#include <filesystem>
#include <arrow/io/api.h>
#include <arrow/csv/api.h>
#include <parquet/arrow/writer.h>

namespace fs = std::filesystem;

std::shared_ptr<arrow::Table> read_csv(const std::string& file_path) {
    auto input_result = arrow::io::ReadableFile::Open(file_path);
    if (!input_result.ok()) {
        throw std::runtime_error("Failed to open CSV file: " + input_result.status().ToString());
    }

    auto read_options = arrow::csv::ReadOptions::Defaults();
    auto parse_options = arrow::csv::ParseOptions::Defaults();
    auto convert_options = arrow::csv::ConvertOptions::Defaults();

    arrow::io::IOContext io_context;
    auto reader_result = arrow::csv::TableReader::Make(io_context, input_result.ValueOrDie(), read_options, parse_options, convert_options);
    if (!reader_result.ok()) {
        throw std::runtime_error("Failed to create CSV reader: " + reader_result.status().ToString());
    }

    auto table_result = reader_result.ValueOrDie()->Read();
    if (!table_result.ok()) {
        throw std::runtime_error("Failed to read CSV file: " + table_result.status().ToString());
    }

    return table_result.ValueOrDie();
}

void write_parquet(const std::string& file_path, const std::shared_ptr<arrow::Table>& table) {
    auto output = arrow::io::FileOutputStream::Open(file_path);
    if (!output.ok()) {
        throw std::runtime_error("Failed to open Parquet file: " + output.status().ToString());
    }

    if (!parquet::arrow::WriteTable(*table, arrow::default_memory_pool(), *output, 128 * 1024).ok()) {
        throw std::runtime_error("Failed to write to Parquet file.");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <path_to_csv_folder> <path_to_new_folder_for_parquet>" << std::endl;
        return 1;
    }

    fs::path source_directory = argv[1]; // Using the first command line argument
    fs::path dest_directory = argv[2];   // Using the second command line argument

    // Create the destination directory if it doesn't exist
    if (!fs::exists(dest_directory)) {
        fs::create_directory(dest_directory);
    }

    for (const auto& entry : fs::directory_iterator(source_directory)) {
        if (entry.path().extension() == ".csv") {
            try {
                std::shared_ptr<arrow::Table> table = read_csv(entry.path().string());

                fs::path dest_file = dest_directory / (entry.path().stem().string() + ".parquet");
                write_parquet(dest_file.string(), table);
            } catch (const std::exception& e) {
                std::cerr << "Error processing " << entry.path().string() << ": " << e.what() << std::endl;
            }
        }
    }

    std::cout << "Conversion completed!" << std::endl;
    return 0;
}
