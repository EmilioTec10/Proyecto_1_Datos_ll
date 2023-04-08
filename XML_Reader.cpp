#include "XML_Reader.h"
#include <libxml/parser.h>
#include <iostream>
#include <vector>
#include <QGuiApplication>
#include <string>

XML_Reader::XML_Reader() = default;
void XML_Reader::XML_Data_Finder(const char *data){
    // Leer el archivo XML
    xmlDocPtr doc = xmlReadFile(data, NULL, 0);
    if (doc == NULL) {
        std::cerr << "Error al leer el archivo XML" << std::endl;

    }

    // Obtener el nodo "edad" y su contenido como una cadena de caracteres
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

    // Convertir la cadena de caracteres a un entero
    int data2 = std::stoi(data_str);
    newest_data = data2;
    // Imprimir el valor de la edad
    std::cout << data2 << std::endl;

    // Liberar la memoria utilizada por el documento
    xmlFreeDoc(doc);


}
int XML_Reader::Data_Changer(const char *data, const char *value){

    // Leer el archivo XML
    xmlDocPtr doc = xmlReadFile(data, NULL, 0);
    if (doc == NULL) {
        std::cerr << "Error al leer el archivo XML" << std::endl;
        return -1;
    }

    // Obtener el nodo "edad" y cambiar su contenido
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr node = root->children;
    while (node != NULL) {
        if (xmlStrcmp(node->name, (const xmlChar *)"value") == 0) {
            xmlNodeSetContent(node, (const xmlChar *)value);
            break;
        }
        node = node->next;
    }

    // Guardar los cambios en el archivo XML
    int saved = xmlSaveFormatFileEnc(data, doc, "UTF-8", 1);
    if (saved == -1) {
        std::cerr << "Error al guardar los cambios en el archivo XML" << std::endl;
    }

    // Liberar la memoria utilizada por el documento
    xmlFreeDoc(doc);

    return 0;


}