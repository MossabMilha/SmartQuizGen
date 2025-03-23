#ifndef PDFEXTRACTOR_H
#define PDFEXTRACTOR_H

#include <string>

class PdfExtractor {
public:
    PdfExtractor();
    ~PdfExtractor();


    std::string extractTextFromPdf(const std::string& pdfFilePath);

private:

};

#endif
