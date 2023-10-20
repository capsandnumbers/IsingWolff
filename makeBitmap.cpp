#include <iostream>
#include <fstream>
#include <vector>

#pragma pack(push, 1)

struct BMPHeader {
    char signature[2] = {'B', 'M'};
    uint32_t fileSize;      // Size of the BMP file
    uint16_t reserved1 = 0; // Reserved
    uint16_t reserved2 = 0; // Reserved
    uint32_t dataOffset;    // Offset to the start of image data
    uint32_t headerSize = 40; // Size of the header
    int32_t width;          // Width of the image
    int32_t height;         // Height of the image
    uint16_t planes = 1;
    uint16_t bitsPerPixel = 1; // 1-bit BMP
    uint32_t compression = 0;
    uint32_t dataSize = 0;
    int32_t horizontalResolution = 2835; // Pixels per meter (2835 ppm = 72 dpi)
    int32_t verticalResolution = 2835;   // Pixels per meter (2835 ppm = 72 dpi)
    uint32_t colors = 0;
    uint32_t importantColors = 0;
};

#pragma pack(pop)

void createBMP(const std::vector<std::vector<int>>& image, const std::string& filename) {
    BMPHeader header;
    int width = image[0].size();
    int height = image.size();

    header.width = width;
    header.height = height;
    int rowWidth = (width + 31) / 32 * 4; // Each row should be a multiple of 4 bytes

    header.fileSize = sizeof(BMPHeader) + rowWidth * height;

    std::ofstream bmpFile(filename, std::ios::out | std::ios::binary);

    // Write the BMP header
    bmpFile.write(reinterpret_cast<char*>(&header), sizeof(header));

    // Write the pixel data (bottom-up)
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            uint8_t pixel = (image[y][x] == 1) ? 0xFF : 0x00; // White or Black
            bmpFile.write(reinterpret_cast<char*>(&pixel), 1);
        }

        // Add padding to make the row width a multiple of 4 bytes
        for (int padding = rowWidth - width; padding > 0; --padding) {
            uint8_t paddingByte = 0x00;
            bmpFile.write(reinterpret_cast<char*>(&paddingByte), 1);
        }
    }

    bmpFile.close();
}

int main() {
    // Replace this with your 10x10 array data (each entry is +1 or -1)
    std::vector<std::vector<int>> image = {
        {1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
        {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
        {1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
        {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
        {1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
        {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
        {1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
        {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1},
        {1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
        {-1, 1, -1, 1, -1, 1, -1, 1, -1, 1}
    };

    createBMP(image, "output.bmp");

    std::cout << "BMP file created successfully." << std::endl;
    return 0;
}
