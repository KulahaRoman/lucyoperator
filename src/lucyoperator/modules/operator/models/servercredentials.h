#pragma once
#include <string>

class ServerCredentials {
 public:
  ServerCredentials();
  ServerCredentials(const std::string& address, unsigned short port);

  std::string GetAddress() const;
  void SetAddress(const std::string& address);

  unsigned short GetPort() const;
  void SetPort(unsigned short port);

 private:
  std::string address;
  unsigned short port;
};
