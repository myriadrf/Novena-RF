#ifndef LMS_MESSAGE_LOG_H
#define LMS_MESSAGE_LOG_H

#include <string>
#include <vector>
using namespace std;

/// @brief Message types used for logging
enum eMessageType
{
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 4,
    LOG_DATA = 8
};

/** @class MessageLog
    @brief Singleton class used for logging messages
*/

class MessageLog
{
public:
    static MessageLog* getInstance();
    ~MessageLog();

    void SetLogFilter(unsigned int messageTypes);
    unsigned int GetLogFilter() const;
    void SetConsoleFilter(unsigned int messageTypes, bool printToConsole = true);
    unsigned int GetConsoleFilter() const;

    void write(const string msg, const eMessageType type = LOG_INFO);
    void saveToFile(const string filename);
    void clear();
    vector<string> getLogMessages() const;

    void enableLogging(bool enabled);
    void registerForNotifications( void (*callback)(const int signal, const char *msg, const int param));
    void unregisterFromNotifications( void (*callback)(const int signal, const char *msg, const int param));

protected:
    static MessageLog *m_pInstance;
    MessageLog();
    MessageLog(MessageLog const&);     // Don't Implement
    void operator=(MessageLog const&); // Don't implement
    vector<string> m_messages; ///log saved messages

    vector< void (*)(const int, const char*, const int) > m_callbacks; ///callback functions that will be notified upon message receive

    unsigned int m_logFilter; ///filter which type messages to save
    unsigned int m_consoleFilter; ///filter which type messages to print to console

    bool m_printToConsole; ///enables message printing to console
    bool m_enableLogging; ///enables saving of logged messages
};


#endif // LMS_MESSAGE_LOG_H

