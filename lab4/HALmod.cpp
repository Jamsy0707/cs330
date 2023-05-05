/*
  Part 1
  a. No. It only prints in the child fork if execvp doesn't work.
  b. The parent is the program that launched the executable. In this case, the makefile.
  c. Get rid of "wait" in the parent fork.

  Part 2
  The child and parent each have their own address space with their own copies of the
  variables. When child is called, duplicate variables are made so changing a variable
  in the child will not affect the parent.
*/

#include "HALmod.h"

int getCommand(string tokens[])
{
  string commandLine;
  bool commandEntered;
  int tokenCount;

  do
  {
    cout << "HALshell> ";
    while (1)
    {
      getline(cin, commandLine);
      commandEntered = checkForCommand();
      if (commandEntered)
      {
        break;
      }
    }
  } while (commandLine.length() == 0);

  tokenCount = tokenizeCommandLine(tokens, commandLine);

  return tokenCount;
}

int tokenizeCommandLine(string tokens[], string commandLine)
{
  char *token[MAX_COMMAND_LINE_ARGUMENTS];
  char *workCommandLine = new char[commandLine.length() + 1];
  int i;
  int tokenCount;

  for (i = 0; i < MAX_COMMAND_LINE_ARGUMENTS; i++)
  {
    tokens[i] = "";
  }
  strcpy(workCommandLine, commandLine.c_str());
  i = 0;
  if ((token[i] = strtok(workCommandLine, " ")) != NULL)
  {
    i++;
    while ((token[i] = strtok(NULL, " ")) != NULL)
    {
      i++;
    }
  }
  tokenCount = i;

  for (i = 0; i < tokenCount; i++)
  {
    tokens[i] = token[i];
  }

  delete[] workCommandLine;

  return tokenCount;
}

// Do not touch the below function
bool checkForCommand()
{
  if (cullProcess)
  {
    cullProcess = 0;
    cin.clear();
    cout << "\b\b  \b\b";
    return false;
  }

  return true;
}

// This is a very paired down version of Dr. Hilderman's function
int processCommand(string tokens[], int tokenCount)
{
  if (tokens[0] == "shutdown" || tokens[0] == "restart" || tokens[0] == "lo")
  {
    if (tokenCount > 1)
    {
      cout << "HALshell: " << tokens[0] << " does not require any arguments"
           << endl;
      return 1;
    }
    cout << endl;
    cout << "HALshell: terminating ..." << endl;

    return 0;
  }
  else
  {
    // step 2 of part 1
    int fork_return = fork();

    if (fork_return == 0)
    {
      char** conv_return = convertToC(tokens, tokenCount);
      execvp(conv_return[0], conv_return);
      cout << "Error on Execvp." << endl;
      exit(0);
    } 
    else if (fork_return > 0)
    {
      int status;
      wait(&status);
      return 1;
    }   
    else
    {
      cout << "Error. Fork has returned a negative value." << endl;
      exit(0);
    }
  }
}
char **convertToC(string tokens[], int tokenCount)
{
  char **words;
  words = (char **)malloc(sizeof(char *) * (tokenCount+1));

  for (int i = 0; i < tokenCount; i++)
  {
    words[i] = strdup(tokens[i].c_str());
  }
  words[tokenCount] = NULL;

  return words;
}
