#include "io_context.hh"
#include "socket.hh"

//#include "task.hh"
#include "task.hpp"

cppcoro::task<bool> inside_loop(Socket& socket)
{
    char buffer[42] = {0};
    ssize_t nbRecv = co_await socket.recv(buffer, sizeof buffer);
    ssize_t nbSend = 0;
    while (nbSend < nbRecv)
    {
        ssize_t res = co_await socket.send(buffer, sizeof buffer);
        if (res <= 0)
            co_return false;
        nbSend += res;
    }
    std::cout << "DONE (" << nbRecv << "):" << '\n';
    if (nbRecv <= 0)
        co_return false;
    printf("%s\n", buffer);
    co_return true;
}

cppcoro::task<> echo_socket(std::unique_ptr<Socket> socket)
{
    bool run = true;
    while (run)
    {
        std::cout << "BEGIN\n";
        run = co_await inside_loop(*socket);
        std::cout << "END\n";
    }
    
}

cppcoro::task<> accept(Socket& listen)
{
    while (true)
    {
        auto socket = co_await listen.accept();
        auto t = echo_socket(std::move(socket));
        t.resume();
    }
}


int main()
{
    IOContext io_context{};
    Socket listen{"3490", io_context};
    auto t = accept(listen);
    t.resume();

    io_context.run();
}
