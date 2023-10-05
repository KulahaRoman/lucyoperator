#include "servercredentials.h"

ServerCredentials::ServerCredentials() {}

ServerCredentials::ServerCredentials(const std::string& address,
                                     unsigned short port)
    : address(address), port(port) {}

std::string ServerCredentials::GetAddress() const { return address; }

void ServerCredentials::SetAddress(const std::string& address) {
  this->address = address;
}

unsigned short ServerCredentials::GetPort() const { return port; }

void ServerCredentials::SetPort(unsigned short port) { this->port = port; }
