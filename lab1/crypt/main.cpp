#include "stdafx.h"
#include "crypt.h"

const std::string CRYPT_ACTION = "crypt";
const std::string DECRYPT_ACTION = "decrypt";

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Error: invalid arguments count" << std::endl;
		std::cout << "Usage: crypt.exe crypt <input file> <output file> <key> " << std::endl;
		std::cout << "Usage: crypt.exe decrypt <input file> <output file> <key> " << std::endl;
		return 1;
	}

	const std::string action = argv[1];

	if (action.empty() || (action != CRYPT_ACTION && action != DECRYPT_ACTION))
	{
		std::cout << "Error: invalid action" << std::endl;
		std::cout << "Usage: crypt OR decrypt" << std::endl;
		return 1;
	}
	const char* key = argv[4];

	char *lastCharPtr;
	int inputDigit = std::strtol(key, &lastCharPtr, 10);

	if ((inputDigit < 0 || inputDigit > 255) || *lastCharPtr == *key)
	{
		std::cout << "Error: invalid digit" << std::endl;
		std::cout << "Usage: 0 .. 255" << std::endl;
		return 1;
	}

	auto byteKey = static_cast<uint8_t>(inputDigit);

	unsigned exitCode = 0;
	if (action == CRYPT_ACTION)
	{
		exitCode = Crypt(argv[2], argv[3], GetCryptFunction(byteKey));
	}
	else
	{
		exitCode = Crypt(argv[2], argv[3], GetDecryptFunction(byteKey));
	}
    return exitCode;
}
