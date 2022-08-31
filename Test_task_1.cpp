#include <iostream>
#include <random>

#include "CArray.h"

template <typename TData>
void PrintResult(const CArray<TData>& _arr)
{
  for (auto& _it : _arr)
    std::cout << _it << " ";

  std::cout << "\n\n";
}

void FirstTask()
{
  CArray<int> arr;

  std::cout << "1.1. добавление в цикле 20 случайных чисел в диапазоне от 0 до 100:\n";
  for (int i = 0; i < 20; i++)
    arr.push_back(std::rand() % 100);

  PrintResult(arr);

  std::cout << "1.2. упорядочивание получившегося набора чисел по возрастанию:\n";
  std::sort(&arr[0], &arr[arr.size()]);

  PrintResult(arr);

  std::cout << "1.3. удаление каждого 2 элемента:\n";
  for (int i = 0, _counter = 0, _entry_size = arr.size(); i != _entry_size; i++, _counter++)
  {
    if (_counter % 2 == 1)
    {
      arr.erase(i);
      i--;
    }
  }

  PrintResult(arr);

  std::cout << "1.4. вставка 10 случайных чисел в диапазоне от 0 до 100 на случайные позиции:\n";
  for (int i = 0; i < 10; i++)
    arr.insert(std::rand() % arr.size(), std::rand() % 100);

  PrintResult(arr);

  std::cout << "1.5. очистка контейнера:\n";

  arr.clear();
  std::cout << "size: " << arr.size() << std::endl;

  PrintResult(arr);
}

void SecondTask()
{
  std::string dictionary[] = { "before", "you", "begin", "the", "test", "assignment", "please", "note", "that", "is",
                               "not", "paid", "and", "will", "not", "be", "used", "for", "commercial", "purposes", "also",
                               "providing", "results", "you", "accept", "fact", "company", "may", "futer", "develop",
                               "internally", "or", "receive", "from", "third", "parties", "ideas", "and", "other", "similar",
                               "materials", "submission", "thaks", "for", "reading" };

  CArray<std::string> arr;

  std::cout << "2.1. добавление в цикле 15 случайно выбранных слов, состоящих из латинских букв в нижнем регистре:\n";
  for (int i = 0; i < 15; i++)
    arr.push_back(dictionary[std::rand() % sizeof(dictionary) / sizeof(std::string)]);

  PrintResult(arr);

  std::cout << "2.2. упорядочивание получившегося набора слов по возрастанию.:\n";
  // sort из 1.2 отсортирует по возрастанию от А до Я
  std::sort(&arr[0], &arr[arr.size()],
    [](
      const std::string& _lhs,
      const std::string& _rhs
      )
    {
      return _lhs.size() < _rhs.size();
    }
  );

  PrintResult(arr);

  std::cout << "2.3. удаление каждого слова, включающего в себя любую из букв: a,b,c,d,e:\n";
  for (int i = 0, _counter = 0, _entry_size = arr.size(); _counter != _entry_size; i++, _counter++)
  {
    for (auto& _it : arr[i])
    {
      if (_it >= 97 && _it <= 101)
      {
        arr.erase(i--);
        break;
      }
    }
  }

  PrintResult(arr);

  std::cout << "2.4. вставка 3 новых случайно выбранных слов на случайные позиции:\n";
  for (int i = 0; i < 3; i++)
    arr.insert(arr.size() == 0 ? 0 : std::rand() % arr.size(), dictionary[std::rand() % sizeof(dictionary) / sizeof(std::string)]);

  PrintResult(arr);
}

int main()
{
  setlocale(LC_ALL, "Russian");
  
  std::srand(std::time(nullptr));

  FirstTask();
  SecondTask();

  //for (int i = 0; i < 200; i++)
  //{
  //  FirstTask();
  //  SecondTask();
  //}
}