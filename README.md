# SMNDE
Имитационная модель нелинейной динамической среды в QT 5.

Вычисляется модель третьего порядка:
x1 = x2;
x2 =(c*u)/x3 - g - (r*x2^2)/x3;
x3 = -u.

Интегрирование методом Эйлера. В главном меню вводятся значения постоянных параметров модели (c,u,T,hтв) и начальные значения переменных состояния(x1(0), x2(0), x3(0)). g = 9.81, r = 0.1*e^(-x1/hтв).

В программе есть:
1. Решение системы дифференциальных уравнений на интервале [0;T]. Для демонстрации результатов обеспечен вывод графиков xi(t), i = 1,2,...,n; значения указанных переменных состояний в конце интервала интегрирования xk(T) и значения относительной погрешности.
2. Анализ зависимости точности и трудоёмкости решения задачи от шага интегрирования. Вывод графиков зависимости относительно погрешности и трудоёмкости от величины шага h.
3. Автоматический выбор величины шага интегрирования для достижения относительной погрешности не более 1% с выводом итоговых результатов для найденного шага.

Графики можно масштабировать и двигать. Для построения графиков был использован QCustomPlot https://www.qcustomplot.com

<h3>Скриншоты работы</h3>

<div>
  <h4>Главное меню</h4>
  <img width="819" alt="Снимок экрана 2024-05-05 в 12 55 12" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/ed33bc9e-3847-4185-8d7c-f393e5f267a3">
</div>
<div>
  <h4>Графики с шагом h</h4>
  <img width="1037" alt="Снимок экрана 2024-05-05 в 13 04 17" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/dc22c66a-30b0-41f7-bcb3-22e3a805821e">
</div>
<div>
  <h4>Графики с шагом h/2</h4>
  <img width="1035" alt="Снимок экрана 2024-05-05 в 13 05 21" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/b67a42a0-76ed-4f6c-8606-e468ec029fd8">
</div>
<div>
  <h4>Дополнительные данные</h4>
  <img width="1033" alt="Снимок экрана 2024-05-05 в 13 06 03" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/1abe4dec-6a06-47d6-91ed-1c46c7dd4f77">
</div>
<div>
  <h4>Автоматическое решение</h4>
  <img width="1028" alt="Снимок экрана 2024-05-05 в 13 06 42" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/5dad11c4-4be3-4ea5-b137-a50e44784cb6">
</div>
<div>
  <h4>Оценка трудоёмкости</h4>
  <img width="1031" alt="Снимок экрана 2024-05-05 в 13 07 20" src="https://github.com/BabySharkHere/SMNDE/assets/82753628/b890d152-0392-4b93-bea1-874275622ff0">
</div>
