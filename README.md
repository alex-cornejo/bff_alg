# Burning Farthest-First algorithm
## An approximation algorithm for the graph burning problem

This repository contains the following approximation algorithms for the Graph Burning Problem.

|  Algorithm |                                          Complexity                               | <img src="https://render.githubusercontent.com/render/math?math=\rho">| keyword
|------------|-----------------------------------------------------------------------------------| -|-
| BFF        | <img src="https://render.githubusercontent.com/render/math?math=O(n^3)">          | <img src="https://render.githubusercontent.com/render/math?math=3-2/b(G)">| bff
| BFF+       | <img src="https://render.githubusercontent.com/render/math?math=O(n^3)">          | <img src="https://render.githubusercontent.com/render/math?math=3-2/b(G)">| bff+


## Install c++ boost libraries
```
sudo apt install libboost-all-dev
```

## Install cmake
```
sudo apt install cmake
```

## Compile program
```
cmake -DCMAKE_BUILD_TYPE=Release .
cmake --build .
```
The binary file will be generated onto the root folder with the name ```bff_alg```.

## Run

```
./bff_alg [file] [algorithm]
```

### Where,

|  Parameter |                                          Description                                          |
|----------|---------------------------------------------------------------------------------------------|
| `[file]` | (string) Instance file path with a valid format.                                    |
| `[algorithm]`    | (string) Algorithm to execute (**bff** and **bff+**)  |

## Example 1 - BFF algorithm
```
./bff_alg dataset/econ-mahindas.mtx bff
```

## Output 1
```
Compute all shortest paths running time: 0.125 seconds
Algorithm running time: 0 seconds
[367, 505, 555, 50, 503, 549]
6
```

## Example 2 - BFF+ algorithm
```
./bff_alg dataset/econ-mahindas.mtx bff+
```

## Output 2
```
Compute all shortest paths running time: 0.140625 seconds
Algorithm running time: 0.046875 seconds
[989, 554, 555, 50, 51]
5
```

# Contact
* jesus.garcia@conacyt.mx
* alexcornejo@inaoe.edu.mx

