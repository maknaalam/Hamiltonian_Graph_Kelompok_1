# Hamiltonian_Graph_Kelompok_1

Group Number: 1 

Group Members:
-	Alif Muflih Jauhary (5025241003)
-	Rayen Yeriel Mangiwa (5025241262)
-	Makna Alam Pratama (5025241077)

## Problem for TSP & CPP

![1](image/hamiltonian.png)<br />

Note on input <br />
first two lines defines the number of nodes n and number of edges e respectively <br />
next e lines consists of set of number denoting: name of edge, two edges that it connects, and its cost <br />
last line denotes the starting point (and finishing point) of the TSP/CPP solution. <br />

### Travelling Salesman Problem (TSP)

Code:
[Code TSP](ravellingSalesmanProblem.cpp)
Input #1 <br />
```
3 
4 
0 1 2 10 
1 2 3 5
2 3 1 7 
3 3 1 2 
1
```
Output #1:<br />

Cost: 17 <br />
Route: 0, 1, 3  <br />


### Chinese Postman Problem (CPP)

Code:

[Code CPP](chinesePostmanProblem.c)

To use the program, start by entering the number of nodes and the number of edges on the first line, separated by a space, and then press Enter. Next, on the following lines, input the details for each edge by typing four numbers—representing the edge's name, the two nodes it connects, and its cost—each separated by a space. After all the edges have been entered, type the single number for the starting node on the final line and press Enter again. The program will then automatically run and display the result. <br />

Input #1 <br />
```
4 5 
0 1 2 10
1 2 3 5
2 3 4 8
3 4 1 6
4 1 3 12
1
```
Output #1:<br />

Cost: 53 <br />
Route: 1, 2, 3, 4, 1, 3, 1 <br />

Input #2 <br />
```
5 6
0 1 2 3
1 2 3 5
2 3 4 4
3 4 1 2
4 1 5 6
5 2 5 7
1
```
Output #2: <br />

Cost: 30 <br />
Route: 1, 4, 3, 2, 5, 1, 2, 1 <br />

## The Knight's Tour

| | | | | |
| --- | --- | --- | --- | --- |
| 0,0  | 1,0 | 2,0  | 3,0  | 4,0  |
| 0,1  | 1,1 | 2,1  | 3,1  | 4,1  |
| 0,2  | 1,2 | 2,2  | 3,2  | 4,2  |
| 0,3  | 1,3 | 2,3  | 3,3  | 4,3  |
| 0,4  | 1,4 | 2,4  | 3,4  | 4,4  |

Note on input <br />
first line defines the size of the chessboard <br />
second line defines the starting position of the knight (coordinate) <br />
<br />
Note on output <br />
It will be the coordinates the knight will go until it visit all squares in the chessboard <br />
<br /> <br />
Code:

[Code The Knight's Tour](theKnightsTour.c)

How to use: <br />
enter 2(two) numbers separated by space(spacebar) on the first line, that initiates size of chessboard; <br />
click enter to begin new line; <br />
enter another 2(two) numbers separated by space(spacebar) on the next line, this initiates the starting point (X,Y); <br />
run the program. <br />
Sample Inputs and Outputs: <br />
Input #0 <br />
```
5 5 
2 2
```
Output: <br />
2 2 <br />
4 1 <br />
2 0 <br />
0 1 <br />
1 3 <br />
3 4 <br />
4 2 <br />
3 0 <br />
1 1 <br />
0 3 <br />
2 4 <br />
4 3 <br />
3 1 <br />
1 0 <br />
0 2 <br />
1 4 <br />
3 3 <br />
2 1 <br />
4 0 <br />
3 2 <br />
4 4 <br />
2 3 <br />
0 4 <br />
1 2 <br />
0 0 <br />

other inputs example <br />
Input #1 <br />
```
6 6
0 0
```
Output: <br />
0 0 <br />
1 2 <br />
3 1 <br />
5 0 <br />
4 2 <br />
3 0 <br />
1 1 <br />
0 3 <br />
2 2 <br />
4 1 <br />
2 0 <br />
0 1 <br />
1 3 <br />
0 5 <br />
2 4 <br />
4 5 <br />
5 3 <br />
3 2 <br />
5 1 <br />
4 3 <br />
5 5 <br />
3 4 <br />
1 5 <br />
2 3 <br />
0 4 <br />
2 5 <br />
4 4 <br />
5 2 <br />
4 0 <br />
2 1 <br />
3 3 <br />
5 4 <br />
3 5 <br />
1 4 <br />
0 2 <br />
1 0 <br />

Input #2 <br />
```
3 3
0 0
```
Output: <br />
No solution found. <br />

