#include "MessageLog.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;

MessageLog* MessageLog::m_pInstance = NULL;

/** @brief Creates one instance of message log
    @return Message log
*/
MessageLog* MessageLog::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new MessageLog();
    }
    return m_pInstance;
}

/** @brief Destroys message log
*/
MessageLog::~MessageLog()
{
    if(m_pInstance != NULL)
        delete m_pInstance;
    m_pInstance = NULL;
}

/** @brief writes message to log
    @param msg message to write
*/
void MessageLog::write(const string msg, eMessageType type)
{
    if(!m_enableLogging)
        return;

    stringstream ss;

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    //add time stamp
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%H:%M:%S",timeinfo);
    ss << "[" << buffer << "] ";

    //add prefix by message type
    switch(type)
    {
    case LOG_INFO:

        break;
    case LOG_WARNING:
        ss << "WARNING: ";
        break;
    case LOG_ERROR:
        ss << "ERROR: ";
        break;
    case LOG_DATA:
        ss << "DATA: ";
        break;
    default:
        ss << "UNDEFIEND TYPE: ";
        break;
    }

    ss << msg;
    if(type & m_logFilter)
        m_messages.push_back(ss.str());
    else
        return;

    //notify about message receive
    for(unsigned int i=0; i<m_callbacks.size(); ++i)
    {
        if( m_callbacks[i])
            m_callbacks[i](1, ss.str().c_str(), 0);
    }

    if(m_printToConsole)
    {
        if( type & m_consoleFilter )
            cout << ss.str();
    }
}

/** @brief Saves log messages to text file
    @param filename file to create
*/
void MessageLog::saveToFile(const string filename)
{
    fstream fout;
    fout.open(filename.c_str(), ios::out);
    for(unsigned int i=0; i<m_messages.size(); ++i)
        fout << m_messages[i];
    fout.close();
}

/** @brief clears all messages
*/
void MessageLog::clear()
{
    m_messages.clear();
}

/** @brief Creates message log, initializes filters.
*/
MessageLog::MessageLog() : m_printToConsole(false), m_enableLogging(false)
{
    m_logFilter = LOG_INFO | LOG_WARNING | LOG_ERROR | LOG_DATA;
    m_consoleFilter = LOG_INFO | LOG_WARNING | LOG_ERROR | LOG_DATA;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"Log started: %Y-%m-%d %H:%M:%S\n",timeinfo);
    write(buffer, LOG_INFO);
}

/** @brief register function to be notified when new messages have been logged.
    @param callback pointer to static function
    @param msg logged message
    @param param reserved additional parameter
*/
void MessageLog::registerForNotifications( void (*callback)(const int signal, const char *msg, const int paraml))
{
    if(callback != NULL)
        m_callbacks.push_back(callback);
}

/** @brief unregister function from notification list
    @param callback pointer to static function
    @param msg logged message
    @param param reserved additional parameter
*/
void MessageLog::unregisterFromNotifications( void (*callback)(const int singal, const char *msg, const int param))
{
    for(unsigned int i=0; i<m_callbacks.size(); ++i)
    {
        if(m_callbacks[i] == callback)
        {
            m_callbacks.erase(m_callbacks.begin()+i);
            break;
        }
    }
}

/** @brief Sets which messages should be logged
    @param messageTypes messages to be logged
*/
void MessageLog::SetLogFilter(unsigned int messageTypes)
{
    m_logFilter = messageTypes;
}

/** @brief Sets which messages should be printed to console
    @param messagesTypes messages types to be printed
    @param printToConsole enable printing to console
*/
void MessageLog::SetConsoleFilter(unsigned int messageTypes, bool printToConsole)
{
    m_consoleFilter = messageTypes;
    m_printToConsole = printToConsole;
}

/** @brief Returns all log messages
    @return vector of log messages
*/
vector<string> MessageLog::getLogMessages() const
{
    return m_messages;
}

/** @brief returns printing to console filter
*/
unsigned int MessageLog::GetConsoleFilter() const
{
    return m_consoleFilter;
}

/** @brief returns log filter
*/
unsigned int MessageLog::GetLogFilter() const
{
    return m_logFilter;
}

/** @brief Enables or disables message logging
    @param enabled message logging enabled
*/
void MessageLog::enableLogging(bool enabled)
{
    m_enableLogging = enabled;
}
