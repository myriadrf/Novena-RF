/**
@file   MessageLog.cpp
@author Lime Microsystems (www.limemicro.com)
@brief  Global message and event logging
*/

#include "MessageLog.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
using namespace std;

const char g_sesionLogFilename[] = "LMS_SessionLog.txt";
const unsigned int g_logMessageLimit = 100;
MessageLog* MessageLog::m_pInstance = NULL;

/** @brief Handles incoming messages
    @param msg message about event
*/
void MessageLog::HandleMessage(const LMS_Message &msg)
{
}

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
    @param type message type: info, warning, error...
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
    {
        fstream fileout;
        fileout.open(g_sesionLogFilename, ios::out | ios::app);
        fileout << ss.str();
        fileout.close();
        if(m_messages.size() > g_logMessageLimit)
            m_messages.pop_front();
        m_messages.push_back(ss.str());
        Notify(LMS_Message(MSG_INFO, ss.str().c_str(), 0, 0));
    }
    else
        return;
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
    for(list<string>::iterator iter = m_messages.begin(); iter!=m_messages.end(); ++iter)
        fout << *iter;
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
MessageLog::MessageLog() : m_printToConsole(false), m_enableLogging(true)
{
    //create or clear session log file
    fstream fileout;
    fileout.open(g_sesionLogFilename, ios::out);
    fileout.close();

    m_logFilter = LOG_INFO | LOG_WARNING | LOG_ERROR;
    m_consoleFilter = LOG_INFO | LOG_WARNING | LOG_ERROR;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"Log started: %Y-%m-%d %H:%M:%S\n",timeinfo);
    write(buffer, LOG_INFO);
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
list<string> MessageLog::getLogMessages() const
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
