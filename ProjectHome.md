Libbarpp is a C++ library which gives you ability to generate and recognize fallowing bar codes:
  * Ean8
  * Ean13
  * Code25
  * Code39
  * Code93
  * Code128

Libbarpp was designed to be OOP portable library. Currently only Win32 platform is supported, but design of the library makes it easy to be ported to other operating systems. Portability of the library is provided by CBarBitmap class, currently implemented only by CBarBitmapWin32. Below the structure of classes is represented:
  * CBarNoise
  * CBarGenerator
    * CBarGeneratorEan8
    * CBarGeneratorEan13
    * CBarGeneratorCode25
    * CBarGeneratorCode39
    * CBarGeneratorCode93
    * CBarGeneratorCode128
  * CBarReader
    * CBarReaderEan8
    * CBarReaderEan13
    * CBarReaderCode25
    * CBarReaderCode39
    * CBarReaderCode93
    * CBarReaderCode128

Libbarpp also includes Barpp applications. Barpp is written in MFC with Ribbon interface and the point of the application is to give a preview of the functions provided by Libbarpp.
![http://libbarpp.googlecode.com/files/barpp_screenshot.png](http://libbarpp.googlecode.com/files/barpp_screenshot.png)

Please visit my personal website http://dominikcebula.pl/