### JakDojade / How to get there

Find the shortest route to the selected city.

"#" represents a two-way road, which takes 1 minute to pass.
"." represents an empty field, through which you cannot drive.
"*" (asterisk) represents a city, which acts as a road but also specifies the coordinates of the city.
Letters represent the names of cities, and "*" (asterisk) is always placed next to the first or last letter of the city's name.

The first line of input contains the dimensions of the map.
Then we load the map.
Next, we load "n" number of airlines, which are one-way connections.
In the following "n" lines, the pattern is [source] [destination] [time].
After the airlines, we load the number of questions.

[source] [destination] [1] represents a question about the fastest time to get from the source to the destination.
[source] [destination] [0] represents a question about the fastest time and all the cities visited during the travel.

examples of inputs: 

1st: 

INPUT:
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
2
KRAKOW GDANSK 10
WARSZAWA WROCLAW 3
3
KRAKOW GDANSK 1
WARSZAWA WROCLAW 1
SZCZECIN KRAKOW 1

OUTPUT:
10
3
29 KIELCE

2nd:

INPUT:
33 23
*A.*W.........Y**Z..........X*.V*
#..#.........................#..#
*B.#.........................#.U*
#..#.........................#..#
*C.#.........................#.T*
#..#.........................#..#
*D.#.........................#.S*
#..#.........................#..#
*E.#.........................#.R*
#..#..........BB#####........#..#
*F.#............*...#........#.Q*
#..#............#...#........#..#
*G.#........AA*##...#........#.P*
#..#.............##*#........#..#
*H.#.............#..CC.......#.O*
#..#...........DD*...........#..#
*I.#.........................#.N*
#..#.........................#..#
*J.#.........................#.M*
#..#.........................#..#
*K.###########################.L*
#...............................#
#################################
0
45
A V 1
V A 1
W X 1
X W 1
Y Z 1
Z Y 1
A V 0
V A 0
W X 0
X W 0
Y Z 0
Z Y 0
V A 0
V B 0
V C 0
V D 0
V E 0
V F 0
V G 0
V H 0
V I 0
V J 0
V K 0
V L 0
V M 0
V N 0
V O 0
V P 0
V Q 0
V R 0
V S 0
V T 0
V U 0
AA BB 1
AA CC 1
AA DD 1
BB AA 1
BB CC 1
BB DD 1
CC AA 1
CC BB 1
CC DD 1
DD AA 1
DD BB 1
DD CC 1

OUTPUT:
76 B C D E F G H I J K L M N O P Q R S T U
76 U T S R Q P O N M L K J I H G F E D C B
66
66
1
1
76
76
66
66
1
1
76
74
72
70
68
66
64
62
60
58
56
20
18
16
14
12
10
8
6
4
2
4
14 BB
18 BB CC
4
10
14 CC
14 BB
10
4
18 CC BB
14 CC
4
