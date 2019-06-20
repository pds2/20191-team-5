#pragma once

#include <stdexcept>

class JogadaInvalidaException : public std::exception
{
    virtual const char *what() const noexcept override;
};

class AcaoInvalidaException : public std::exception
{
    virtual const char *what() const noexcept override;
};

class ErroExecucaoException : public std::exception
{
    virtual const char *what() const noexcept override;
}