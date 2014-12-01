/* 
 * File:   ChannelGroup.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 20:40
 */

#ifndef CHANNELGROUP_H
#define	CHANNELGROUP_H

#include <list>
#include <memory>
#include <algorithm>
#include <functional>

#include "IWritable.h"
#include "AChannel.h"

class ChannelGroup : public IWritable {
public:
  typedef std::shared_ptr<AChannel> SharedChannel;

private:
  std::string m_name;
  std::list<SharedChannel> m_channels;

public:
  ChannelGroup(std::string const& name) :
    m_name(name), m_channels()
  {}

  ChannelGroup(std::string const& name,
    std::list<SharedChannel> const& channels) :
    m_name(name), m_channels(channels)
  {}

  ChannelGroup(const ChannelGroup& orig) :
    m_name(orig.m_name), m_channels(orig.m_channels)
  {}

  virtual ~ChannelGroup() {}

  void add(SharedChannel const& channel) {
    m_channels.push_back(channel);
  }

  void remove(std::string const& name) {
    m_channels.remove_if(
      [name](SharedChannel const& sh_ptr) {
        return sh_ptr.get()->getName() == name;
    });
  }

  void removeIf(
    std::function<bool (SharedChannel const&)> pred)
  {
    m_channels.remove_if(pred);
  }

  void forEach(
    std::function<void (SharedChannel const&)> func) const
  {
    std::for_each(m_channels.begin(), m_channels.end(), func);
  }

  // Maybe useful ?
  // void sync() {
  //   forEach([](SharedChannel const& sh_ptr) {
  //     sh_ptr.get()->sync();
  //   });
  // }

  virtual void write(bool value) {
    forEach([value](SharedChannel const& sh_ptr) {
      sh_ptr.get()->write(value);
    });
  }
};

#endif	/* CHANNELGROUP_H */

