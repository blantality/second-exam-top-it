#include <iostream>

namespace parsov
{
  char* appendChars(const char* oldArray, std::size_t oldSize, std::size_t count, char symbol)
  {
    char* newArray = nullptr;
    try
    {
      newArray = new char[oldSize + count];
    }
    catch (const std::bad_alloc&)
    {
      return nullptr;
    }
    for (std::size_t i = 0; i < oldSize; ++i)
    {
      newArray[i] = oldArray[i];
    }
    for (std::size_t i = 0; i < count; ++i)
    {
      newArray[oldSize + i] = symbol;
    }
    return newArray;
  }
}

int main()
{
  char* seq= nullptr;
  std::size_t seqSize = 0;

  while (true)
  {
    unsigned int count = 0;
    if (!(std::cin >> count))
    {
      if (std::cin.eof())
      {
        break;
      }
      std::cerr << "failed to read count\n";
      delete[] seq;
      return 1;
    }

    char symbol = '\0';
    if (!(std::cin >> symbol))
    {
      std::cerr << "failed to read symbol\n";
      delete[] seq;
      return 1;
    }

    if (count > 0)
    {
      char* newSeq = parsov::appendChars(seq, seqSize, count, symbol);
      if (!newSeq)
      {
        std::cerr << "failed to alloc memory\n";
        delete[] seq;
        return 2;
      }
      delete[] seq;
      seq = newSeq;
      seqSize = seqSize + count;
    }
  }

  std::cout << "\n";
  delete[] seq;
  return 0;
}
