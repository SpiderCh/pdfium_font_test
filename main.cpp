#include <public/fpdfview.h>


int main(int, char**)
{
	FPDF_LIBRARY_CONFIG config;
	config.version = 2;
	config.m_pUserFontPaths = nullptr;
	config.m_pIsolate = nullptr;
	config.m_v8EmbedderSlot = 0;

	FPDF_InitLibraryWithConfig(&config);

	FPDF_DestroyLibrary();
	return 0;
}
