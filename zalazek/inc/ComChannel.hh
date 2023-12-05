#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

#include "AbstractComChannel.hh"

#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

#define PORT  6217

class ComChannel : public AbstractComChannel
{
public:
    bool OpenConnection();
    void CloseConnection();
    int Send(const char *sMesg);

    ComChannel() {}
    void Init(int Socket);
    int GetSocket() const;
    void LockAccess();
    void UnlockAccess();
    std::mutex &UseGuard();
    ~ComChannel();

private:
    int Socket4Sending;
    std::mutex m_mutex;
};

#endif