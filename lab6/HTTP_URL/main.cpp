#include "stdafx.h"
#include "CHttpUrl.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::string url;
	while (std::getline(std::cin, url))
	{
		try
		{
			CHttpUrl httpUrl(url);

			auto protocol = httpUrl.GetProtocol();
			std::string type;
			if (httpUrl.GetProtocol() == Protocol::HTTP)
			{
				type = "HTTP";
			}
			else
			{
				type = "HTTPS";
			}
			std::cout << "URL: " << httpUrl.GetURL() << std::endl;
			std::cout << "Protocol: " << type << std::endl;
			std::cout << "Domain: " << httpUrl.GetDomain() << std::endl;
			std::cout << "Port: " << httpUrl.GetPort() << std::endl;
			std::cout << "Document: " << httpUrl.GetDocument() << std::endl;
		}
		catch (std::exception& error)
		{
			std::cout << error.what() << std::endl;
		}
	}
	return 0;
}
