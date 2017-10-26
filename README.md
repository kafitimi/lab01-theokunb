# imgproc-01-bmpwrite
Это лабораторная работа к курсу "Алгоритмы цифровой обработки изображений".

## Оценка (заполняется после сдачи работы)
| Показатель  | 1 |2 |3 |4 |
| -------|- |- |- |- |
| Цвет   |  |  |  |X |
| Ч/б    |  |  |  |X |
| Вовремя|  |  |  |X |

## ЛР1: Создание BMP-файла

**Цель работы**: написать программу, которая зачитывает из _текстового_ файла двумерный числовой массив, задающий цвета пикселей изображения и формирует файл в формате BMP (Windows Bitmap), пиксели которого соответствуют этим числам. Используйте вашу программу, чтобы узнать, что за изображения скрываются в текстовых файлах!

**Что надо сдать**: 
* проект консольного приложения Windows для MS Visual Studio на языке на С++, который скомпилируется в программу, выполняющую поставленную задачу, либо
* питон-скрипт bmpwrite.py, выполняющий поставленную задачу.

**Входной файл**: программа читает из входного файла `input.txt`, либо файла, имя которого указано в качестве аргумента командной строки.

Первая строка входного файла содержит числа 

  N M C 

где `N` - ширина изображения, `M` - высота изображения, а `C` - признак цветности. При `C=0` следует создать BMP-файл, использующий градации серого, а при  `C=2` - полноцветный BMP-файл с 24 битами на пиксель.

Далее идут `M` строк, каждая из которых содержит значения цветов пикселей очередного горизонтального ряда, ряды записаны сверху вниз:

* для *C*=0: по *N* целых значений в диапазоне 0..255 (`0`=черный, `255`=белый), либо
* для *C*=2: по 3*N* целых значений в диапазоне 0..255, задающих по группами по три цвет очередного пикселя в модели RGB (`255 0 0`=красный, `0 0 255`=синий)

**Выходной файл**: должен представлять собой ВMP-файл, имя которого получено из имени входного файла добавлением `.bmp`, например для `input.txt` должно получиться `input.txt.bmp`.

**Содержимое репозитория**: 
* презентация с деталями формата BMP;
* проект Visual Studio с программой, которая правильно зачитывает ваходной файл;  
* скрипт на Питоне, выполняющий то же;
* пример небольшого текстового файла [`color3x3.txt`](color3x3.txt) и соответствующего 24-битного цветного файла `color3x3.txt.bmp`;
* пример небольшого текстового файла [`gray3x3.txt`](gray3x3.txt) и соответствующего файла в градациях серого  `gray3x3.txt.bmp`,
* текстовые файлы [`inputcolor.txt`](inputcolor.txt) и [`inputgray.txt`](inputgray.txt), которые надо преобразовать в bmp-файлы, чтобы узнать, что на них изображено.

**Запрещается пользоваться любыми библиотеками, кроме входящих в поставку MSVC + Windows SDK/Python standard library.**

<hr>

This is a lab for the "Digital image processing algorithm" course.

## Marks (to be filled by the instructor)
| Mark rubric   |1 |2 |3 |4 |
| --------------|- |- |- |- |
| Color BMP     |  |  |  |  |
| Grayscale BMP |  |  |  |  |
| Timeliness    |  |  |  |  |

## Lab1: Writing BMP files

**Goal**: write a program that will read from _text_ file a numeric 2d array of color values for pixels, and will write out a valid BMP (Windows Bitmap) image file containing those pixels. Use your program to reveal the mystery images!

The BMP file format is chosen for its simplicity.
 
**Deliverables**: 

* either an MS Visual Studio C++ console application project that will compile into a program that does the job, or
* a Python script `bmpwrite.py` that does the job.

**Input file**: the program should read from the file given as the command-line argument, or the file named `input.txt`.

The first line of the input filecontains three integers 

  N M C 

being the image width `N`, the image height `M`, and the color code `C`. `C=0` means grayscale image data, `C=2` a 24 bit-per-pixel RGB data.

The remaining `M` lines of the input contain the pixel values of pixel rows, from top to bottom:

* for *C*=0: each line holds ''N'' integers in the range 0..255 (`0`=black, `255`=white), or
* for *C*=2: each line holds 3''N'' integers in the range 0..255, giving pixel values as triplets of integers in the RGB model(`255 0 0`=красный, `0 0 255`=синий)

**Output file**: must be a valid ВMP-file recognized at least by the standard Windows image viewer, the name obtained by appending `.bmp` to the input file name, e.g.  `input.txt.bmp` if input data was given in `input.txt`.

**This repo contains**: 
* a presentation with the BMP file format specifics
* a Visual Studio 2015 project with C++ code that only reads the input file,  
* a Python sript that does the same,
* a small sample text file [`color3x3.txt`](color3x3.txt) and the corresponding 24-bit color BMP file `color3x3.txt.bmp`,
* a sample text file [`gray3x3.txt`](gray3x3.txt) and the corresponding grayscale file  `gray3x3.txt.bmp`,
* text files [`inputcolor.txt`](inputcolor.txt) и [`inputgray.txt`](inputgray.txt) that should be converted ( I will not reveal what is in the images).

**You must not use any libraries not included with MSVC + Windows SDK or the Python standard library.**
