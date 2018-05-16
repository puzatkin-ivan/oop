#include "stdafx.h"
#include "../HTTP_URL/CHttpUrl.h"

BOOST_AUTO_TEST_SUITE(CHttpURL)
	BOOST_AUTO_TEST_CASE(initialization)
	{
		BOOST_CHECK_THROW(CHttpUrl("www.google.net", "/search/image.png", Protocol::HTTPS, 15), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("ws://domain.net/document"), CUrlParsingError);
		BOOST_CHECK_THROW(CHttpUrl("http://domain.net/docum ent"), CUrlParsingError);
	}
	BOOST_AUTO_TEST_SUITE(parse_url)
		BOOST_AUTO_TEST_CASE(parse_protocol)
		{
			BOOST_CHECK_THROW(CHttpUrl("nohttp://domain.net/document"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("ters://domain.net/document"), CUrlParsingError);
			CHttpUrl httpUrl("http://domain.net/document");
			BOOST_CHECK(httpUrl.GetProtocol() == Protocol::HTTP);
			CHttpUrl httpsUrl("https://domain.net/document");
			BOOST_CHECK(httpsUrl.GetProtocol() == Protocol::HTTPS);
		}
		BOOST_AUTO_TEST_CASE(parse_domain)
		{
			BOOST_CHECK_THROW(CHttpUrl("http://"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("http://domainn odomain.net/document"), CUrlParsingError);

			CHttpUrl httpsUrl("https://google.com/");
			BOOST_CHECK(httpsUrl.GetDomain() == "google.com");
		}
		BOOST_AUTO_TEST_CASE(parse_port)
		{
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net: "), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net:0/"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net:-8/"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net:65536"), CUrlParsingError);

			CHttpUrl httpsUrl("https://google.com/");
			BOOST_CHECK((int)httpsUrl.GetPort() == 443);

			CHttpUrl httpUrl("http://google.com/");
			BOOST_CHECK((int)httpUrl.GetPort() == 80);

			CHttpUrl url("https://google.com:3008/");
			BOOST_CHECK((int)url.GetPort() == 3008);
		}
		BOOST_AUTO_TEST_CASE(parse_document)
		{
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net/assd asd/sada /"), CUrlParsingError);
			BOOST_CHECK_THROW(CHttpUrl("https://domain.net/as sdasd?asdasd=asdas"), CUrlParsingError);

			CHttpUrl url("https://google.com:3008/index.php");
			BOOST_CHECK(url.GetDocument() == "/index.php");

			CHttpUrl httpUrl("https://google.com/search/dictonary.php");
			BOOST_CHECK(httpUrl.GetDocument() == "/search/dictonary.php");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
