/**
 *
 * Copyright (C) 2013 Jacky Alcine <jacky.alcine@thesii.org>
 *
 * This file is part of Wintermute, the extensible AI platform.
 *
 *
 * Wintermute is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Wintermute is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Wintermute.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef WINTERMUTE_CORE_PLUGIN_HPP
#define WINTERMUTE_CORE_PLUGIN_HPP

#include <Wintermute/Globals>
#include <QtCore/QUuid>
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QList>
#include <QtCore/QMap>

namespace Wintermute {
  class Version;
  class PluginPrivate;

  /**
   * @class Wintermute::Plugin
   *
   * The Plugin object is meant as a way to manage the highest of plug-ins 
   * that can be mananged in the platform.
   *
   * @note The most direct means of handling plugins is recommended to be done 
   * through the Factory class.
   */
  class Plugin : public QObject {
    // {{{ QObject-ified.
    Q_OBJECT;
    Q_ENUMS(State);
    Q_PROPERTY(QString Name          READ name);
    Q_PROPERTY(Version Version       READ version);
    Q_PROPERTY(Version SystemVersion READ systemVersion);
    Q_PROPERTY(State   State         READ state);
    // }}} QObject-ified.

    // {{{ Private data.
    QScopedPointer<PluginPrivate> d_ptr;
    // }}} Private data.

    protected:
    Q_DECLARE_PRIVATE(Plugin);
    explicit Plugin(const QString& uuid);
    QSettings* configuration() const;

    public:

    virtual ~Plugin();
    
    /**
     * Flags used to represent the different states that a plug-in can exist 
     * in.
     */
    enum State {
      Undefined = 0x0,  // Reserved for a lack of a state (typically null) plugin.
      Loading   = 0x1,  // The plugin is currently undergoing the act of loading its prerequisties into Wintermute.
      Loaded    = 0x2,  // The plugin has been successfully loaded into Wintermute.
      Unloading = 0x3,  // The plugin is currently underdoing the work of removing itself from Wintermute.
      Unloaded  = 0x4,  // The plugin has been successfully removed from Wintermute.
      Crashed   = 0x5   // The plugin has encountered an undefined error.
    };

    /**
     * @fn isLoaded
     * Determines if the plugin has been loaded.
     */
    inline bool isLoaded() const { return state() == Loaded; }
    
    /**
     * @fn id
     * Obtains the UUID used as a unique identifer for the plugin.
     */
    QUuid id() const;

    /**
     * @fn name
     */
    QString name() const;
    Version version() const;
    Version systemVersion() const;
    State state() const;

    Q_SIGNAL void loaded();
    Q_SIGNAL void unloaded();

    Q_SLOT bool unload();
    Q_SLOT bool load();

    friend class Factory;
    friend class FactoryPrivate;
  };

  typedef QList<Plugin*> PluginList;
  typedef QMap<QUuid, Plugin*> PluginMap;
}

#endif /* WINTERMUTE_CORE_PLUGIN_HPP */
