/**
 * @author Jacky Alcine <jackyalcine@gmail.com>
 * @legalese
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * @endlegalese
 */

#ifndef PLUGINS_HPP
#define PLUGINS_HPP
#include <QMap>
#include <QFile>
#include <QVector>
#include <QPluginLoader>
#include <QVariant>
#include <QStringList>
#include <wntr/config.hpp>

using namespace std;
using std::vector;
using std::map;

namespace Wintermute {
    namespace Plugins {
        struct Factory;
        struct PluginBase;

        /**
         * @brief Represents a named set of plugins.
         * @typedef PluginMap
         */
        typedef QMap<QString, PluginBase*> PluginList;

        /**
         * @brief Factory management of plugins.
         * This abstract class manages anything and everything to do with plugins; from
         * loading, unloading, obtaining information and more about plugins.
         * @class Factory plugins.hpp "include/wintermute/plugins.hpp"
         * @see Plugin
         */
        class Factory {
            friend class Plugin;
            public:
                /**
                 * @brief Starts the plug-in system.
                 * @fn Startup
                 */
                static void Startup();
                /**
                 * @brief Stops the plug-in system.
                 * @fn Shutdown
                 */
                static void Shutdown();
                /**
                 * @brief Loads a plugin.
                 * @fn loadPlugin
                 * @param
                 */
                static const PluginBase* loadPlugin ( const string& );
                /**
                 * @brief Loads a plugin.
                 * @fn loadPlugin
                 * @overload
                 * @param
                 */
                static const PluginBase* loadPlugin ( const QFile* );

                PluginList const & loadedPlugins() { return s_allPlgns; }
            private:
                static PluginList s_allPlgns;
        };

        /**
         * @brief Abstract class representing the outlining information of a plug-in.
         * @todo Implement a means of updating plug-ins as well.
         * @class Plugin plugins.hpp "include/wntr/plugins.hpp"
         */
        class PluginBase : public QObject {
            friend class Factory;
            Q_OBJECT
            Q_PROPERTY(const double Version READ version)
            Q_PROPERTY(const double CompatibleVersion READ compatVersion)
            Q_PROPERTY(const QString UUID READ uuid)
            Q_PROPERTY(const QString Name READ name)
            Q_PROPERTY(const QString Author READ author)
            Q_PROPERTY(const QString VendorName READ vendorName)
            Q_PROPERTY(const QString Description READ description)
            Q_PROPERTY(const QString WebPage READ webPage)
            Q_PROPERTY(const QString Dependencies READ dependencies)

            private:
                QPluginLoader* m_plgnLdr;

            public:
                explicit PluginBase() : QObject(NULL), m_plgnLdr(NULL) { }
                PluginBase(QPluginLoader* p_pl ) : QObject(p_pl), m_plgnLdr(p_pl) { }
                PluginBase(PluginBase const &p_pb) : QObject(p_pb.m_plgnLdr), m_plgnLdr(p_pb.m_plgnLdr){  }
                void operator= (PluginBase const &p_plgn) {
                    delete this->m_plgnLdr;
                    this->m_plgnLdr = p_plgn.m_plgnLdr;
                }
                virtual ~PluginBase() {
                    delete this->m_plgnLdr;
                }

                virtual const double version() const = 0;
                virtual const double compatVersion() const = 0;
                virtual const QString uuid() const = 0;
                virtual const QString name() const = 0;
                virtual const QString author() const = 0;
                virtual const QString vendorName() const = 0;
                virtual const QString description() const = 0;
                virtual const QString webPage() const = 0;
                virtual const QString dependencies() const = 0;
                virtual void initialize() = 0;
                virtual void deinitialize() = 0;
                virtual QObject* instance() = 0;

                const bool isSupported() const { return compatVersion() >= WINTERMUTE_VERSION; }
                const QString path() const { return QString::null; }
                //bool operator == (const PluginBase &p_1 ) { return p_1.m_plgnLdr == m_plgnLdr; }
        };

    }
}

Q_DECLARE_INTERFACE(Wintermute::Plugins::PluginBase, "thesii.Wntr.PluginBase");

#endif /* PLUGINS_HPP */
// kate: indent-mode cstyle; space-indent on; indent-width 4;
