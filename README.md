# Architecture of Evaluating Systems LAB2

The assignment text: [`task.pdf`](./task.pdf)

The solution source code: [`LAB2.cpp`](./LAB2.cpp)

## Variants
1, 3, 7

1) 1-й операнд завжди в акумуляторі, результат команди заноситься в
акумулятор
2) 15-бітні
3) X mod Y (остача від ділення X на Y).

### Tasks

1) розміщення інтерпретуємої програми у текстовому файлі (наприклад, один рядок=одна команда);
2) мінімум 2 команди (одна з них - занесення значення у регістр/стек/ОП, інші задаються варіантом);
3) для операндів/регістрів представлення побітно, можливо, для деяких варіантів із побайтним групуванням бітів.
Оперативна пам’ять має представлятися у 16-річному форматі;
4) фіксація у регістрі стану як мінімум знаку результату виконання команди;
5) потактове виконання команд (наприклад, 1-й такт – занесення команди у регстр команди, 2-й такт - інтерпретація
операндів, 3-й такт – виконання операції і занесення результату).

## Registres

1) accm
2) state
3) tick

## Implemented commands

* *set_c const* - sets accum to const
* *load_ca addr* - loads value of addr in accm
* *dump_ca addr* - dumps accum val to RAM

* *mod_c const* - computes accum mod const to accum
* *mod_ca addr* - computes accum mod value of addr to accum
