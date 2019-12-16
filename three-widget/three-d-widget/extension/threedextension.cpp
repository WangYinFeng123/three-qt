#include "threedextension.h"
QSettings ThreeDExtension::settings("csnc","config");

ThreeDExtension::ThreeDExtension(void* metadata) : metadata(metadata) {}
ThreeDExtension::~ThreeDExtension() {}
void* ThreeDExtension::getMetadata() {return metadata;}

