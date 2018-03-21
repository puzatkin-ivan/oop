#include "stdafx.h"
#include "HtmlDecode.h"

using Map = std::vector<std::vector<std::string>>;

const Map HTML_ENTITIES{
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" },
	{ "&quot;", "\"" },
	{ "&apos;", "'" }
};

std::string HtmlDecode(const std::string & htmlStr)
{
	std::string resultStr = htmlStr;
	
	for (auto& entity : HTML_ENTITIES)
	{
		resultStr = Replace(resultStr, entity[0], entity[1]);
	}
	return resultStr;
}

std::string Replace(const std::string & inputStr, const std::string & searchStr, const std::string & replacementStr)
{
	if (searchStr.empty())
	{
		return inputStr;
	}
	std::string resultStr;
	size_t initSearchPos = 0;

	while (initSearchPos != std::string::npos)
	{
		auto foundPos = inputStr.find(searchStr, initSearchPos);
		resultStr.append(inputStr, initSearchPos, foundPos - initSearchPos);

		if (foundPos != std::string::npos)
		{
			resultStr.append(replacementStr);
			foundPos += searchStr.size();
		}
		initSearchPos = foundPos;
	}

	return resultStr;
}
