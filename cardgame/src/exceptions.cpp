#include "exceptions.h"

const char *JogadaInvalidaException::what() const noexcept
{
    return "Jogada Invalida!";
}

const char *AcaoInvalidaException::what() const noexcept
{
    return "Nao eh possivel executar esta acao!";
}
 
const char *ErroExecucaoException::what() const noexcept
{
    return "Erro durante execucao do programa!";
}
