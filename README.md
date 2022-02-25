# Лабораторная работа. Алгебра полиномов

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## Цель

__Цель данной работы__ — разработать программную систему для выполнения алгебраических операций над полиномами от трёх переменных.
Выполнение работы предполагает решение следующих задач:
1. Разработка интерфейса системы классов для работы с полиномом.
2. Разработка интерфейса системы классов для работы с постфиксной формой.
3. Разработка интерфейса системы классов для работы с таблицами.
3. Реализация методов классов каждой системы классов.
4. Разработка и реализация модульных тестов для классов.
5. Публикация исходных кодов в командном репозитории на GitHub.
6. Демонстрация результатов работы заказчику.


## Используемые инструменты
- Система контроля версий Git.
- Фреймворк для написания автоматических тестов Google Test.
- Среда разработки Microsoft Visual Studio.
- Утилита CMake для генерации проектов по сборке исходных кодов.

## Состав команды
- Бугров Андрей
- Колесников Денис
- Цветков Алексей

## Общая структура проекта

Структура проекта:

  - `gtest` — библиотека Google Test.
  - `base` — каталог с основным проектом ЛР.
  - `base_test` — каталог с проектом с модульными тестами.
  - `README.md` — информация о проекте.
  - `mp2-lab6-algebra-polynom.sln` - файл с решением (solution) для Microsoft Visual Studio.
  - Служебные файлы
    - `.gitignore` — перечень расширений файлов, игнорируемых Git при добавлении файлов в репозиторий.
    - ` CMakeLists.txt` — корневой файл для сборки проекта с помощью CMake.


## Программа должна выполнять следующие операции:
1. Операции с полиномом:
    - Сложение;
    - Вычитание;
    - Умножение;
    - Деление;
    - Нахождение значения в точке;
    - Интегрирование;
    - Дифференцирование.
2. Операции с постфиксной формой:
    - Те же операции, что и у полинома, кроме нахождения значения в точке;
    - Подразумевается использование скобок.
3. Операции с таблицами:
    - Добавление;
    - Поиск;
    - Удаление.


## Требования к различным системам классов
1. Система классов для работы с полиномом:
    - Полином должен быть от трёх переменных;
    - Достаточно требовать от пользователя ввода коэффициентов в порядке сначала x, затем y, затем z;
    - Пользователь вправе не вводить коэффициент 1 перед мономами, вводить мономы в случайном порядке, вводить сразу несколько мономов с одинаковыми степенями переменных;
    - Полином должен быть организован на списке.
2. Система классов для работы с постфиксной формой:
    - Возможность использования в выражениях имена полиномов;
    - Проверка на корректность алгебраического выражения.
3. Система классов для работы с таблицами:
    - Ключ в таблице — имя полинома;
    - Достаточно консольное визуальное представление таблицы;
    - Должны быть представлены следующие 6 таблиц:
        - Хэш-таблица (с открытым перемешиванием и со списками);
        - Неупорядоченная таблица (на массиве и на списке);
        - Упорядоченная таблцица (на массиве и на дереве поиска).
4. Общее требование — разумное время работы алгоритмов.



## Модели объектов и алгоритмы
### Моном
Содержит коэффициент и степень. Представляется в виде строки со знаком "+" или "-", цифрами и буквами x, y, z. Степени не выделяются отдельно символом "^".
### Полином
Строится на основе списка (может либо содержать начальное звено, либо список мономов). Таким образом, реализуется однонаправленный линейный список. Представление аналогично представлению монома за исключением того, что знаков "+" и "-" может быть много.

* Алгоритмы, используемые с мономами и полиномами
Мономы в данном случае рассматриваются как тривиальные полиномы.
  1. Сложение. Реализуется при помощи слияния двух отсортированнх списков.
  2. Вычитание. Реализуется при помощи слияния двух отсортированных списков полиномов (применяется инверсия коэффициентов).
  4. Умножение. Реализутся при помощи слияния множества (по числу мономов во втором полиноме) отсортированных списков полиномов.
  5. Деление. Реализуется при использовании алгоритма деления "уголком".
  6. Дифференцирование. Ненулевая степень уменьшается на 1, коэффициент умножается на показатель соответствующей степени. Моном с нулевой степенью удаляется.
  7. Интегрирование. Соответствующая степень увеличивается на 1, а коэффициент делится на эту соответствующую степень.
  8. Нахождение значения в точке. У каждого монома высчитывается при помощи умножения и возведения в степень, затем все полученные результаты складываются.

