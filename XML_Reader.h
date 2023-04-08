#ifndef XML_READER_H
#define XML_READER_H
#include <libxml/parser.h>

class XML_Reader {
public:
    XML_Reader();
    int newest_data;
    //void XML_Data_Finder();
    // Resto de métodos y variables
    void XML_Data_Finder(const char *data);
    int Data_Changer(const char *data, const char *value);

};

#endif // XML_READER_H

