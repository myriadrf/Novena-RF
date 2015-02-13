// -----------------------------------------------------------------------------
// FILE: 		MessageLog.h
// DESCRIPTION: Header for MessageLog.cpp
// DATE:		2013-11-28
// AUTHOR(s):	Lime Microsystems
// REVISIONS:
// -----------------------------------------------------------------------------

#ifndef LMS_MESSAGE_LOG_H
#define LMS_MESSAGE_LOG_H

#include <string>
#include <list>
#include <vector>
#include "SignalHandler.h"

/// @brief Message types used for logging
enum eMessageType
{
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 4,
    LOG_DATA = 8,
    LOG_ALL = 0xFFFF
};

/** @class MessageLog
    @brief Singleton class used for logging messages
*/

class MessageLog : public SignalHandler
{
public:
    static MessageLog* getInstance();
    ~MessageLog();

    void SetLogFilter(unsigned int messageTypes);
    unsigned int GetLogFilter() const;
    void SetConsoleFilter(unsigned int messageTypes, bool printToConsole = true);
    unsigned int GetConsoleFilter() const;

    void write(const std::string msg, const eMessageType type = LOG_INFO);
    void saveToFile(const std::string filename);
    void clear();
    std::list<std::string> getLogMessages() const;

    void enableLogging(bool enabled);
    void HandleMessage(const LMS_Message &msg);

protected:
    static MessageLog *m_pInstance;
    MessageLog();
    MessageLog(MessageLog const&);     // Don't Implement
    void operator=(MessageLog const&); // Don't implement
    std::list<std::string> m_messages; ///log saved messages

    unsigned int m_logFilter; ///filter which type messages to save
    unsigned int m_consoleFilter; ///filter which type messages to print to console

    bool m_printToConsole; ///enables message printing to console
    bool m_enableLogging; ///enables saving of logged messages
};

#endif // LMS_MESSAGE_LOG_H

