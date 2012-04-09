/***
 * @file factory.hpp
 * @author Jacky Alcine <jacky.alcine@thesii.org>
 * @author Adrian Borucki <adrian@thesii.org>
 *
 * @section lcns Licensing
 * This program is free software; you can redistribute it and/or
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
 *
 */

#ifndef WINTERMUTE_FACTORY_HPP_
#define WINTERMUTE_FACTORY_HPP_

#include <app/global.hpp>
#include <app/plugin.hpp>
#include <app/pluginhandle.hpp>

namespace Wintermute
{
namespace Plugins
{

struct FactoryPrivate;
/**
 * @brief Provides factory management of plug-ins.
 *
 * This static class manages anything and everything to do with plug-ins; from
 * loading, unloading, obtaining information and more about plugins. A lot of the
 * internal working dealing with plug-ins, however, are done within the AbstractPlugin
 * class itself. This merely manages the loaded plug-ins and executes prerequisties commands.
 *
 * @class Factory plugins.hpp "include/wintermute/plugins.hpp"
 * @see AbstractPlugin
 */
class WNTR_EXPORT Factory : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY (Factory)
    Q_DECLARE_PRIVATE (Factory)
    WINTER_SINGLETON (Factory)
    friend class AbstractPluginPrivate;

signals:
    /**
     * @brief Emitted when a plug-in has been successfully loaded into the system.
     * @fn pluginLoaded
     * @param p_uuid The UUID of the loaded plug-in.
     */
    void pluginLoaded (const QString& p_uuid) const;

    /**
     * @brief Emitted when a plug-in has been successfully unloaded from the system.
     * @fn pluginUnloaded
     * @param p_uuid The UUID of the unloaded plug-in.
     */
    void pluginUnloaded (const QString& p_uuid) const;

    /**
     * @brief Emitted when a plug-in experiences a sporadic crash.
     * @fn pluginCrashed
     * @param p_uuid The UUID of the faulty plug-in.
     */
    void pluginCrashed (const QString& p_uuid) const;

    /**
     * @brief Emitted when the factory's up and running.
     */
    void started() const;

    /**
     * @brief Emitted when the factory's down for the count.
     */
    void stopped() const;

public slots:

    /**
     * @brief Starts the plug-in system.
     * @fn Startup
     */
    static void startup();
    /**
     * @brief Stops the plug-in system.
     * @fn Shutdown
     */
    static void shutdown();

public:
    /**
     * @brief Loads a plug-in.
     * @fn loadPlugin
     * @param
     */
    static AbstractPlugin* loadPlugin (const QString& p_uuid);

    /**
     * @brief Unloads a plug-in from the system.
     * @fn unloadPlugin
     * @param
     */
    static void unloadPlugin (const QString& p_uuid);

    /**
     * @brief Returns a list of all currently plug-ins with meta-data information.
     * @fn loadedPlugins
     * @returns A QList of plug-ins that are currently loaded into the system.
     */
    static QStringList loadedPlugins();

    /**
     * @brief Obtains a list of all of the plug-ins that are installed and recognized by Wintermute.
     * @fn allPlugins
     * @return const QStringList
     */
    static QStringList allPlugins();

    static AbstractPlugin* currentPlugin();
    static QVariant attribute (const QString& p_uuid, const QString& p_attributePath);
    static void setAttribute (const QString& p_uuid, const QString& p_attributePath, const QVariant& p_attributeValue);
    static AbstractPlugin* obtainPlugin(const QString& p_uuid);

protected:
    /**
     * @brief Obtains the specification options (not the configuration used by the plug-in).
     * @param string The UUID of the plug-in in question.
     * @return A pointer to a QSettings object or NULL if the UUID doesn't refer to a plug-in.
     */
    static QSettings* getPluginSettings (const QString& p_uuid);

    /**
     * @brief
     * @param string The UUID of the plug-in in question.
     * @return True if the plug-in has been loaded successfully, false otherwise.
     */
    static bool loadBackendPlugin (const QString& p_uuid);

private:
    QScopedPointer<FactoryPrivate> d_ptr;

private slots:
    /**
     * @brief Loads the plug-in defined to be executed from the command-line.
     * @fn loadStandardPlugin
     */
    static void loadStandardPlugin();

    /**
     * @brief Unloads the plug-in defined to be executed from the command-line.
     * @fn unloadStandardPlugin
     */
    static void unloadStandardPlugin();

    /**
     * @brief Represents the notifying of a plug-in's loading into the plug-in pool.
     * @fn doPluginLoad
     * @param string The UUID of the plug-in.
     */
    static void doPluginLoad (const QString&);

    /**
     * @brief Represents the notifying of a plug-in's unloading from the plug-in pool.
     * @fn doPluginUnload
     * @param string The UUID of the plug-in.
     */
    static void doPluginUnload (const QString&);

    /**
     * @brief Represents the notifying of a plug-in's crash.
     * @fn doPluginCrash
     * @param string The UUID of the plug-in.
     */
    static void doPluginCrash (const QString&);
};

} // namespaces
}

#endif // _FACTORY_HPP_
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
