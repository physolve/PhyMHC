# Задачи разработки

Конец декабря 2024: разработать модель процесса циклирования двух металлогидридных реакторов
Концепт модели: реакция в двух реакторов протекает как маятник. Клапаны блокируют потоки, чтобы зарядить. И разблокируют, чтобы разрядить

## Система моделирования процесса цикла
- [ ] Разбить цикл на стадии (параллельные)
    - [ ] Нагрев, охлаждение -> параметры?
    - [ ] Подача газа -> параметры?
    - [ ] Откачка -> параметры?
    - [ ] Сорбция и десорбция без нагрева -> параметры?
    - [ ] Нагрев в материале для сорбции -> параметры?
    - [ ] Нагрев в материале для десорбции -> параметры?
- [ ] Разработать event для рекции кллапанов на стадии

## Параметры на реакторе
- [ ] Вывод входного, внутреннего и выходного потоков (входной и выходной - плюс минус одно?)
- [ ] Внутренее время реактора 

## Влияние клапана
- [ ] Если клапан открыт и подача газа - растет пока не наберет в молях достаточное кол-во

## Причины остановки эксперимента
- [ ] Закончился баллон - условия, предотвратить?
- [ ] Материал не сорбцирует - условия?
- [ ] Материал не десорбцирует - условия?
- [ ] Нагрев меньше ожидаемого - условия?
- [ ] Нагрев больше ожидаемого - условия?
- [ ] Давление газа меньше ожидаемого - условия?
- [ ] Давление газа больше ожидаемого - условия?
- [ ] Вакуум не герметичный - условия?