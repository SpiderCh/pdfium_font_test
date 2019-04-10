#include <vector>
#include <functional>

#include <fstream>
#include <iostream>

#include <public/fpdfview.h>
#include <public/fpdf_edit.h>
#include <public/fpdf_text.h>
#include <public/cpp/fpdf_scopers.h>

namespace
{

class PDFiumScopeInit
{
public:
	PDFiumScopeInit()
	{
		FPDF_LIBRARY_CONFIG config;
		config.version = 2;
		config.m_pUserFontPaths = nullptr;
		config.m_pIsolate = nullptr;
		config.m_v8EmbedderSlot = 0;

		FPDF_InitLibraryWithConfig(&config);
		unsigned long error = FPDF_GetLastError();
		assert(error == 0);
	}

	~PDFiumScopeInit()
	{
		FPDF_DestroyLibrary();
	}
};
}

int main(int argc, char** argv)
{
	if (argc < 2)
		return 0;

	const PDFiumScopeInit init_pdfium;

	const std::string document_path(argv[1]);
	ScopedFPDFDocument document(FPDF_LoadDocument(document_path.data(), nullptr));
	if (!document)
	{
		unsigned long err = FPDF_GetLastError();
		std::cout << "Cannot open document: "<< err << std::endl;
		return 1;
	}

	const int page_size = FPDF_GetPageCount(document.get());

	for (int i = 0; i < page_size; ++i)
	{
		std::cout << __PRETTY_FUNCTION__ << " Page: " << i << std::endl;
		ScopedFPDFPage page(FPDF_LoadPage(document.get(), i));
		if(!page)
		{
			std::cout << __PRETTY_FUNCTION__ << " cannot open page by index 0" << std::endl;
			continue;
		}

		const int objectsSize = FPDFPage_CountObjects(page.get());
		std::cout << __PRETTY_FUNCTION__ << " counted objects: " << objectsSize << std::endl;

		ScopedFPDFTextPage text_page(FPDFText_LoadPage(page.get()));

		constexpr int font_name_size {1024};
		const int total_chars = FPDFText_CountChars(text_page.get());
		for(int i = 0; i < total_chars; ++i)
		{
			int flags = 0;
			char font_name[font_name_size] = "\0";
			const unsigned int res = FPDFText_GetFontInfo(text_page.get(), i, font_name, font_name_size, &flags);
			std::cout << __PRETTY_FUNCTION__ << " symbol index: " << i << "; font size: " << res << "; font name: " << font_name << "; flags: " << flags << std::endl;
		}
	}

	return 0;
}
