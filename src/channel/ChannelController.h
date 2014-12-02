#ifndef CHANNELCONTROLLER_H_
#define CHANNELCONTROLLER_H_

#include <map>
#include <string>

#include "AChannel.h"


/* TODO: loger */
class ChannelController {

  std::map<std::string, AChannel*> _map;

public:
  ChannelController() : _map() {}

  void add(AChannel& channel) {
    if (_map.find(channel.getName()) != _map.end()) {
      _map[channel.getName()] = &channel;
    } else {
      // TODO: throw custom exception
    }
  }

  // throw std::out_of_range
  void remove(std::string const& chanName) {
    delete _map.at(chanName);
    _map.erase(chanName);
  }

  void write(std::string const& chanName, bool value) {
    _map.at(chanName)->write(value);
  }

  bool read(std::string const& chanName) const {
    return _map.at(chanName)->read();
  }

  void sync(std::string const& chanName) {
    _map.at(chanName)->sync();
  }

  void writeAll(bool value) {
    for (auto& pair : _map) {
      pair.second->write(value);
    }
  }

  void syncAll() {
    for (auto& pair : _map) {
      pair.second->sync();
    }
  }

  std::map<std::string, bool>& readAll() const {
    auto& resMap = *new std::map<std::string, bool>;
    for (auto& pair : _map) {
      resMap[pair.first] = pair.second->read();
    }
    return resMap;
  }
};

#endif // !CHANNELCONTROLLER_H_