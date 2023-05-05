//a. " "
//b. Automatic memory allocation and simpler code.

#include "HALmod.h"

int main()
{
  string tokens[MAX_COMMAND_LINE_ARGUMENTS];
  int tokenCount;

  do
  {
    tokenCount = getCommand(tokens);
    char ** cTokens = convertToC (tokens, tokenCount);
    printReverse (cTokens, tokenCount);
    cleanUpCArray (cTokens, tokenCount);
  } while (processCommand(tokens, tokenCount));

  return 0;
}
