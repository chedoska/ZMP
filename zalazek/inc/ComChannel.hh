#ifndef COMCHANNEL_HH
#define COMCHANNEL_HH

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

#include "AbstractComChannel.hh"

#define PORT  6217

class ComChannel : public AbstractComChannel
{
public:
    bool OpenConnection();
    int Send(const char *sMesg);

    virtual void Init(int Socket);
    virtual int GetSocket() const;
    virtual void LockAccess();
    virtual void UnlockAccess();
    std::mutex &UseGuard();
    virtual ~ComChannel();

private:
    int Socket4Sending;
};

#endif