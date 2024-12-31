#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>

namespace Compressor {

/**
     * @brief Compresses the input string using the LZW algorithm.
     *
     * This function takes an input string and compresses it using the LZW (Lempel-Ziv-Welch) algorithm.
     * The compressed output is returned as a single concatenated string of integer codes.
     *
     * @param input The original string to be compressed.
     * @return std::string The compressed string represented as concatenated integer codes.
     */
std::string compress(const std::string& input);

/**
     * @brief Decompresses the input string using the LZW algorithm.
     *
     * This function takes a compressed string (as generated by the compress function) and
     * decompresses it back to the original string using the LZW (Lempel-Ziv-Welch) algorithm.
     *
     * @param input The compressed string represented as concatenated integer codes.
     * @return std::string The decompressed original string.
     */
std::string decompress(const std::string& input);

} // namespace Compressor

#endif // COMPRESSOR_H