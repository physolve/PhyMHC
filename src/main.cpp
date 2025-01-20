#include "phymhc.h"

// #include <windows.h>
// #include "lib/USBIO_CSWrapper.h"
// #pragma comment(lib, "ICPDAS_USBIO.lib")

int main(int argc, char *argv[]) {
    QCoreApplication::setApplicationName("GRAMs");
    QCoreApplication::setApplicationVersion("1.0.0");
    QCoreApplication::setOrganizationName(QStringLiteral("Tomsk Polytechnic University"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("tpu.ru"));
    // qputenv("QT_FONT_DPI", QByteArray("96")); //96/128 set for High DPI screen

    PhyMHC app(argc, argv);
    int ret;
    try{
        ret = app.exec(); 
    } catch (const std::bad_alloc &){
        // cleaning, saving session
        // close config files
        return EXIT_FAILURE;
    }
    
    return ret;
}

