# Architecture of Evaluating Systems LAB2

The assignment text: [`task.pdf`](./task.pdf)

The solution source code: [`LAB2.cpp`](./LAB2.cpp)

## Variants
1, 3, 7

1) 1-� ������� ������ � ����������, ��������� ������� ���������� �
����������
2) 15-���
3) X mod Y (������ �� ������ X �� Y).

### Tasks

1) ��������� ������������ �������� � ���������� ���� (���������, ���� �����=���� �������);
2) ����� 2 ������� (���� � ��� - ��������� �������� � ������/����/��, ���� ��������� ��������);
3) ��� ��������/������� ������������� ������, �������, ��� ������ ������� �� ��������� ����������� ���.
���������� ������ �� �������������� � 16-������ ������;
4) �������� � ������ ����� �� ����� ����� ���������� ��������� �������;
5) ��������� ��������� ������ (���������, 1-� ���� � ��������� ������� � ������ �������, 2-� ���� - �������������
��������, 3-� ���� � ��������� �������� � ��������� ����������).

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