### Таблица
Содержит структуру хранения строк таблицы. Визуально представляется в виде символов псевдографики, доступных в ASCII.
Особенности различных таблиц:
1. Неупорядоченная таблица. Создаётся на основе динамического массива и на основе списка.

* Алгоритмы:
  - Поиск. Проход по списку или массиву (принципиальной разницы нет), пока не встретит совпадение ключа.
  - Добавление. Проверяет, не существует ли уже строка с данным ключом, затем вставляет либо в конец (массив), либо в начало (список). Если список двусвязный, то возможна вставка и в конец.
  - Удаление. Если таблица организована на списке, то просто удаляет звено и меняет указатель предыдущего звена (либо указатель на первое звено). Если таблица организована на массиве, то меняет местами последний элемент и удаляемый, а затем удаляет последний.

2. Упорядоченная таблица на массиве. Элементы в упорядоченных таблицах располагаются в некотором определенном порядке, задаваемым относительным расположением ключей. Таблица будет организована с помощью статического массива, поскольку для динамических упорядоченных таблиц при включении и удалении элементов приходится выполнять реорганизацию таблиц сразу при выполнении операций, что увеличивает время выполнения этих операций. 

* Алгоритмы:

  - Поиск элемента. В упорядоченной таблице элементы располагаются по возрастанию значений ключей, что позволяет делать некоторые предположения о месте размещения искомого элемента таблицы. Если, например, нам требуется найти элемент с ключом k*, и нам известно, что в i-ом элементе таблицы ключ ki>k*, это означает, что искомый элемент может находиться среди первых (i-1)-го элементов таблицы. Если же ki<k *, то искомый элемент может находиться среди последних элементов таблиц, начиная с (i+1)-го элемента. На этом основан алгоритм двоичного поиска. В соответствии с алгоритмом двоичного поиска определяется индекс записи, находящейся в середине таблицы. Сравнение искомого ключа и ключа найденного элемента позволяет определить (если они не равны), в какой половине таблицы – верхней или нижней – может находиться искомый элемент. В соответствии с принятым решением ненужная половина таблицы, включая и найденную запись, исключается из рассмотрения, в результате чего количество элементов, которые нужно проанализировать, сокращается вдвое. Такое сокращение может происходить до тех пор пока в одной из частей не отсанется единтсвенного нужного нам элемента. Таким образом, через некоторое количество попыток запись с требуемым ключом, если она имеется в таблице, будет найдена. Если же требуемая запись отсутствует в таблице, через некоторое количество попыток все элементы таблицы будут исключены из рассмотрения.

  - Добавление элемента. При включении нового элемента в таблицу удобно использовать алгоритм сортировки вставками. При этом если в таблице не могут находиться элементы с одинаковыми значениями ключей, сначала следует выполнить поиск элемента и, в случае неуспешного поиска, вставить в таблицу новый элемент. При использовании сортировки вставками сравнение ключей элементов осуществляется от конца таблицы к ее началу. Пока очередной элемент таблицы имеет ключ, превышающий ключ включаемого элемента, этот элемент таблицы копируется в следующую за ним позицию таблицы. Как только ключ очередного элемента таблицы окажется меньше ключа нового элемента, новый элемент включается после найденного. Если вся таблица будет просмотрена, новый элемент будет включен в первую позицию таблицы.
  - Удаление элемента. Удаление элемента включает в себя операцию поиска. После нахождения элемента осуществляется непосредственно удаление, при этом структура таблицы не должна быть нарушена. Поэтому требяется реорганизация таблицы, которая в случае таблицы на статическом массиве реализуется достаточно просто: в результате поиска элемента получаем его индекс в таблице, после чего нижняя половина таблицы перемещается на одну позицию вверх.
[//]: # ( 3. Таблица на АВЛ-дереве. АВЛ-дерево — сбалансированное по высоте двоичное дерево поиска: для каждой его вершины высота её двух поддеревьев различается не более чем на 1.

* Алгоритмы:
    - Балансировка - балансировкой - операция, которая в случае разницы высот левого и правого поддеревьев = 2, изменяет связи предок-потомок в поддереве данной вершины так, что разница становится <= 1, иначе ничего не меняет. Указанный результат получается вращениями поддерева данной вершины. Операция приводит к тому, что полная высота уменьшается не более чем на 1 и не может увеличиться.
    - Добавление. Проход по пути поиска, пока не убедимся, что ключа в дереве нет.Включение новой вершины в дерево и определения результирующих показателей балансировки. «Отступления» назад по пути поиска и проверка в каждой вершине показателя сбалансированности. Если необходимо — балансировка. При вставке (листу) присваивается нулевой баланс. 
    - Удаление вершины. Если вершина — лист, то удаляет её и вызовет балансировку всех её предков в порядке от родителя к корню. Иначе найдёт самую близкую по значению вершину в поддереве наибольшей высоты (правом или левом) и переместим её на место удаляемой вершины, при этом вызвав процедуру её удаления.
    - Поиск. Для каждого узла начиная с корня сравнивает значение его ключа с искомым ключом. Если ключи одинаковы, алгоритм закончен, в противном случае функция вызывается рекурсивно для левого или правого поддерева. )

