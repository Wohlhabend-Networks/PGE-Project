#ifndef PGENETLL_SERVER_H
#define PGENETLL_SERVER_H

#include <asio.hpp>
#include <functional>

#include <ConnectionLib/Shared/util/ThreadedQueue.h>

using asio::ip::tcp;

class PGENETLL_Server
{
public:
    PGENETLL_Server(asio::io_service& io_service, short port);

    void startAccepting();



    void setIncomingTextFunc(const std::function<void (std::string)> &incomingTextFunc);
    void setPacketToPush(const std::shared_ptr<ThreadedQueue<std::string> > &packetToPush);

private:
    // Will be forwarded to the session:
    std::function<void(std::string)> m_incomingTextFunc;
    std::shared_ptr<ThreadedQueue<std::string> > m_packetToPush;

    tcp::acceptor m_pgenetll_acceptor;
    tcp::socket m_pgenetll_nextsocket;
};

#endif // PGENETLL_SERVER_H
