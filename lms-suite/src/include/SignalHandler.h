/**
@file   SignalHandler.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for handling message passing between modules
*/

#ifndef LMS_SIGNAL_HANDLER
#define LMS_SIGNAL_HANDLER

#include <vector>
#include <string>
class SignalHandler;

/// Available message types
enum LMS_MessageType
{
    MSG_UNDEFINED,
	MSG_BOARD_CONNECTED,
	MSG_BOARD_DISCONNECTED,
	MSG_BOARD_RESET,
	MSG_REGISTER_TEST,
	MSG_CHANNEL_CHANGED,
	MSG_REGISTER_VALUE_SET,
	MSG_PROGRAMMING_PACKET_SENT,
	MSG_PROGRAMMING_COMPLETED,
	MSG_ERROR,
	MSG_WARNING,
	MSG_INFO
};

/** @brief Message packet
    param1 and param2 are general purpose variables, their usage depends from message type
*/
struct LMS_Message
{
    LMS_Message() : type(MSG_UNDEFINED), text("Empty"), param1(0), param2(0) {};
    LMS_Message(LMS_MessageType type, const std::string text, const int p1, const int p2) :
        type(type), text(text), param1(p1), param2(p2) {};
	LMS_MessageType type;
	std::string text;
	int param1;
	int param2;
};

class SignalHandler
{
public:
	SignalHandler();
	virtual ~SignalHandler();

	void RegisterForNotifications(SignalHandler *handler);
	void UnregisterFromNotifications(SignalHandler *handler);

	void Notify(const LMS_Message &msg);

	/// Method used to handle incoming messages
	virtual void HandleMessage(const LMS_Message &msg) = 0;
protected:
	std::vector< SignalHandler* > m_listeners;
};
#endif
