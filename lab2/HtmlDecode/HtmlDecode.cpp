#include "stdafx.h"
#include <array>
#include "HtmlDecode.h"

using Map = std::array<std::pair<std::string, std::string>, 5>;

const Map HTML_ENTITIES = {{
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&amp;", "&" },
}};

std::string HtmlDecode(const std::string & htmlStr)
{
	std::string resultStr = htmlStr;
	
	for (auto& entity : HTML_ENTITIES)
	{
		resultStr = Replace(resultStr, entity.first, entity.second);
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
