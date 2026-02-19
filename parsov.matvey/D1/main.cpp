#include <iostream>
#include <cstddef>
#include <new>

namespace parsov
{
  char* extend(const char* oldArray, std::size_t oldSize, std::size_t count, char symbol)
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

  void reverseSequence(char* seq, std::size_t size)
  {
    if (size == 0)
    {
      return;
    }
    std::size_t left = 0;
    std::size_t right = size - 1;
    while (left < right)
    {
      const char temp = seq[left];
      seq[left] = seq[right];
      seq[right] = temp;
      left = left + 1;
      right = right - 1;
    }
  }

  void cleanup(char* seq, std::size_t size)
  {
    reverseSequence(seq, size);
    for (std::size_t i = 0; i < size; ++i)
    {
      std::cout << seq[i];
    }
    std::cout << "\n";
    delete[] seq;
  }
}

int main()
{
  char* seq = nullptr;
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
      parsov::cleanup(seq, seqSize);
      return 1;
    }

    char symbol = '\0';
    if (!(std::cin >> symbol))
    {
      std::cerr << "failed to read symbol\n";
      parsov::cleanup(seq, seqSize);
      return 1;
    }

    if (count > 0)
    {
      char* newSeq = parsov::extend(seq, seqSize, count, symbol);
      if (!newSeq)
      {
        std::cerr << "failed to alloc memory\n";
        parsov::cleanup(seq, seqSize);
        return 2;
      }
      delete[] seq;
      seq = newSeq;
      seqSize = seqSize + count;
    }
  }

  parsov::cleanup(seq, seqSize);
  return 0;
}
