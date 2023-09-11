#include <stb.h>
#include <iostream>
int main() {
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("tank.png", &widthImg, &heightImg, &numColCh, 0);
	std::cout << bytes <<std::endl;
	size_t dataSize = widthImg * heightImg * numColCh;
	// Access and print the pixel data
	for (size_t i = 0; i < dataSize; i++) {
		unsigned char pixelValue = bytes[i];
		printf("%u ", pixelValue); // Print the pixel value
	}
	std::cout << "hello" << std::endl;
	stbi_image_free(bytes);
	return 0;
}