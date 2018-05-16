#include "stdafx.h"
#include "CHttpUrl.h"
#include <algorithm>
#include <iostream>

namespace
{
static std::map<std::string, Protocol> ProtocolMap({ { "http", Protocol::HTTP }, { "https", Protocol::HTTPS } });
}

CHttpUrl::CHttpUrl(const std::string& url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
	:m_domain(domain)
	,m_document(document)
	,m_protocol(protocol)
	,m_port(port)
{
	ValidateDomain(m_domain);
}

std::string CHttpUrl::GetURL() const
{
	auto url = ToStringProtocol() + "://" + m_domain;

	if ((m_port != 80) || (m_port != 443))
	{
		url += ":" + std::to_string(m_port);
	}

	url += m_document;
	return url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	m_protocol = ParseProtocol(url);
	auto urlStr = url.substr(ToStringProtocol().size() + 3, url.size() - 1);

	m_domain = ParseDomain(urlStr);
	urlStr = urlStr.substr(m_domain.size(), urlStr.size() - 1);

	m_port = ParsePort(urlStr);
	if (urlStr[0] == ':')
	{
		urlStr = urlStr.substr(std::to_string(m_port).size() +1, urlStr.size());
	}
	m_document = ParseDocument(urlStr);
}

Protocol CHttpUrl::ParseProtocol(const std::string& url)
{
	auto endPos = url.find("://");

	if (endPos == std::string::npos)
	{
		throw CUrlParsingError("Error: Invalid url protocol");
	}

	auto protocol = url.substr(0, endPos);
	if (!ValidateProtocol(protocol))
	{
		throw CUrlParsingError("Error: Invalid type protocol");
	}

	return ProtocolMap.find(protocol)->second;
}

std::string CHttpUrl::ParseDomain(const std::string& url)
{
	auto endPos = url.find(':');
	if (endPos == std::string::npos)
	{
		endPos = url.find('/');
	}

	if (endPos == std::string::npos)
	{
		throw CUrlParsingError("Error: Invalid url domain");
	}

	auto domain = url.substr(0, endPos);
	if (!ValidateDomain(domain))
	{
		throw CUrlParsingError("Error: Invalid syntax domain");
	}

	return domain;
}

unsigned short CHttpUrl::ParsePort(const std::string& url)
{
	if (url[0] != ':')
	{
		return static_cast<unsigned short>(m_protocol);
	}

	auto endPos = url.find('/');
	if (endPos == std::string::npos)
	{
		throw CUrlParsingError("Invalid syntax url.");
	}
	auto portStr = url.substr(1, endPos);
	int port = std::stoi(portStr);
	if (port < 1 || port > 65535 || portStr.find(' ') != std::string::npos)
	{
		throw CUrlParsingError("Port parsing error.");
	}

	return static_cast<unsigned short>(port);
}

std::string CHttpUrl::ParseDocument(const std::string& url)
{
	auto document = url;
	
	auto endPos = url.find('?');
	if (endPos != std::string::npos)
	{
		document = document.substr(0, endPos);
	}

	auto spacePos = url.find(' ');
	if (spacePos != std::string::npos)
	{
		throw CUrlParsingError("Invalid syntax document");
	}
	return document;
}

bool CHttpUrl::ValidateProtocol(const std::string& protocol)
{
	return ProtocolMap.find(protocol) != ProtocolMap.end();
}

bool CHttpUrl::ValidateDomain(const std::string& domain)
{
	if (domain.empty())
	{
		return false;
	}

	auto slash = std::find(domain.begin(), domain.end(), '/');
	auto space = std::find(domain.begin(), domain.end(), ' ');
	auto ReserseSlash= std::find(domain.begin(), domain.end(), ' ');
	if (slash != domain.end() || space != domain.end() || ReserseSlash != domain.end())
	{
		return false;
	}
	return true;
}

std::string CHttpUrl::ToStringProtocol()const
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return "http";

	case Protocol::HTTPS:
		return "https";
	}

	return std::string();
}
