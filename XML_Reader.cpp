#include "XML_Reader.h"
#include <libxml/parser.h>
#include <vector>
#include <QGuiApplication>
#include <string>
XML_Reader::XML_Reader() = default;
void XML_Reader::XML_Data_Finder(const char *data){
    // Leer el archivo XML
    xmlDocPtr doc = xmlReadFile(data, NULL, 0);

    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr node = root->children;
    std::string data_str;
    while (node != NULL) {
        if (xmlStrcmp(node->name, (const xmlChar *)"value") == 0) {
            xmlChar* content = xmlNodeGetContent(node);
            data_str = std::string((char*)content);
            xmlFree(content);
            break;
        }
        node = node->next;
    }
    int data2 = std::stoi(data_str);
    newest_data = data2;

    xmlFreeDoc(doc);
}
int XML_Reader::Data_Changer(const char *data, const char *value){
    xmlDocPtr doc = xmlReadFile(data, NULL, 0);
    if (doc == NULL) {

        return -1;
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr node = root->children;
    while (node != NULL) {
        if (xmlStrcmp(node->name, (const xmlChar *)"value") == 0) {
            xmlNodeSetContent(node, (const xmlChar *)value);
            break;
        }
        node = node->next;
    }
    int saved = xmlSaveFormatFileEnc(data, doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    return 0;
}