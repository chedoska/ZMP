#include "ComChannel.hh"
#include <iostream>

void ComChannel::Init(int Socket)
{
    Socket4Sending = Socket;
}

int ComChannel::GetSocket() const
{
    return Socket4Sending;
}

void ComChannel::LockAccess()
{
  m_mutex.lock();
}

void ComChannel::UnlockAccess()
{
  m_mutex.unlock();
}

std::mutex& ComChannel::UseGuard()
{
  return m_mutex;
}

ComChannel::~ComChannel()
{
  close(Socket4Sending);
}

bool ComChannel::OpenConnection()
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  Socket4Sending = socket(AF_INET,SOCK_STREAM,0);

  if (Socket4Sending < 0) {
     std::cerr << "*** Blad otwarcia gniazda." << std::endl;
     return false;
  }

  if (connect(Socket4Sending,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
     return false;
   }
  return true;
}

int ComChannel::Send(const char *sMesg)
{
  if (Socket4Sending < 0) {
     std::cerr << "*** Gniazdo zostało zamknięte - Blad wysylania." << std::endl;
     return false;
  }

  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Socket4Sending,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    std::cerr << "*** Blad przeslania napisu." << std::endl;
  }
  return 0;
}

void ComChannel::CloseConnection()
{
  Send("Close\n");
}