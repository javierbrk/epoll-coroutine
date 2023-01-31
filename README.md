# C++ coroutine with epoll

Use C++20 coroutine to have async accept / recv / send operation

Exemple echo server with in the main.cc

# My local improvements

The original project has a problem with socket liberation. 

This implementation fixes socket resource liberation and task destructor. 

The branch named cppcoro includes the original task by lewissbaker wich also correctly frees the resources. 

## Purpose

Learning coroutine.

Inspired by:
* https://github.com/lewissbaker/cppcoro

## TODO / Improvement

* catch sigint + destroy coroutine
* move semantic on socket accept (RVO ?)
* handling error
* clean (remove logging, ...)

