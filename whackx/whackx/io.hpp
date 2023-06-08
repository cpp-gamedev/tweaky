#pragma once
#include <string>

namespace whackx::io {
///
/// \brief Setup data directory.
/// \returns true if found / created successfully.
/// \param exe_path Path to executable (argv[0]).
/// \param data_dir_uri URI of data directory to search for / create.
///
/// This function stores the exe path and searches upwards for a directory named data_dir_uri.
/// If not found, the working directory is searched for the same URI.
/// If not found, a new subdirectory is attempted to be created at the working directory.
/// Whichever succeeds first is set as the data directory for the session.
///
bool find_or_create_data(std::string exe_path, std::string_view data_dir_uri);

///
/// \brief Obtain the path to the executable.
///
std::string_view exe_path();
///
/// \brief Obtain the path to the data directory.
///
std::string_view data_dir();

///
/// \brief Obtain the full data path of the passed URI.
/// \param uri URI to resolve.
///
std::string data_path(std::string_view uri);
} // namespace whackx::io
