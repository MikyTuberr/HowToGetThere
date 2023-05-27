# JakDojade / How to get there

<p>Find the shortest route to the selected city.</p>

<p>"#" represents a two-way road, which takes 1 minute to pass.</p>
<p>"." represents an empty field, through which you cannot drive.</p>
<p>"*" (asterisk) represents a city, which acts as a road but also specifies the coordinates of the city.</p>
<p>Letters represent the names of cities, and "*" (asterisk) is always placed next to the first or last letter of the city's name.</p>

<p>The first line of input contains the dimensions of the map. Then we load the map. 
Next, we load "n" number of airlines, which are one-way connections.
In the following "n" lines, the pattern is [source] [destination] [time].
After the airlines, we load the number of questions. </p>

<p>[source] [destination] [1] represents a question about the fastest time to get from the source to the destination.</p>
<p>[source] [destination] [0] represents a question about the fastest time and all the cities visited during the travel.</p>

<p>examples of inputs: </p>

<h1>1st:</h1> 

<h2>INPUT:</h2>
<p>20 20</p>
<p>.........GDANSK.....</p>
<p>........*...........</p>
<p>........#...........</p>
<p>........#...........</p>
<p>*##################.</p>
<p>#SZCZECIN.........#.</p>
<p>#.................#.</p>
<p>##................#.</p>
<p>.############*#####.</p>
<p>.#...WARSZAWA.......</p>
<p>.#..................</p>
<p>.#############......</p>
<p>.#...........#......</p>
<p>.#..WROCLAW.##......</p>
<p>.#..*.......*.......</p>
<p>.####.......#KIELCE.</p>
<p>......*##.#########.</p>
<p>.OPOLE..#.*.......#.</p>
<p>........#.KRAKOW..#.</p>
<p>........###########.</p>
<p>2</p>
<p>KRAKOW GDANSK 10</p>
<p>WARSZAWA WROCLAW 3</p>
<p>3</p>
<p>KRAKOW GDANSK 1</p>
<p>WARSZAWA WROCLAW 1</p>
<p>SZCZECIN KRAKOW 1</p>

<h2>OUTPUT:</h2>
<p>10</p>
<p>3</p>
<p>29 KIELCE</p>

<h1>2nd:</h1>

<h2>INPUT:</h2>
<p>33 23</p>
<p>*A.*W.........Y**Z..........X*.V*</p>
<p>#..#.........................#..#</p>
<p>*B.#.........................#.U*</p>
<p>#..#.........................#..#</p>
<p>*C.#.........................#.T*</p>
<p>#..#.........................#..#</p>
<p>*D.#.........................#.S*</p>
<p>#..#.........................#..#</p>
<p>*E.#.........................#.R*</p>
<p>#..#..........BB#####........#..#</p>
<p>*F.#............*...#........#.Q*</p>
<p>#..#............#...#........#..#</p>
<p>*G.#........AA*##...#........#.P*</p>
<p>#..#.............##*#........#..#</p>
<p>*H.#.............#..CC.......#.O*</p>
<p>#..#...........DD*...........#..#</p>
<p>*I.#.........................#.N*</p>
<p>#..#.........................#..#</p>
<p>*J.#.........................#.M*</p>
<p>#..#.........................#..#</p>
<p>*K.###########################.L*</p>
<p>#...............................#</p>
<p>#################################</p>
<p>0</p>
<p>45</p>
<p>A V 1</p>
<p>V A 1</p>
<p>W X 1</p>
<p>X W 1</p>
<p>Y Z 1</p>
<p>Z Y 1</p>
<p>A V 0</p>
<p>V A 0</p>
<p>W X 0</p>
<p>X W 0</p>
<p>Y Z 0</p>
<p>Z Y 0</p>
<p>V A 0</p>
<p>V B 0</p>
<p>V C 0</p>
<p>V D 0</p>
<p>V E 0</p>
<p>V F 0</p>
<p>V G 0</p>
<p>V H 0</p>
<p>V I 0</p>
<p>V J 0</p>
<p>V K 0</p>
<p>V L 0</p>
<p>V M 0</p>
<p>V N 0</p>
<p>V O 0</p>
<p>V P 0</p>
<p>V Q 0</p>
<p>V R 0</p>
<p>V S 0</p>
<p>V T 0</p>
<p>V U 0</p>
<p>AA BB 1</p>
<p>AA CC 1</p>
<p>AA DD 1</p>
<p>BB AA 1</p>
<p>BB CC 1</p>
<p>BB DD 1</p>
<p>CC AA 1</p>
<p>CC BB 1</p>
<p>CC DD 1</p>
<p>DD AA 1</p>
<p>DD BB 1</p>
<p>DD CC 1</p>

<h2>OUTPUT:</h2>
<p>76 B C D E F G H I J K L M N O P Q R S T U</p>
<p>76 U T S R Q P O N M L K J I H G F E D C B</p>
<p>66</p>
<p>66</p>
<p>1</p>
<p>1</p>
<p>76</p>
<p>76</p>
<p>66</p>
<p>66</p>
<p>1</p>
<p>1</p>
<p>76</p>
<p>74</p>
<p>72</p>
<p>70</p>
<p>68</p>
<p>66</p>
<p>64</p>
<p>62</p>
<p>60</p>
<p>58</p>
<p>56</p>
<p>20</p>
<p>18</p>
<p>16</p>
<p>14</p>
<p>12</p>
<p>10</p>
<p>8</p>
<p>6</p>
<p>4</p>
<p>2</p>
<p>4</p>
<p>14 BB</p>
<p>18 BB CC</p>
<p>4</p>
<p>10</p>
<p>14 CC</p>
<p>14 BB</p>
<p>10</p>
<p>4</p>
<p>18 CC BB</p>
<p>14 CC</p>
<p>4</p>