4. Таблица на Красно-черном дереве. Красно-чёрным называется бинарное поисковое дерево, у которого каждому узлу сопоставлен дополнительный атрибут — цвет и для которого выполняются следующие свойства:
   - Каждый узел промаркирован красным или чёрным цветом
   - Корень и конечные узлы (листья) дерева — чёрные
   - У красного узла родительский узел — чёрный
   - Все простые пути из любого узла x до листьев содержат одинаковое количество чёрных узлов
   - Чёрный узел может иметь чёрного родителя
  
* Алгоритмы:
    - Добавление. Каждый элемент вставляется вместо листа, поэтому для выбора места вставки идёт от корня до тех пор, пока указатель на следующего сына не станет нулевым (то есть этот сын — лист). Вставляет вместо него новый элемент с нулевыми потомками и красным цветом. Теперь проверяет балансировку. Если отец нового элемента черный, то никакое из свойств дерева не нарушено. Если же он красный, то нарушается свойство 3, для исправления достаточно рассмотреть два случая: 1) "Дядя" этого узла тоже красный. Тогда, чтобы сохранить свойства 3 и 4, просто перекрашивает "отца" и "дядю" в чёрный цвет, а "деда" — в красный. 2) "Дядя" чёрный. Выполняет поворот. Если добавляемый узел был правым потомком, то необходимо сначала выполнить левое вращение, которое сделает его левым потомком. 
    - Удаление вершины. При удалении красной вершины свойства дерева не нарушаются, то восстановление балансировки потребуется только при удалении чёрной. Могут возникнуть три случая в зависимости от количества детей удаляемой вершины: 1) Если у вершины нет детей, то изменяем указатель на неё у родителя на nil. 2) Если у неё только один ребёнок, то делаем у родителя ссылку на него вместо этой вершины. 3) Если же имеются оба ребёнка, то находим вершину со следующим значением ключа. У такой вершины нет левого ребёнка (так как такая вершина находится в правом поддереве исходной вершины и она самая левая в нем, иначе бы мы взяли ее левого ребенка.  Удаляет скопировав её ключ в изначальную вершину. 
    - Поиск. Для каждого узла начиная с корня сравнивает значение его ключа с искомым ключом. Если ключи одинаковы, алгоритм закончен, в противном случае функция вызывается рекурсивно для левого или правого поддерева. 


  
### Интерфейс
Интерфейс, обеспечивающий передачу информации между пользователем-человеком и программно-аппаратными компонентами компьютерной системы. В программе представлен в виде консольного интерфейса и предоставляет доступ к пользовательским операциям модулей программной системы.




### Постфикс для полиномов

Для расчета арифметических операций с полиномами используется постфиксная форма. Она реализуется при помощи стека.

* Алгоритм перевода инфиксной формы в постфиксную для полиномов:
  1. Перебираем инфиксную запись слева направо.
  2. Если входящий элемент число, то он добавляется в постфикс. Если входящий элемент операция (+, -, *, /) то происходит проверка:
  3. Если стек операций пуст или содержит левую скобку в вершине, то входящий элемент добавляется в стек. 
  4. Если входящий элемент имеет более высокий приоритет чем вершина, он помещается в стек. 
  5. Если входящий элемент имеет более низкий или равный приоритет, чем вершина, стек выгружается в постфикс, пока не обнаружится элемент с меньшим приоритетом или левая скобка на вершине стека, затем входящий элемент добавляется в стек.
  6. Если входящий элемент является левой скобкой, он помещается в стек.
  7. Если входящий элемент является правой скобкой, стек выгружается в постфикс, до тех пор пока на вершине стека не окажется левая скобка, которая удаляется из стека.
  8. В конце инфиксной записи все элементы, оставшиеся в стеке, выгружаются в постфиксную запись.
