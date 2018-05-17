#pragma once

#include <map>
#include <string>
#include <vector>

#include "CUrlParsingError.h"

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
};

class CHttpUrl
{
public:
	CHttpUrl(const std::string& url);
	CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP, unsigned short port = 80);
	
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	void ParseUrl(const std::string& url);
	Protocol ParseProtocol(const std::string& url);
	std::string ParseDomain(const std::string& url);
	unsigned short ParsePort(const std::string& url);
	std::string ParseDocument(const std::string& url);

	static bool ValidateProtocol(const std::string& protocol);
	static bool ValidateDomain(const std::string& domain);
	static bool ValidatePort(int port);
	static bool ValidateDocument(const std::string& document);

	std::string ToStringProtocol() const;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
