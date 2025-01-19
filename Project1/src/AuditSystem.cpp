// AuditSystem.cpp, created by Hannah Nelson
// A system that produces an audit file of the election. As lines get input
// to the writeLine funciton, they get ouputted to an audit file.

#include "AuditSystem.h"
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

AuditSystem::AuditSystem(string& filePath) {
    stringstream updateFilePath;

    updateFilePath << filePath.substr(0, -5) << "Audit.txt";
    string auditPath = updateFilePath.str();
    const char* pathing = auditPath.c_str();
    fp = fopen(pathing, "w");
}

void AuditSystem::writeLine(string addition) {
    const char* c = addition.c_str();
    fputs(c, fp);
}

void AuditSystem::closeAudit() {
   fclose(fp);
}

AuditSystem::~AuditSystem() {}

AuditSystem::AuditSystem() {}